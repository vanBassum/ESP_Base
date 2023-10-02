#pragma once
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"
#include <string>
#include "esp_log.h"



// https://beej.us/guide/bgnet/html/#structs

class Endpoint
{
	constexpr const static char* TAG = "Endpoint";
	struct sockaddr addr;	//holds socket address information for many types of sockets. Including IPv4 amd IPv6
	
	
public:
	
	socklen_t Size() const {
		return addr.sa_family == AF_INET ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
    }

	const struct sockaddr* GetSockAddr() const
	{
		return &addr;
	}
		
	void Set(int port)
	{
		memset(&addr, 0, sizeof(addr));
		struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *)&addr ;
		dest_addr_ip4->sin_addr.s_addr = htonl(INADDR_ANY) ;
		dest_addr_ip4->sin_family = AF_INET ;
		dest_addr_ip4->sin_port = htons(port) ;
	}

	bool Resolve(std::string host, int port)
	{
		memset(&addr, 0, sizeof(addr));
		ip_addr_t ip_Addr;
		err_t err = dns_gethostbyname(host.c_str(), &ip_Addr, NULL, NULL);
		if (err != 0)
		{
			ESP_LOGE(TAG, "DNS failed %d", err);
			return false;
		}
		
		if (ip_Addr.type == IPADDR_TYPE_V4)
		{
			struct sockaddr_in *destAddr = (struct sockaddr_in *)&addr;
			destAddr->sin_len = sizeof(struct sockaddr_in);
			destAddr->sin_addr.s_addr = ip_Addr.u_addr.ip4.addr;
			destAddr->sin_family = AF_INET;
			destAddr->sin_port = htons(port);
		}
		
		if (ip_Addr.type == IPADDR_TYPE_V6)
		{
			struct sockaddr_in6* destAddr = (struct sockaddr_in6*)&addr;
			destAddr->sin6_len = sizeof(struct sockaddr_in6);
			destAddr->sin6_addr.un.u32_addr[0] = ip_Addr.u_addr.ip6.addr[0];
			destAddr->sin6_addr.un.u32_addr[1] = ip_Addr.u_addr.ip6.addr[1];
			destAddr->sin6_addr.un.u32_addr[2] = ip_Addr.u_addr.ip6.addr[2];
			destAddr->sin6_addr.un.u32_addr[3] = ip_Addr.u_addr.ip6.addr[3];
			destAddr->sin6_family = AF_INET6;
			destAddr->sin6_port = htons(port);
		}
		
		return true;
	}
};

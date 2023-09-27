#pragma once
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"
#include <string>
#include "esp_log.h"


class Endpoint
{
	constexpr const static char* TAG = "Endpoint";
	struct sockaddr_storage addr; // Large enough for both IPv4 or IPv6
		
public:

		
	socklen_t Size() const
	{
		return sizeof(addr);
	}
		
	struct sockaddr* GetSockAddr() const
	{
		return (struct sockaddr *)&addr;
	}
		
	void Set(int port)
	{
		struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *)&addr ;
		dest_addr_ip4->sin_addr.s_addr = htonl(INADDR_ANY) ;
		dest_addr_ip4->sin_family = AF_INET ;
		dest_addr_ip4->sin_port = htons(port) ;
	}

	void Set(std::string host, int port)
	{			
		ip_addr_t ip_Addr;
		IP_ADDR4(&ip_Addr, 0, 0, 0, 0);
		err_t err = dns_gethostbyname(host.c_str(), &ip_Addr, NULL, NULL);
		if (err != 0)
		{
			ESP_LOGE(TAG, "DNS failed %d", err);
			return;
		}
		
		if (ip_Addr.type == IPADDR_TYPE_V4)
		{
			struct sockaddr_in *destAddr = (struct sockaddr_in *)&addr ;
			destAddr->sin_addr.s_addr = ip_Addr.u_addr.ip4.addr;
			destAddr->sin_family = AF_INET;
			destAddr->sin_port = htons(port);
		}
		if (ip_Addr.type == IPADDR_TYPE_V6)
		{
			struct sockaddr_in6 *destAddr = (struct sockaddr_in6 *)&addr ;
			destAddr->sin6_addr.un.u32_addr[0] = ip_Addr.u_addr.ip6.addr[0];
			destAddr->sin6_addr.un.u32_addr[1] = ip_Addr.u_addr.ip6.addr[1];
			destAddr->sin6_addr.un.u32_addr[2] = ip_Addr.u_addr.ip6.addr[2];
			destAddr->sin6_addr.un.u32_addr[3] = ip_Addr.u_addr.ip6.addr[3];
			destAddr->sin6_family = AF_INET6;
			destAddr->sin6_port = htons(port);
		}
	}
};

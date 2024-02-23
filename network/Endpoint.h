#pragma once
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include <string>
#include "IDevice.h"


class Endpoint {
	constexpr static const char* TAG = "Endpoint";
    sockaddr_storage addr; // Large enough for both IPv4 or IPv6
        
public:
    socklen_t Size() const {
        return sizeof(addr);
    }

    const sockaddr* GetSockAddr() const {
        return reinterpret_cast<const sockaddr*>(&addr);
    }
	
	Result SetPort(int port) {
        if (port < 0 || port > 65535) {
            // Invalid port number
            return Result::Error;
        }
        if (addr.ss_family == AF_INET) {
            struct sockaddr_in* ipv4 = reinterpret_cast<struct sockaddr_in*>(&addr);
            ipv4->sin_port = htons(port);
        } else if (addr.ss_family == AF_INET6) {
            struct sockaddr_in6* ipv6 = reinterpret_cast<struct sockaddr_in6*>(&addr);
            ipv6->sin6_port = htons(port);
        } else {
            // Unsupported address family
            return Result::Error;
        }
        return Result::Ok;
    }
    
    Result SetIP(const std::string& ip) {
        if (inet_pton(AF_INET, ip.c_str(), &((struct sockaddr_in*)&addr)->sin_addr) == 1) {
            // IPv4 address
            addr.ss_family = AF_INET;
        } else if (inet_pton(AF_INET6, ip.c_str(), &((struct sockaddr_in6*)&addr)->sin6_addr) == 1) {
            // IPv6 address
            addr.ss_family = AF_INET6;
        } else {
            // Invalid IP address
            return Result::Error;
        }
        return Result::Ok;
    }
    
    Result Set(struct addrinfo* p) {
        if (p == nullptr) {
            // Invalid pointer
            return Result::Error;
        }
        memcpy(&addr, p->ai_addr, p->ai_addrlen);
        return Result::Ok;
    }
	
};


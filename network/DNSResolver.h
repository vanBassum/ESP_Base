#pragma once
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include <string>
#include "Endpoint.h"

class DNSResolver {
	constexpr static const char* TAG = "DNSResolver";
public:
    Result Resolve(std::string host, Endpoint& result) {
        return Resolve(host, 80, result); // Default port 80
    }
    
    Result Resolve(std::string host, int port, Endpoint& result) {
        struct addrinfo hints, *res;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC; // Allow IPv4 or IPv6
        hints.ai_socktype = SOCK_STREAM; // Stream socket (TCP)

        std::string portStr = std::to_string(port);

        int status = getaddrinfo(host.c_str(), portStr.c_str(), &hints, &res);
        if (status != 0) {
            // DNS resolution failed
            return Result::Error;
        }

        // Copy the resolved address to the endpoint
        result.Set(res);

        freeaddrinfo(res);
        return Result::Ok;
    }
};


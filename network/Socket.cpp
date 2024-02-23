#include "Socket.h"

Socket::~Socket() {
    if (handle >= 0) {
        Close();
    }
}

Result Socket::Shutdown(int how) {
    if (handle < 0) {
        ESP_LOGE(TAG, "Socket not initialized");
        return Result::Error;
    }
    if (shutdown(handle, how) == 0) {
        return Result::Ok;
    } else {
        ESP_LOGE(TAG, "Failed to shutdown socket: errno %d, %s", errno, strerror(errno));
        return Result::Error;
    }
}

Result Socket::Close() {
    if (handle < 0) {
        return Result::Ok;  //Already closed
    }
    if (close(handle) == 0) {
        handle = -1;
        return Result::Ok;
    } else {
        ESP_LOGE(TAG, "Failed to close socket: errno %d, %s", errno, strerror(errno));
        return Result::Error;
    }
}

Result Socket::Init(int domain, int type, int protocol) {
    handle = socket(domain, type, protocol);
    if (handle < 0) {
        ESP_LOGE(TAG, "Failed to create socket: errno %d, %s", errno, strerror(errno));
        return Result::Error;
    }
    return Result::Ok;
}

Result Socket::SetKeepAlive(int enable, int idle, int interval, int count) {
    if (handle < 0) {
        ESP_LOGE(TAG, "Socket not initialized");
        return Result::Error;
    }
    if (setsockopt(handle, SOL_SOCKET, SO_KEEPALIVE, &enable, sizeof(int)) != 0 ||
        setsockopt(handle, IPPROTO_TCP, TCP_KEEPIDLE, &idle, sizeof(int)) != 0 ||
        setsockopt(handle, IPPROTO_TCP, TCP_KEEPINTVL, &interval, sizeof(int)) != 0 ||
        setsockopt(handle, IPPROTO_TCP, TCP_KEEPCNT, &count, sizeof(int)) != 0) {
        ESP_LOGE(TAG, "Failed to set keep alive options: errno %d, %s", errno, strerror(errno));
        return Result::Error;
    }
    return Result::Ok;
}

Result Socket::SetTimeout(struct timeval* timeout) {
    if (handle < 0) {
        ESP_LOGE(TAG, "Socket not initialized");
        return Result::Error;
    }
    if (setsockopt(handle, SOL_SOCKET, SO_RCVTIMEO, timeout, sizeof(struct timeval)) != 0) {
        ESP_LOGE(TAG, "Failed to set timeout options: errno %d, %s", errno, strerror(errno));
        return Result::Error;
    }
    return Result::Ok;
}

Result Socket::Receive(uint8_t* buffer, size_t size, size_t* read, int flags) {
    if(read != 0)
        *read = 0;
    if (handle < 0) {
        ESP_LOGE(TAG, "Socket not initialized");
        return Result::Error;
    }
    int result = recv(handle, buffer, size, flags);
    if (result <= 0) {
        ESP_LOGE(TAG, "Failed to receive data: errno %d, %s", errno, strerror(errno));
        return Result::Error;
    }
    if(read != 0)
        *read = result;
    return Result::Ok;
}

Result Socket::Send(const uint8_t* buffer, size_t size, size_t* bytesSend, int flags) {
    if(bytesSend != 0)
        *bytesSend = 0;
    if (handle < 0) {
        ESP_LOGE(TAG, "Socket not initialized");
        return Result::Error;
    }
    int result = send(handle, buffer, size, flags);
    if (result <= 0) {
        ESP_LOGE(TAG, "Failed to send data: errno %d, %s", errno, strerror(errno));
        return Result::Error;
    }
    if(bytesSend != 0)
        *bytesSend = 0;
    return Result::Ok;
}

Result Socket::SendTo(Endpoint& endpoint, const uint8_t* buffer, size_t size, size_t* bytesSend, int flags) {
    if(bytesSend != 0)
        *bytesSend = 0;
    if (handle < 0) {
        ESP_LOGE(TAG, "Socket not initialized");
        return Result::Error;
    }
    int result = sendto(handle, buffer, size, flags, endpoint.GetSockAddr(), endpoint.Size());
    if (result <= 0) {
        ESP_LOGE(TAG, "Failed to send data to endpoint: errno %d, %s", errno, strerror(errno));
        return Result::Error;
    }
    if(bytesSend != 0)
        *bytesSend = 0;
    return Result::Ok;
}

Result Socket::Connect(Endpoint& endpoint) {
    if (handle < 0) {
        ESP_LOGE(TAG, "Socket not initialized");
        return Result::Error;
    }
    if (connect(handle, endpoint.GetSockAddr(), endpoint.Size()) != 0) {
        ESP_LOGE(TAG, "Failed to connect to endpoint: errno %d, %s", errno, strerror(errno));
        return Result::Error;
    }
    return Result::Ok;
}

Result Socket::Bind(Endpoint& endpoint) {
    if (handle < 0) {
        ESP_LOGE(TAG, "Socket not initialized");
        return Result::Error;
    }
    if (bind(handle, endpoint.GetSockAddr(), endpoint.Size()) != 0) {
        ESP_LOGE(TAG, "Failed to bind to endpoint: errno %d, %s", errno, strerror(errno));
        return Result::Error;
    }
    return Result::Ok;
}

Result Socket::Accept(std::shared_ptr<Socket>& socket) {
    if (handle < 0) {
        ESP_LOGE(TAG, "Socket not initialized");
        return Result::Error;
    }
    struct sockaddr_storage source_addr; // Large enough for both IPv4 or IPv6
    socklen_t addr_len = sizeof(source_addr);
    int sock = accept(handle, (struct sockaddr *)&source_addr, &addr_len);
    if (sock < 0) {
        ESP_LOGE(TAG, "Failed to accept connection: errno %d, %s", errno, strerror(errno));
        return Result::Error;
    }
    socket = std::make_shared<Socket>();
    socket->handle = sock;
    return Result::Ok;
}

Result Socket::Listen(int backlog) {
    if (handle < 0) {
        ESP_LOGE(TAG, "Socket not initialized");
        return Result::Error;
    }
    if (listen(handle, backlog) != 0) {
        ESP_LOGE(TAG, "Failed to listen: errno %d, %s", errno, strerror(errno));
        return Result::Error;
    }
    return Result::Ok;
}

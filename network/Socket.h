#pragma once
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "esp_log.h"
#include "Endpoint.h"
#include <memory>

class Socket
{
	int handle = -1;
	constexpr static const char* TAG = "Socket";
public:
	~Socket();
	///0	Further receives are disallowed
	///1	Further sends are disallowed
	///2	Further sends and receives are disallowed(like close())
	///		https://beej.us/guide/bgnet/html/#close-and-shutdownget-outta-my-face
	Result Shutdown(int how);
	Result Close();
	Result Init(int domain, int type, int protocol);	//	AF_INET, SOCK_STREAM, IPPROTO_IP
	Result InitTCP() { return Init(AF_INET, SOCK_STREAM, IPPROTO_IP); };
	Result InitUDP() { return Init(AF_INET, SOCK_DGRAM, IPPROTO_IP); };
	Result SetKeepAlive(int enable, int idle, int interval, int count);
	Result SetTimeout(struct timeval* timeout);
	Result Receive(uint8_t* buffer, size_t size, size_t* bytesRead, int flags = 0);
	Result Send(const uint8_t* buffer, size_t size, size_t* bytesSend, int flags = 0);
	Result SendTo(Endpoint& endpoint, const uint8_t* buffer, size_t bytesSend, size_t* send, int flags = 0);
	Result Connect(Endpoint& endpoint);
	Result Bind(Endpoint& endpoint);
	Result Accept(std::shared_ptr<Socket>& socket);
	Result Listen(int backlog);
	Result SetupForNonblocking();
	Result WaitForData(struct timeval* timeout);
};




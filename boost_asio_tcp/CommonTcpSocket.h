#pragma once

#include "ISocketServer.h"
#include "tcp_server.h"


template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class CommonTcpSocket : public ISocketServer
{
	public:
		CommonTcpSocket(unsigned int port);
		virtual void handleAcceptedConnection();
		virtual void handleReadFinished(std::size_t bytes_transferred);
	private:
		tcp_server m_server;
		static unsigned int const MAX_MSG_SIZE = 32768;
		char m_message[MAX_MSG_SIZE];
		char incomingData[MAX_MSG_SIZE];

};
#pragma once

#include <cstddef>

class ISocketServer
{
	public:
		virtual void handleAcceptedConnection() = 0;
		virtual void handleReadFinished(std::size_t bytes_transferred) = 0;
};
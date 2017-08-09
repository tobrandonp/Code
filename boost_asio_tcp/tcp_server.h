#pragma once

#include "ISocketServer.h"
#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/asio/placeholders.hpp>
#include <string>
#include <ctime>
#include <iostream>

using boost::asio::ip::tcp;

class tcp_server
{
	public:
		tcp_server(unsigned int port, std::unique_ptr<ISocketServer> socketServerInterface);
		tcp::socket& getSocket(){return m_socket;}
	protected:
		void done_writing(const boost::system::error_code &error, std::size_t bytes_transferred);
		void handle_accept(const boost::system::error_code& error);
		void read_handler(const boost::system::error_code &error, std::size_t bytes_transferred);


		boost::asio::io_service m_ioService;
		tcp::socket m_socket;
		tcp::acceptor m_acceptor;
		boost::thread m_thread;
		std::unique_ptr<ISocketServer> m_handler;

	private:
		void run();
		void waitOnConnection();

};
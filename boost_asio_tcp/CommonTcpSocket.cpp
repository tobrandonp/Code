#include "CommonTcpSocket.h"

CommonTcpSocket::CommonTcpSocket(unsigned int port) : 
	m_server(port, make_unique<CommonTcpSocket>(this))
{

}

void CommonTcpSocket::handleAcceptedConnection()
{
	m_server.getSocket().async_read_some(boost::asio::buffer(incomingData, 5),
      boost::bind(&tcp_server::read_handler, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));

	std::cout<<incomingData[0] << incomingData[1] << incomingData[2] << incomingData[3] << incomingData[4] << std::endl;
}

void CommonTcpSocket::handleReadFinished(std::size_t bytes_transferred)
{
	std::cout<<"Read finished handling..."<<std::endl;
}
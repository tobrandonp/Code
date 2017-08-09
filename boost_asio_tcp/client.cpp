#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/asio/placeholders.hpp>
#include <array>
#include <string>
#include <iostream>

using namespace boost::asio;
using namespace boost::asio::ip;


class ClientTcp
{

  public:

   ClientTcp(): 
     m_ioservice(),
     m_resolv(m_ioservice),
     m_socket(m_ioservice),
     m_thread(boost::bind(&ClientTcp::run, this))
   {
     bytes[0] = 'z';
     bytes[1] = 'y';
     bytes[2] = 'x';
     bytes[3] = 'w';
     bytes[4] = 'v';
   }


void run()
{
  //tcp::resolver::query q{"localhost", "2014"};

  //m_resolv.async_resolve(q, boost::bind(&ClientTcp::resolve_handler, this, 
                // boost::asio::placeholders::error, boost::asio::placeholders::iterator));

  //m_ioservice.run();
  sleep(100);
}


void write_handler(const boost::system::error_code &error,
  std::size_t bytes_transferred)
{

  if (!error)
  {
   // std::cout.write(bytes.data(), bytes_transferred);
   std::cout<<"Just sent " << bytes_transferred << " bytes"<<std::endl;

  }
}

void connect_handler(const boost::system::error_code &error)
{
  if (!error)
  {

    boost::asio::async_write(m_socket, boost::asio::buffer(bytes, max_length),
        boost::bind(&ClientTcp::write_handler, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }
}

void resolve_handler(const boost::system::error_code &error,
  tcp::resolver::iterator it)
{
  if (!error)
  {
     m_socket.async_connect(*it, boost::bind(&ClientTcp::connect_handler, this, 
                boost::asio::placeholders::error));
  }
}
      void sendMessage_connect_handler(const boost::system::error_code &error, 
                    char* msg, unsigned int length)
      {
        if(!error)
        {
          std::cout<<"trying to send msvg"<<std::endl;
          boost::asio::async_write(m_socket, boost::asio::buffer(msg, length),
                boost::bind(&ClientTcp::write_handler, this,
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
        }
      }


      void sendMessage_resolve_handler(const boost::system::error_code &error, tcp::resolver::iterator it,
                char* msg, unsigned int length)
      {
        if (!error)
        {
           m_socket.async_connect(*it, boost::bind(&ClientTcp::sendMessage_connect_handler, this, 
                      boost::asio::placeholders::error, msg, length));
        }
      }

      void sendMessage( char* msg , unsigned int length)
      {
        m_socket.close();
        m_ioservice.reset();
        tcp::resolver::query q{"localhost", "2014"};

        m_resolv.async_resolve(q, boost::bind(&ClientTcp::sendMessage_resolve_handler, this, 
                      boost::asio::placeholders::error, boost::asio::placeholders::iterator, msg, length));

        m_ioservice.run();
      }



  private:
   io_service m_ioservice;
   tcp::resolver m_resolv;
   tcp::socket m_socket;
   boost::thread m_thread;
   static const unsigned int max_length = 32768;
   char bytes[max_length];
};

int main()
{
  ClientTcp ct;
  const char* msg = "abcde";
  sleep(2);
  ct.sendMessage((char*)msg, 5);
  sleep(1);
  ct.sendMessage((char*)msg, 5);
  sleep(1);
  ct.sendMessage((char*)msg, 5);
  sleep(100);
  
}

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

void log(const std::string msg)
{
 std::cout<<msg<<std::endl;
}


using boost::asio::ip::tcp;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}


class tcp_server
{
public:
  tcp_server(unsigned int port)
    : m_ioService(),
      m_socket(m_ioService),
      m_acceptor(m_ioService, tcp::endpoint(tcp::v4(), port)),
      m_thread(boost::bind(&tcp_server::run, this))
  {
     m_message[0] = 0;
     m_message[1] = 1;
     m_message[2] = 2;
     m_message[3] = 3;
     m_message[4] = 4;
  }

private:

  void run()
  {
      waitOnConnection();

      try
      {
        m_ioService.run();
      }
      catch(const std::exception& ex)
      {
        std::cout<<"Caught Exception: "<< ex.what()<<std::endl;
      }
  }

  void waitOnConnection()
  {
    m_acceptor.async_accept(m_socket,
          boost::bind(&tcp_server::handle_accept, this,
            boost::asio::placeholders::error));
  }

  void done_writing(const boost::system::error_code &error, std::size_t bytes_transferred)
  {
    if(!error)
    {
      m_acceptor.async_accept(m_socket,
            boost::bind(&tcp_server::handle_accept, this,
              boost::asio::placeholders::error));
    }
    else
    {
      std::cout<<"done_writing error: "<< error.message()<<std::endl;
    }
   
  }

  void handle_accept( const boost::system::error_code& error)
  {
    std::cout<<"--0"<<std::endl;
    std::cout<<"connection accepted!"<<std::endl;
    if (!error)
    {

      m_socket.async_read_some(boost::asio::buffer(incomingData, 5),
        boost::bind(&tcp_server::read_handler, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
      std::cout<<"0: "<< incomingData[0] <<std::endl
               <<"1: "<< incomingData[1] <<std::endl
               <<"2: "<< incomingData[2] <<std::endl
               <<"3: "<< incomingData[3] <<std::endl
               <<"4: "<< incomingData[4] <<std::endl
               <<std::endl;

    }
    else
    {
      std::cout<<"handle_accept error: "<< error.message()<<std::endl;
    }
  }

  void read_handler(const boost::system::error_code &error, std::size_t bytes_transferred)
  {
    if (!error)
    {
      // Close previous connection, since we need a new socket
      m_socket.close();
      waitOnConnection();

    }
    else
    {
      std::cout<<"read_handler error: "<< error.message()<<std::endl;
    }
  }

  boost::asio::io_service m_ioService;
  tcp::socket m_socket;
  tcp::acceptor m_acceptor;
  boost::thread m_thread;
  static unsigned int const MAX_MSG_SIZE = 32768;
  char m_message[MAX_MSG_SIZE];
  char incomingData[MAX_MSG_SIZE];
};

int main()
{
  try
  {
    tcp_server server(2014);
    sleep(200);
    
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}

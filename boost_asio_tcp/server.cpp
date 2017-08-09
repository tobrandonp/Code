#include "CommonTcpSocket.h"

int main()
{
  try
  {
    CommonTcpSocket server(2014);
    sleep(200);
    
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}

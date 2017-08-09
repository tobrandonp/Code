client: client.cpp
	g++ -std=c++0x client.cpp -o client -L/usr/local/lib/ -lboost_thread -lboost_system -Wl,-rpath,/usr/local/lib -lpthread

server: tcp_server.cpp
	g++ -std=c++0x tcp_server.cpp -o server -L/usr/local/lib/ -lboost_thread -lboost_system -Wl,-rpath,/usr/local/lib -lpthread

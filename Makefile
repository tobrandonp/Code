main: main.o
	g++ -std=c++0x main.cpp -o main -L/usr/local/lib/ -lboost_thread -lboost_system -lboost_filesystem -Wl,-rpath,/usr/local/lib -lpthread


clean: 
	-rm -f main main.o
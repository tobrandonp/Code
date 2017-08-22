#include "A.h"
#include "B.h"
#include <iostream>

int main()
{
	A a;
	a.doStuff();
	std::cout<<a.getB()<<std::endl;

    std::cout<<"done you"<<std::endl;

	B b;
	b.doStuff();
}
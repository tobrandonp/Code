#pragma once

class A
{
	public:
		A(){m_b= 2;}
	  void doStuff();
      int getB(){return m_b;}

	  int m_a;
	  int m_b;
};
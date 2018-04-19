#include <iostream>
#include "Static_Polymorphism.h"

struct NON_TYPE{};
int main()
{

	//BulkInserter<GrandparentTwoParents<int, double,char> > bi;

	
	BulkInserter<Grandparent<int, NON_TYPE, NON_TYPE> > gpBulkInserter;
	int val = 3;
	gpBulkInserter.addGrandparentRow(val);

}
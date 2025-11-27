#ifndef _MYTREE.H
#define _MYTREE .H
#include <btree.h>
#include <iostream.h>

class mydata : public btree
{
public:

	int info;

public:

	mydata();
	mydata(int num);
	~mydata();
	void print();
	friend int condition(void *v1, void *v2);
	friend ostream &operator<<(ostream &out, mydata &t);
	friend istream &operator>>(istream &in, mydata &t);
};
#endif

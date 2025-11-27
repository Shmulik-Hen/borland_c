#ifndef _MYCLASS1_H
#define _MYCLASS1_H
#include "tree.h"
#include "types.def"

class myclass : public treenode
{
	int num;
	char *name;

public:

	myclass();
	~myclass();
	myclass(int, char *);
	myclass *find(char *);
	friend int my_comp(const void *);
	friend void printall(myclass *);
	void print();
	void read();
};
#endif

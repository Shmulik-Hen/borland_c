#ifndef _MYCLASS_H
#define _MYCLASS_H
#include "queue.cpp"
#include <stddef.h>

class myclass
{
	int num;

public:

	myclass *next;
	myclass() {};
	myclass(int n)
	{
		num = n;
		next = NULL;
	};
	~myclass() {};
	friend myclass *merge(myclass *, myclass *);
	friend myclass *merge_sort(queue<myclass> &);
	void print();
};
#endif

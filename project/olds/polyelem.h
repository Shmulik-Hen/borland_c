#ifndef _POLYELEM_H
#define _POLYELEM_H
#include "queue.cpp"
#include "unit.h"
#include "vector.h"
#include "matrix.h"
#include "polygon.h"

class polyelem
{
	static char *memory;
	static char *current;

public:

	matrix mat;
	polygon *poly;
	char color;
	unit depth;
	polyelem *next;
	polyelem *nextq;
	polyelem()
	{
		next = NULL;
		nextq = NULL;
	};
	~polyelem() {};
	void *operator new(size_t);
	friend void freemem();
	friend polyelem *merge(polyelem *, polyelem *);
	friend polyelem *merge_sort(queue<polyelem> &);
	void print();
	void show();
};
#endif

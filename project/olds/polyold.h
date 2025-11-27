#ifndef _POLYELEM_H
#define _POLYELEM_H
#include "queue.h"
#include "unit.h"
#include "vector.h"
#include "matrix.h"
#include "polygon.h"

class polyelem : public queue
{
	static far char memory[64000];
	static far char *current;

public:

	matrix mat;
	polygon *poly;
	char color;
	unit depth;
	polyelem *next;
	polyelem();
	~polyelem();
	void *operator new(size_t);
	friend void freemem();
	friend polyelem *merge(polyelem *, polyelem *);
	friend polyelem *merge_sort();
	void print();
	void show();
};
#endif

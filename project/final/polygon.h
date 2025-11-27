#ifndef _POLYGON_H
#define _POLYGON_H
#include "vector.h"
#include "list.cpp"
#include "types.def"

class polygon
{
public:

	NAME name;
	friend class polyelem;
	int force;
	char color;
	vector fill;
	vector normal;
	list<vector> points;
	polygon() {};
	~polygon() {};
	vector find_fill();
	friend polygon *find_poly(list<polygon> &, char *);
	friend int poly_comp(const void *);
	void read(ifstream &);
	void *operator new(size_t);
};
#endif

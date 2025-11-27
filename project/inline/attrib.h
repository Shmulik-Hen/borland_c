#ifndef _ATTRIB_H
#define _ATTRIB_H
#include "unit.h"
#include <iostream.h>

class matrix;
class attrib
{
	unit deg_x, deg_y, deg_z;
	unit off_x, off_y, off_z;
	unit zoom;

public:

	attrib() {};
	~attrib() {};
	attrib(unit, unit, unit, unit, unit, unit, unit);
	attrib &operator+=(const attrib &);
	friend void prep_gen_mat(matrix &, const attrib &);
	friend void prep_rot_mat(matrix &, const attrib &);
	void read(ifstream &);
};
#endif

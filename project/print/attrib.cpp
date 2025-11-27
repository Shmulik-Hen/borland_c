/**************************************************************************
 * SUBJECT:    FLIGHT SIMULATOR.                                           *
 *                                                                         *
 * TITLE:      GRADUATION PROJECT.                                         *
 *                                                                         *
 * FILE NAME:  attrib.cpp                                                  *
 *                                                                         *
 * PURPOSE:    function definitions for class ATTRIB.                      *
 **************************************************************************/

#include "attrib.h"

/* default constructor */

attrib::attrib()
{
}

/* default destructor */

attrib::~attrib()
{
}

/* constructor with parameters */

attrib::attrib(unit dx, unit dy, unit dz, unit ox, unit oy, unit oz, unit z)
{
	deg_x = dx;
	deg_y = dy;
	deg_z = dz;
	off_x = ox;
	off_y = oy;
	off_z = oz;
	zoom = z;
}

/* operator overloading for addition with asignment */

attrib &attrib::operator+=(const attrib &a)
{
	deg_x += a.deg_x;
	deg_y += a.deg_y;
	deg_z += a.deg_z;
	off_x += a.off_x;
	off_y += a.off_y;
	off_z += a.off_z;
	zoom *= a.zoom;
	return *this;
}

/* function for initializing with data from file */

void attrib::read(ifstream &f)
{
	deg_x.read(f);
	deg_y.read(f);
	deg_z.read(f);
	off_x.read(f);
	off_y.read(f);
	off_z.read(f);
	zoom.read(f);
}

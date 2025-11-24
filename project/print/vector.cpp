/**************************************************************************
* SUBJECT:    FLIGHT SIMULATOR.                                           *
*                                                                         *
* TITLE:      GRADUATION PROJECT.                                         *
*                                                                         *
* FILE NAME:  vector.cpp                                                  *
*                                                                         *
* PURPOSE:    function definitions for class VECTOR.                      *
**************************************************************************/

#include "vector.h"

/*default constructor */

vector::vector()
{
}

/* default destructor */

vector::~vector()
{
}

/* constructor eith parameters */

vector::vector(unit x,unit y,unit z)
{
 coord[X]=x;
 coord[Y]=y;
 coord[Z]=z;
}

/* operator overloading for addition */

vector vector::operator+(const vector& v)
{
 return vector(coord[X]+v.coord[X],coord[Y]+v.coord[Y],coord[Z]+v.coord[Z]);
}

/* operator overloading for subtraction */

vector vector::operator-(const vector& v)
{
 return vector(coord[X]-v.coord[X],coord[Y]-v.coord[Y],coord[Z]-v.coord[Z]);
}

/*operator overloading for scalar multiplication*/

unit vector::operator*(const vector& v)
{
 return unit(coord[X]*v.coord[X]+coord[Y]*v.coord[Y]+coord[Z]*v.coord[Z]);
}

/* operator overloading for addition with assignment */

vector& vector::operator+=(const vector& v)
{
 coord[X]+=v.coord[X];
 coord[Y]+=v.coord[Y];
 coord[Z]+=v.coord[Z];
 return *this;
}

/* operator overloading for subtraction with assignment */

vector& vector::operator-=(const vector& v)
{
 coord[X]-=v.coord[X];
 coord[Y]-=v.coord[Y];
 coord[Z]-=v.coord[Z];
 return *this;
}

/* function for performing prespective projections */

vector project(const vector& p,const vector& v)
{
 vector temp;
 if(abs(v.coord[Z]-p.coord[Z]) >= UNIT)
  {
   temp.coord[X]=((p.coord[X]-v.coord[X])/(v.coord[Z]-p.coord[Z]))*v.coord[Z];
   temp.coord[Y]=((p.coord[Y]-v.coord[Y])/(v.coord[Z]-p.coord[Z]))*v.coord[Z];
  }
 else
  {
   temp.coord[X]=((p.coord[X]-v.coord[X])*v.coord[Z])/(v.coord[Z]-p.coord[Z]+UNIT);
   temp.coord[Y]=((p.coord[Y]-v.coord[Y])*v.coord[Z])/(v.coord[Z]-p.coord[Z]+UNIT);
  }
 return temp;
}

/* function for initializing with data from file */

void vector::read(ifstream& f)
{
 coord[X].read(f);
 coord[Y].read(f);
 coord[Z].read(f);
}

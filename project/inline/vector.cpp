#include "vector.h"

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

void vector::read(ifstream& f)
{
 coord[X].read(f);
 coord[Y].read(f);
 coord[Z].read(f);
}

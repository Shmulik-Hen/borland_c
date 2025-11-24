#ifndef _ATTRIB_H
#define _ATTRIB_H
#include "unit.h"
#include <iostream.h>

class matrix;
class attrib
      {
       public:
	unit deg_x,deg_y,deg_z;
	unit off_x,off_y,off_z;
	unit zoom;
	attrib(){};
	~attrib(){};
	attrib::attrib(unit dx,unit dy,unit dz,unit ox,unit oy,unit oz,unit z)
	  {
	   deg_x=dx;
	   deg_y=dy;
	   deg_z=dz;
	   off_x=ox;
	   off_y=oy;
	   off_z=oz;
	   zoom=z;
	  }
	attrib& attrib::operator+=(const attrib& a)
	  {
	   deg_x+=a.deg_x;
	   deg_y+=a.deg_y;
	   deg_z+=a.deg_z;
	   off_x+=a.off_x;
	   off_y+=a.off_y;
	   off_z+=a.off_z;
	   zoom*=a.zoom;
	   return *this;
	  }
	//attrib(unit,unit,unit,unit,unit,unit,unit);
	//attrib& operator+=(const attrib&);
	friend void prep_gen_mat(matrix&,const attrib&);
	friend void prep_rot_mat(matrix&,const attrib&);
	void read(ifstream&);
      };
#endif

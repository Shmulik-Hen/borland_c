#ifndef _VECTOR_H
#define _VECTOR_H
#include "unit.h"

enum coords {X,Y,Z};
class matrix;
class vector
      {
       public:
	unit coord[3];
	vector(){};
	~vector(){};
	vector(unit x,unit y,unit z){coord[X]=x;coord[Y]=y;coord[Z]=z;};
	vector operator+(const vector& v) {return vector(coord[X]+v.coord[X],coord[Y]+v.coord[Y],coord[Z]+v.coord[Z]);};
	vector operator-(const vector& v) {return vector(coord[X]-v.coord[X],coord[Y]-v.coord[Y],coord[Z]-v.coord[Z]);};
	vector& operator+=(const vector& v) {coord[X]+=v.coord[X];coord[Y]+=v.coord[Y];coord[Z]+=v.coord[Z];return *this;};
	vector& operator-=(const vector& v) {coord[X]-=v.coord[X];coord[Y]-=v.coord[Y];coord[Z]-=v.coord[Z];return *this;};
	unit operator*(const vector& v) {return unit(coord[X]*v.coord[X]+coord[Y]*v.coord[Y]+coord[Z]*v.coord[Z]);};
	friend vector operator*(const matrix&,const vector&);
	friend vector project(const vector&,const vector&);
	void read(ifstream&);
      };
#endif

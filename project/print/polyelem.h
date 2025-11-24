/**************************************************************************
* SUBJECT:    FLIGHT SIMULATOR.                                           *
*                                                                         *
* TITLE:      GRADUATION PROJECT.                                         *
*                                                                         *
* FILE NAME:  polyelem.h                                                  *
*                                                                         *
* PURPOSE:    function declarations for class POLYELEM.                   *
**************************************************************************/
#ifndef _POLYELEM_H
#define _POLYELEM_H
#include "queue.h"
#include "unit.h"
#include "vector.h"
#include "matrix.h"
#include "polygon.h"

class polyelem:public queue
      {
       public:
	matrix mat;
	polygon* poly;
	char color;
	unit depth;
	polyelem* next;
	polyelem();
	~polyelem();
	friend polyelem* merge(polyelem*,polyelem*);
	friend polyelem* merge_sort();
	void show();
	void* operator new(size_t);
	friend void pe_free();
      };
#endif

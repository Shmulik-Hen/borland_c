/**************************************************************************
* SUBJECT:    FLIGHT SIMULATOR.                                           *
*                                                                         *
* TITLE:      GRADUATION PROJECT.                                         *
*                                                                         *
* FILE NAME:  queue.h                                                     *
*                                                                         *
* PURPOSE:    function declarations for class QUEUE.                      *
**************************************************************************/
#ifndef _QUEUE_H
#define _QUEUE_H
#include <stddef.h>

class queue
      {
	static queue* head;
	static queue* tail;
	queue* nextq;
       public:
	queue();
	~queue();
	void push();
	friend queue* pop();
      };
#endif

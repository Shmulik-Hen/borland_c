/**************************************************************************
* SUBJECT:    FLIGHT SIMULATOR.                                           *
*                                                                         *
* TITLE:      GRADUATION PROJECT.                                         *
*                                                                         *
* FILE NAME:  queue.cpp                                                   *
*                                                                         *
* PURPOSE:    function definitions for class QUEUE.                       *
**************************************************************************/

#include "queue.h"

/* static pointers initializing */

queue* queue::head=NULL;
queue* queue::tail=NULL;

/*default constructor */

queue::queue()
{
 nextq=NULL;
}

/* default destructor */

queue::~queue()
{
}

/* function for adding an item to tail of queue */

void queue::push()
{
 if(!tail)
    tail=head=this;
 else
   {
    tail->nextq=this;
    tail=tail->nextq;
   }
}

/* function for removing an item from head of queue */

queue* pop()
{
 if(!queue::head) return NULL;
 queue* temp=queue::head;
 queue::head=queue::head->nextq;
 temp->nextq=NULL;
 if(!queue::head)
   queue::tail=NULL;
 return temp;
}

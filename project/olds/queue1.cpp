#include "queue.h"
#include "types.def"
#include "utils.h"
#include <stddef.h>

template<class T>
queue<T>::queue()
{
 head=tail=NULL;
}

template<class T>
queue<T>::~queue()
{
}

template<class T>
void queue<T>::push(T* newitem)
{
 if(!tail)
   head=tail=newitem;
 else{
      tail->nextq=newitem;
      tail=tail->nextq;
     }
}

template<class T>
T* queue<T>::pop()
{
 if(!head) return NULL;
 T* temp=head;
 head=head->nextq;
 if(!head)
   tail=head;
 return temp;
}

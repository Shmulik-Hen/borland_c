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
 item* temp;
 while(head)
   {
    temp=head;
    head=head->next;
    if(temp->data)
       delete temp->data;
    delete temp;
   }
}

template<class T>
void queue<T>::push(T* newitem)
{
 item* temp=new item;
 if(!temp) error("not enough memory in queue::push()");
 temp->data=newitem;
 temp->next=NULL;
 if(!tail)
   tail=temp;
 else{
      tail->next=temp;
      tail=tail->next;
     }
 if(!head)
   head=temp;
}

template<class T>
T* queue<T>::pop()
{
 if(empty()) return NULL;
 item* temp=head;
 T* temp2=temp->data;
 head=head->next;
 if(!head)
   tail=NULL;
 delete temp;
 return(temp2);
}

template<class T>
int queue<T>::empty()
{
 return (head==NULL);
}

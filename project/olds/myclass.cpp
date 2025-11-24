#include "myclass.h"

void myclass::print()
{
 cout<<num<<" ";
}

myclass* merge(myclass* l1,myclass* l2)
{
 myclass *first,*temp,*last=NULL;

 while(l1 && l2)
   {
    if(l1->num > l2->num)
      {
       temp=l1;
       l1=l1->next;
      }
    else
      {
       temp=l2;
       l2=l2->next;
      }
    if(!last)
      first=temp;
    else
      last->next=temp;
    last=temp;
   }
 if(last)
   if(l1)
     last->next=l1;
   else
     last->next=l2;
 else
  if(l1)
    first=l1;
  else
    first=l2;
 return first;
}

myclass* merge_sort(queue<myclass>& q)
{
 myclass *l1,*l2,*l3;
 l1=q.pop();
 l2=q.pop();
 while(l2)
   {
    l3=merge(l1,l2);
    q.push(l3);
    l1=q.pop();
    l2=q.pop();
   }
 return l1;
}

#include "..\\files\\binfinal.cpp"
#include <string.h>

class worker:public btree
{
 public:
   char name[20];
 public:
   worker();
   friend int condition(void *w1,void *w2);
   void read();
   friend void print(worker *h);
};

int condition(void *e1,void *e2)
{
 worker *w1,*w2;
 w1=(worker *)e1;
 w2=(worker *)e2;
 return(strcmp(w1->name,w2->name));
}

worker::worker():btree()
{
 cond=condition;
}

void print(worker *h)
{
 if (h!=NULL)
    {
     print((worker *)h->left);
     cout<<h->count<<" "<<h->name<<endl;
     print((worker *)h->right);
    }
}

void worker::read()
{
 cout<<"Enter name"<<endl;
 cin>>name;
}

void main()
{
 worker *head,*ptr;
 head=NULL;
 ptr=new worker();
 ptr->read();
 while ((strcmp(ptr->name,"quit")))
       {
	ptr->addtree(head);
	if (head==NULL)
	   head=ptr;
	ptr=new worker();
	ptr->read();
       }
 print(head);
}
#include "myclass1.h"
#include <conio.h>

void main()
{
 myclass* root=NULL,*p1,*p2;
 clrscr();
 p1=new myclass;  //a
 p1->read();
 root=p1;

 p1=new myclass;     //b
 p1->read();
 p2=root->find("a");
 p1->addnode(p2);

 p1=new myclass;     //c
 p1->read();
 p2=root->find("a");
 p1->addnode(p2);

 p1=new myclass;     //d
 p1->read();
 p2=root->find("b");
 p1->addnode(p2);

 p1=new myclass;        //e
 p1->read();
 p2=root->find("b");
 p1->addnode(p2);

 p1=new myclass;        //f
 p1->read();
 p2=root->find("c");
 p1->addnode(p2);

 p1=new myclass;        //g
 p1->read();
 p2=root->find("c");
 p1->addnode(p2);

 p1=new myclass;        //h
 p1->read();
 p2=root->find("g");
 p1->addnode(p2);

 p1=new myclass;        //i
 p1->read();
 p2=root->find("f");
 p1->addnode(p2);

 p1=new myclass;        //j
 p1->read();
 p2=root->find("e");
 p1->addnode(p2);

 p1=new myclass;        //k
 p1->read();
 p2=root->find("d");
 p1->addnode(p2);

 clrscr();
 printall(root);
}

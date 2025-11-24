#include "tree.cpp"
#include <string.h>
class names:public tree
{
 public:
 char name[80];
 public:
 names(const char *m_name,int id);
 friend int condition(void *n1,void *n2);
 friend void print(names *h);
 void read();
};

names::names(const char *m_name,int id):tree(condition)
{
 strcpy(name,m_name);
}

void names::read()
{
 cout<<"Enter name"<<endl;
 cin>>name;
}
int condition(void *n1,void *n2)
{
 names *l_n1,*l_n2;
 l_n1=(names *)n1;
 l_n2=(names *)n2;
 return(strcmp(l_n1->name,l_n2->name));
}

void print(names *h)
{
}

names h("ROOT"),*p,*s;
void main()
{
 int id=0;

 s=&h;
 p=new names("");
 p->read();
 while (strcmp(p->name,"quit"))
       {
	p->addtree(s);
	p=new names("Stam");
	p->read();
	s=new names("Stam");
	cout<<"Search what?"<<endl;
	s->read();
	s=(names *)s->search(&h);
       }
 print(&h);
}
/*COMPLEX VERSION 2.0*/
#include<stdio.h>
#include <conio.h>

class complex {
		private:
			int re;
			int im;
		public:
			void rdnum();
			void print();
			void init(int r, int i);
			complex operator+(complex &t);
			complex operator-(complex &t);
			complex operator+=(complex &t);
	      };

void complex::init(int r ,int i)
{
 re=r;
 im=i;
}

void complex::rdnum()
{
 printf("enter real and imag parts ");
 scanf("%d %d",&re,&im);
}
		   
void complex::print()
{
 printf("%d +i%d\n",re,im);
}
		   
complex complex::operator+(complex &t)
{
 complex result;
 result.init(re+t.re, im+t.im);
 return result;
}

complex complex::operator-(complex &t)
{
 complex result;
 result.init(re-t.re, im-t.im);
 return result;
}

complex complex::operator+=(complex &t)
{
 re+=t.re;
 im+=t.im;
 return t;
}


void main()
{ 
 complex a,b,c;

 clrscr();
 a.rdnum();
 b.rdnum();
 c=a+b;
 b+=c;
 a.print();
 b.print();
 c.print();
 getch();
}
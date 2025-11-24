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
			int operator!=(complex &t);
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
 printf("%d,%di\n",re,im);
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

int complex::operator!=(complex &t)
{
 if(re==t.re && im==t.im)
    return 0;
 else
    return 1;
}	



void main()
{ 
 complex a,b,c;

 clrscr();
 a.rdnum();
 b.rdnum();
 c.init(0,0);
 do{
    a+=b;
    a.print();
   }
 while (a!=c);
 getch();
}
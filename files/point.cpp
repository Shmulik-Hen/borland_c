/*POINT VER 1.0*/
#include<stdio.h>
#include<conio.h>
#include<math.h>

class point {
		private:
			int x;
			int y;
		public:
			void rdnum();
			void print();
			void init(int m_x, int m_y);
			point operator+(point &p);
			float operator-(point &p);
			void cast();
	      };

void point::init(int m_x ,int m_y)
{
 x=m_x;
 y=m_y;
}

void point::rdnum()
{
 printf("enter real and imag parts ");
 scanf("%d %d",&x,&y);
}
		   
void point::print()
{
 printf("%d,%di\n",x,y);
}
		   
point point::operator+(point &p)
{
 point result;
 result.init(x+p.x, y+p.y);
 return result;
}

float point::operator-(point &p)
{
 return sqrt( (p.x-x)*(p.x-x) + (p.y-y)*(p.y-y) );
}

void point::cast()
{
 if(x<0)
    x=0;
 if(x>80)
    x=80;
 if(y<0)
    y=0;
 if(y>25)
    y=25;
}

void main()
{ 
 point a,b,c;
 float dist;

 clrscr();
 a.rdnum();
 b.rdnum();
 a.cast();
 b.cast();
 c=a+b;
 dist=b-a;
 c.cast();
 a.print();
 b.print();
 c.print();
 printf("%3.3f",dist);
 getch();
}
/*CIRCLE VER 1.0*/
/*CONSTRUCTOR + INHERITANCE*/
#include<stdio.h>
#include<conio.h>
#include<math.h>

class point {
             protected:
               int x;
               int y;
             public:
               point();
	       point(int m_x, int m_y );
	       void print();
	       double operator-(point &p);
	    };


point::point()
{
 x=y=0;
}
 
point::point(int m_x, int m_y)
{
 x=m_x;
 y=m_y;
 if(x<0)
    x=0;
 if(x>80)
    x=80;
 if(y<0)
    y=0;
 if(y>25)
    y=25;
}

       
void point::print()
{
 printf("pos x %d pos y%d\n",x,y);
}
       

double point::operator-(point &p)
{
 return sqrt( (p.x-x)*(p.x-x) + (p.y-y)*(p.y-y) );
}


class circle:public point
             {
	      int r;
	      public:
		circle();
		circle(int m_x, int m_y, int m_r);
		void print();
		int operator-(circle &c);
	     };
	     
circle::circle():point()                   
{
  r=0;
}

circle::circle(int m_x, int m_y, int m_r):point(m_x, m_y)
{
  r=m_r;
}

void circle::print()
{
  point p;
  printf("center   \n");
  p=point(x,y);
  p.print();
  printf("radius %d\n",r);
}

int circle::operator-(circle &c)
{
 double res;
 res=point(x,y)-point(c.x,c.y);
 if(res>(r+c.r))  
      return 1;
 if(res<(r+c.r))
      return -1;
 if(res==(r+c.r))
      return 0;
}          

void main()
{ 
 circle a,b;
 int x,y,r,res;

 clrscr();
 printf("enter x,y,r for circle 1 ");
 scanf("%d %d %d",&x,&y,&r);
 a=circle(x,y,r);
 printf("enter x,y,r for circle 2 ");
 scanf("%d %d %d",&x,&y,&r);
 b=circle(x,y,r);
 res=a-b;
 switch(res)
       {
	case 0:printf("mashikim");
	       break;
	case 1:printf("hotchim");
	       break;
	case -1:printf("rehokim");
		break;
       }
 getch();
}
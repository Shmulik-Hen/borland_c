#include<stdio.h>
#include<graphics.h>
#include<math.h>

class complex{
	      private:
		      double re;
		      double im;
	      public:
		      complex();
		      complex(double r, double i);
		      complex operator+(complex &c);
		      complex operator*(complex &c);
		      double operator-(complex &c);	
	     };

complex::complex()
{
 re=im=0.0;
}

complex::complex(double r, double i)
{
 re=r;
 im=i;
}

complex complex::operator+(complex &c)
{
 return complex(re+c.re, im+c.im);
}

complex complex::operator*(complex &c)
{
 return complex( (re*c.re - im*c.im) , (re*c.im + im*c.re) );
}

double complex::operator-(complex &c)
{
 return sqrt( (c.re-re)*(c.re-re) + (c.im-im)*(c.im-im) );
}


void main()
{
 complex z,c,o;
 double r,i,rstep,istep;
 int x,y,color,count;
 int gdrive=DETECT,gmode;
 FILE *fp;
 char *filename="c:\\bc\\files\\mandel.dat";

 rstep=4.0/640;
 istep=3.0/480;

 fp=fopen(filename,"w");
 initgraph(&gdrive,&gmode,"c:\\bc\\bgi");

 for(y=0,i=1.5;y<=240;y++,i-=istep)
    for(x=0,r=-2.5;x<=640;x++,r+=rstep)
       {
	z=complex(0.0, 0.0);
	c=complex(r,i);
	for(count=0;count<1000;count++)
	   {
	    z=z*z+c;
	    if( (z-o) > 2.0)
	      break;
	   }
	fprintf(fp,"%d ",count);
	color=count/16;
	putpixel(x,y,color);
       }
 fclose(fp);
 getchar();
}

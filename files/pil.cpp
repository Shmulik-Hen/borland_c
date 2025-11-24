#include<conio.h>
#include<graphics.h>
#include<math.h>
#include<dos.h>
#include<process.h>

char ar[][2]={{-80,23},{-86,47},{-44,47},{-33,36},{-30,40},
	      {50,40},{67,24},{65,5},{44,25},{55,-70},
	      {25,-70},{25,-30},{15,-35},{-27,-35},{-33,-28},
	      {-33,-70},{-57,-70},{-57,-12},{-55,-5},{-63,-5},
	      {-65,-1},{-55,6},{-67,5},{-67,12},{-73,0},
	      {-73,-50},{-70,-55},{-70,-60},{-80,-50}};

char r_ar[29][2];

void rotate(float ang)
{
 int i;
 for(i=0;i<29;i++)
   {
    r_ar[i][0]=ar[i][1]*sin(ang)-ar[i][0]*cos(ang);
    r_ar[i][1]=ar[i][1]*cos(ang)+ar[i][0]*sin(ang);
   }
}

void draw(int x,int y,float xsize,float ysize,int color,float angle)
{
 int i;

 rotate(angle);
 setcolor(color);
 moveto(x-r_ar[0][0]*xsize,y-r_ar[0][1]*ysize);
 for(i=1;i<29;i++)
   lineto(x-r_ar[i][0]*xsize,y-r_ar[i][1]*ysize);
 lineto(x-r_ar[0][0]*xsize,y-r_ar[0][1]*ysize);
}
/*
int Getch(int x,int y,float xsize,float ysize,float f)
{
 char ch;

 ch=getch();
 draw(x,y,xsize,ysize,0,f);
 return ch;
}
*/
void makeellicenter(int x,int y,int *tx,int *ty,float f,int radius)
{
 *tx=x+radius*sin(f);
 *ty=y+radius*cos(f);
}

void main()
{
 int gm,gd=DETECT;
 int x,y,cx,cy,rx,ry,color;
 float f,xsize,ysize;
 char ch;

 initgraph(&gd,&gm,"d:\\borlandc\\bgi");
 x=320;
 y=240;
 f=0;
 color=3;
 setlinestyle(0,0,3);
 for(f=0;!kbhit();f-=0.00015)
   {
    makeellicenter(x,y,&cx,&cy,f,50);
    makeellicenter(x,y,&rx,&ry,f*60,100);
    setcolor(color);
    line(x,y,cx,cy);
    draw(cx,cy,xsize/2,ysize/2,color,f);
    setcolor(color-1);
    line(x,y,rx,ry);
    draw(rx,ry,xsize/2,ysize/2,color-1,f*60);
    delay(40);
    setcolor(0);
    line(x,y,cx,cy);
    line(x,y,rx,ry);
    draw(cx,cy,xsize/2,ysize/2,0,f);
    draw(rx,ry,xsize/2,ysize/2,0,f*60);
   }
}
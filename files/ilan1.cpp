#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <iostream.h>
#include <graphics.h>
#include <conio.h>
#include <ctype.h>

union key{
	  int i;
	  char c[2];
	 };

char *get_string(int x, int y, int len);
void draw_circle();
void draw_malben();
void draw_triangle();
void draw_elipse();
void endprog();

void main()
{
 int gd,gm;
 char choice='1';
 gd=DETECT;
 initgraph(&gd,&gm,"");
 if (graphresult()!=grOk)
    {
     cout << "error in initialising graphics mode\n";
     exit (1);
    }
 else cout << "all is fine\n";

 while(choice != '5')
      {
       cleardevice();
       setfillstyle(1,14);
       bar3d(65,45,480,300,30,1);
       setcolor(0);
       outtextxy (200,100,"- 1");
       outtextxy (200,130,"- 2");
       outtextxy (200,160,"- 3");
       outtextxy (200,190,"- 4");
       outtextxy (200,220,"- 5");
       outtextxy (200,250,":");
       setcolor(15);
       choice=getch();
       switch (choice)
	 {
	  case '1':draw_circle();
		  break;
	  case '2':draw_malben();
		  break;
	  case '3':draw_triangle();
		  break;
	  case '4':draw_elipse();
		  break;
	  case '5':endprog();
		  break;
	  default :break;
	 }
  }
}

char *get_string(int x, int y, int len)
{
 union key k;
 char str[80];
 int j=0;

 k.i=getch();
 while(k.c[0]!='\r' && j<len)
    {
     k.c[1]='\0';
     if(k.c[0]!=0 && isdigit(k.i))
       {
	outtextxy(x,y,k.c);
	str[j++]=k.c[0];
	x+=10;
       }
      k.i=getch();
     }
 str[j]='\0';
 return str;
}

void draw_circle()
{
  int cent_x, cent_y, rad;
  char *str;
  cleardevice();
  setfillstyle(1,13);
  bar3d(65,45,330,90,30,1);
  outtextxy(100,50,": X");
  cent_x=atoi(str=get_string(70,50,3));
  outtextxy(100,60,": Y");
  cent_y=atoi(str=get_string(70,60,3));
  outtextxy(100,70,":");
  rad=atoi(str=get_string(70,70,3));
  cleardevice();
  circle(cent_x,cent_y,rad);
  outtextxy(100,460,"...");
  getch();
}

void draw_malben()
{
 int xs,ys,xe,ye;
 char *str;

  cleardevice();
  setfillstyle(1,13);
  bar3d(65,45,480,90,30,1);
  outtextxy(100,50,":  X-");
  xs=atoi(str=get_string(70,50,3));
  outtextxy(100,60,": Y-");
  ys=atoi(str=get_string(70,60,3));
  outtextxy(100,70,": X-");
  xe=atoi(str=get_string(70,70,3));
  outtextxy(100,80,": Y-");
  ye=atoi(str=get_string(70,80,3));
  cleardevice();
  rectangle(xs,ys,xe,ye);
  outtextxy(100,460,"...");
  getch();

}

void draw_triangle()
{
  char *str;
  int x1,x2,x3,y1,y2,y3;

  cleardevice();
  setfillstyle(1,13);
  bar3d(65,45,480,120,30,1);
  outtextxy(100,50,": X-");
  x1=atoi(str=get_string(70,50,3));
  outtextxy(100,60,": Y-");
  y1=atoi(str=get_string(70,60,3));
  outtextxy(100,70,": X-");
  x2=atoi(str=get_string(70,70,3));
  outtextxy(100,80,": Y-");
  y2=atoi(str=get_string(70,80,3));
  outtextxy(100,90,": X-");
  x3=atoi(str=get_string(70,90,3));
  outtextxy(100,100,": Y-");
  y3=atoi(str=get_string(70,100,3));

  cleardevice();
  line(x1,y1,x2,y2);
  line(x2,y2,x3,y3);
  line(x3,y3,x1,y1);
  outtextxy(100,460,"...");
  getch();

}


void draw_elipse()
{
  char *str;
  int x,y,sta,ena,xrad,yrad;

  cleardevice();
  setfillstyle(1,13);
  bar3d(65,45,410,120,30,1);
  outtextxy(100,50,": X-");
  x=atoi(str=get_string(70,50,3));
  outtextxy(100,60,": Y-");
  y=atoi(str=get_string(70,60,3));
  outtextxy(100,70,":");
  sta=atoi(str=get_string(70,70,3));
  outtextxy(100,80,":");
  ena=atoi(str=get_string(70,80,3));
  outtextxy(100,90,":                    X-");
  xrad=atoi(str=get_string(70,90,3));
  outtextxy(100,100,":           Y-");
  yrad=atoi(str=get_string(70,100,3));
  cleardevice();
  ellipse(x,y,sta,ena,xrad,yrad);
  outtextxy(100,460,"...");
  getch();

}

void endprog()
{
 cleardevice();
 outtextxy(0,0,"Bye Bye");
 delay(1000);
 exit(0);
}

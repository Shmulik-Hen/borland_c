#include <graphics.h>
#include <dos.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <iostream.h>
#define ESC 27

typedef struct POINT
	{
	 int x;
	 int y;
	};

int InitMouse();
void ShowMouse();
void HideMouse();
int MouseDownLeft();
int MouseDownRight();
int MousePressed();
void GetMouseLocation(POINT *p);
void SetMouseLocation(POINT *p);
void LocToStr(char *s ,int x, int y);
void keyboard_things();
void mouse_things();
void standart_things();

POINT p;

void main()
{
 int gd=DETECT,gm;

 if(!InitMouse())
   {
    cout<<"mouse driver not found";
    exit(1);
   }

 initgraph(&gd,&gm,"");
 if(graphresult()!=grOk)
   {
    cout<<"error initialising graphics mode";
    exit(1);
   }

 cleardevice();
 setbkcolor(1);
 setfillstyle(1,1);
 ShowMouse();
 while(1)
   {
    while( !MouseDownLeft() && !MouseDownRight() && !kbhit() )
	 {
	  // things to do when no action is taken
	  standart_things();
	 }
    if(kbhit())
       keyboard_things();  //things to do when keyboard is used
    if(MousePressed())
       mouse_things();     //things to do when mouse is used
   }
}

int InitMouse()
{
 union REGS r;

 r.x.ax = 0;
 int86(0x33,&r,&r);
 return r.x.ax;
}

void HideMouse()
{
 union REGS r;

 r.x.ax = 2;
 int86(0x33,&r,&r);
}

void ShowMouse()
{
 union REGS r;

 r.x.ax = 1;
 int86(0x33,&r,&r);
}

int MousePressed()
{
 union REGS r;

 r.x.ax = 3;
 int86(0x33,&r,&r);
 return (r.x.bx & 0x03);
}

int MouseDownLeft()
{
 union REGS r;

 r.x.ax = 3;
 int86(0x33,&r,&r);
 return (r.x.bx & 0x01);
}

int MouseDownRight()
{
 union REGS r;

 r.x.ax = 3;
 int86(0x33,&r,&r);
 return (r.x.bx & 0x02);
}

void GetMouseLocation(POINT *p)
{
 union REGS r;

 r.x.ax = 3;
 int86(0x33,&r,&r);
 p->x = r.x.cx;
 p->y = r.x.dx;
}

void SetMouseLocation(POINT *p)
{
 union REGS r;

 r.x.ax = 4;
 r.x.cx = p->x;
 r.x.dx = p->y;
 int86(0x33,&r,&r);
}

void LocToStr(char *s,int x, int y)
{
 char str1[3],str2[3];

 strcpy(s,"");
 itoa(x,str1,10);
 itoa(y,str2,10);
 strcat(s,str1);
 strcat(s,",");
 strcat(s,str2);
 strcat(s,"\0");
}

void keyboard_things()
{
 char c;

 if((c=getch())==ESC)
   {
    closegraph();
    exit(0);
   }
}

void mouse_things()
{
 char str[8];

 if(MouseDownRight())
   {
    while(MouseDownRight());
    closegraph();
    exit(0);
   }
 if(MouseDownLeft())
   {
    while(MouseDownLeft());
    GetMouseLocation(&p);
    LocToStr(str,p.x,p.y);
    HideMouse();
    cleardevice();
    outtextxy(p.x,p.y,str);
    ShowMouse();
   }
}

void standart_things()
{
 static char s[2];

 s[1]='\0';
 if(s[0] <= '0')
   s[0]='0';
 if(s[0] > '9')
    s[0]='0';
 bar(0,0,10,10);
 outtextxy(0,0,s);
 s[0]++;
 delay(100);
}
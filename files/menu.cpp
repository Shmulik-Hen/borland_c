#include <menu.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <iostream.h>
#include <stdlib.h>
#define CLIP_ON  1
#define CLIP_OFF 0

my_menu::my_menu()
{
}

my_menu::~my_menu()
{
}

my_menu::my_menu(int x,int y,int r,char *s[])
:my_window(x,y,longest(r,s)*textwidth("H")+5,r*textheight("H")+10)
{
 int i;

 rows=r;
 x_pos=x;
 y_pos=y;
 y_inc=textheight("H");
 width=longest(r,s)*textwidth("H")+5;
 height=r*y_inc+10;
 show(x,y);
 setfillstyle(SOLID_FILL,BLACK);
 bar3d(x,y,width,height,0,0);
 for(i=0;i<r;i++)
    {
     outtextxy(x+4,y,s[i]);
     y+=y_inc;
    }
 save();
 hide();
}

int my_menu::choice()
{
 int count=0,x,y;
 unsigned int size;
 void *buff1;
 void *buff2;
 char c;

 x=x_pos;
 y=y_pos;

 size=imagesize(x+2,y,width-2,y+y_inc);
 if( (buff1=(void*)new char[size]) == NULL)
   {
    closegraph();
    cout<<"Error: not enough heap space in my_menu().";
    getch();
    exit(1);
   }
 if( (buff2=(void*)new char[size]) == NULL)
   {
    closegraph();
    cout<<"Error: not enough heap space in my_menu().";
    getch();
    exit(1);
   }

 setfillstyle(SOLID_FILL,WHITE);
 bar(x+2,y,width-2,y+y_inc);
 getimage(x+2,y,width-2,y+y_inc,buff1);
 show(x_pos,y_pos);
 getimage(x+2,y+3,width-2,y+3+y_inc,buff2);
 putimage(x+2,y+3,buff1,XOR_PUT);
 while((c=getch()) != '\r')
      {
       if(c==27)
	 return 0;
       if(c==0)
	 c=getch();
       switch(c)
	 {
	  case 72:count--;
		  if(count<0)
		    count=rows-1;
		  break;
	  case 80:count++;
		  if(count>=rows)
		    count=0;
		  break;
	  default:break;
	 }
	  putimage(x+2,y+3,buff2,COPY_PUT);
	  y=y_inc*count;
	  getimage(x+2,y+3,width-2,y+3+y_inc,buff2);
	  putimage(x+2,y+3,buff1,XOR_PUT);
      }

 delete []buff1;
 delete []buff2;
 return count+1;
}

int longest(int r,char *s[])
{
 int i,temp,length=0;

 for(i=0;i<r;i++)
    {
     temp=strlen(s[i]);
     if(temp>length)
       length=temp;
    }
 return length;
}

#include "tar_win.h"
#include <iostream.h>
#include <process.h>
#include <conio.h>

void error(const char*);
int win::count=0;

win::win()
{
 bg=fg=NULL;
}

win::~win()
{
 if(fg!=NULL)
   delete[] fg;
 if(bg!=NULL)
   delete[] bg;
}

win::win(int wd, int ht ,int col)
{
 int i;

 bg=new int[wd*ht];
   if(bg==NULL) error("not enough memory in win::win()");
 fg=new int[wd*ht];
   if(bg==NULL) error("not enough memory in win::win()");
 width=wd;
 height=ht;
 xc=yc=1;
 id=++count;
 bcolor=col;
 fcolor=WHITE;
 size=wd*ht;
 for(i=0;i<size;i++)
   fg[i]=ch2int(32);
 unselect();
}

void win::show(int mx, int my)
{
 x=mx;
 y=my;
 gettext(x,y,x+width-1,y+height-1,bg);
 puttext(x,y,x+width-1,y+height-1,fg);
}

void win::hide()
{
 gettext(x,y,x+width-1,y+height-1,fg);
 puttext(x,y,x+width-1,y+height-1,bg);
}

void win::save()
{
 gettext(x,y,x+width-1,y+height-1,fg);
}

void win::select()
{
 int i;

 for(i=1;i<width-1;i++)
     fg[(height-1)*width+i]=fg[i]=ch2int(205);
 for(i=width;i<size-width;i+=width)
    fg[i]=fg[i+width-1]=ch2int(186);
 fg[0]=ch2int(201);
 fg[width-1]=ch2int(187);
 fg[size-width]=ch2int(200);
 fg[size-1]=ch2int(188);
 fg[2]=ch2int(id+48);
 textcolor(fcolor);
 textbackground(bcolor);
 puttext(x,y,x+width-1,y+height-1,fg);
 gotoxy(x+xc,y+yc);
}

void win::unselect()
{
 int i;

 for(i=1;i<width-1;i++)
     fg[(height-1)*width+i]=fg[i]=ch2int(196);
 for(i=width;i<size-width;i+=width)
    fg[i]=fg[i+width-1]=ch2int(179);
 fg[0]=ch2int(218);
 fg[width-1]=ch2int(191);
 fg[size-width]=ch2int(192);
 fg[size-1]=ch2int(217);
 fg[2]=ch2int(id+48);
 puttext(x,y,x+width-1,y+height-1,fg);
}

void win::type_in()
{
 char ch;

 while( ((ch=getch())!='\t')  && (ch!=27) )
   {
    if(ch==0)
      {
       getch();
       continue;
      }
    switch(ch)
     {
      case '\b': if(xc>0)
		    xc--;
		 if(xc==0 && yc>1)
		   {
		    xc=width-2;
		    yc--;
		   }
		 if(xc>0 && yc>0)
		   {
		    gotoxy(x+xc,y+yc);
		    putch(' ');
		    gotoxy(x+xc,y+yc);
		   }
		 else xc++;
		 break;
      case '\r': xc=1;
		 if(yc<height-2)
		   yc++;
		 gotoxy(x+xc,y+yc);
		 break;
      default  : gotoxy(x+xc,y+yc);
		 putch(ch);
		 xc++;
		 if(xc==width-1 && yc<height-2)
		   {
		    xc=1;
		    yc++;
		   }
		 break;
     }
   }
 ungetch(ch);
 save();
}

int win::ch2int(int ch)
{
 return ((((bcolor<<4)|fcolor)<<8)|ch);
}

void error(const char *s)
{
 cerr<<s;
 exit(1);
}
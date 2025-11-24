#include <graphics.h>
#include <stdlib.h>
#include <iostream.h>
#include <conio.h>
#define ROWS 6
#define COLS 8
#define ESC 27

void save_image(int xs,int ys,int xe,int ye,void **buf);
void restore_image(int x,int y,void **buf);

void *buff[2];

int main(void)
{
 int gdriver = DETECT, gmode, errorcode;
 int x,y,i,x_inc,y_inc,count;
 char c,buffer[ROWS][COLS]={"LINE","RECT","CIRCLE","SQUARE","POLIGON","QUIT"};

 initgraph(&gdriver, &gmode, "");
 errorcode = graphresult();
 if (errorcode != grOk)
    {
     cout<<"Graphics error: "<<grapherrormsg(errorcode)<<endl;
     cout<<"Press any key to halt:";
     getch();
     exit(1);
    }

 setcolor(WHITE);
 setbkcolor(BLACK);
 settextstyle(SMALL_FONT,HORIZ_DIR,0);
 setusercharsize(2,1,2,1);
 x_inc=textwidth("H");
 y_inc=textheight("H");
 x=0;
 y=0;

 bar(x+3,y,x+(COLS-1)*x_inc,y+y_inc);
 save_image(x+3,y,x+(COLS-1)*x_inc,y+y_inc,&buff[0]);
 cleardevice();

 rectangle(x,y,x+(COLS-1)*x_inc+5,y+ROWS*y_inc+10);

 for(i=0;i<ROWS;i++)
    {
     outtextxy(x+5,y+2,buffer[i]);
     y+=y_inc;
    }

 x=0;
 y=0;
 save_image(x+3,y+5,x+(COLS-1)*x_inc,y+y_inc+5,&buff[1]);
 //putimage(100,100,buff[1],NOT_PUT);
 putimage(x+3,y+5,buff[0],XOR_PUT);

 count=0;
 while((c=getch()) != ESC)
      {
       if(c == 0)
	 c=getch();
       switch(c)
	     {
	      case 72: count--;
		       if(count<0)
			 count=ROWS-1;
		       break;
	      case 80: count++;
		       if(count>=ROWS)
			 count=0;
		       break;
	      default: break;
	     }
       restore_image(x+3,y+5,&buff[1]);
       y=y_inc*count;
       save_image(x+3,y+5,x+(COLS-1)*x_inc,y+y_inc+5,&buff[1]);
       putimage(x+3,y+5,buff[0],XOR_PUT);
      }

 cleardevice();
 closegraph();
 return 0;
}

void save_image(int xs,int ys,int xe,int ye,void **buf)
{
   unsigned size;

   size = imagesize(xs,ys,xe,ye);

   if ((*buf=(void *)malloc(size)) == NULL)
      {
	 closegraph();
	 cout<<"Error: not enough heap space in save_image().\n";
	 getch();
	 exit(1);
      }
   getimage(xs,ys,xe,ye,*buf);
}

void restore_image(int x,int y, void **buf)
{
 putimage(x,y,*buf,COPY_PUT);
 free(*buf);
}

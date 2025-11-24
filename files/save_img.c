#include<graphics.h>
#include<conio.h>
#include<stdio.h>

void save_bit(int bit,int count);

FILE *fp;
unsigned char byte;

void main()
{
   int gdriver = IBM8514, gmode=IBM8514HI , errorcode;
   int x,y,i,count=0,color;
   char filename[20]="C:\\TC\\TRY.DAT";
   byte=0x00;

   initgraph(&gdriver, &gmode, "C:\\TC\\BGI");
   color=getmaxcolor();
   setcolor(color);
   setlinestyle(SOLID_LINE,0,1);
   setfillstyle(XHATCH_FILL,color);
   rectangle(50,50,100,100);
   floodfill(51,51,color);

   fp=fopen(filename,"w");

   for(y=49;y<=101;y++)
      {
       for(x=49;x<=101;x++)
	  {
	   if( getpixel(x,y)==color )
	       i=1;
	   else
	       i=0;
	   save_bit(i,count);
	   count=(count+1)%8;
	  }
      }

   fputc(EOF,fp);
   fclose(fp);

   getch();
   cleardevice();
   closegraph();
}


void save_bit(int bit,int count)
{
 if(bit==0)
    byte=byte << 1;
 if(bit==1)
   {
    byte=byte << 1;
    byte++;
   }
 if(count==7)
    fputc(byte,fp);
}
		
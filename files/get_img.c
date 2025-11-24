#include<graphics.h>
#include<conio.h>
#include<stdio.h>

int read_bit(int count);

FILE *fp;

void main()
{
   int gdriver = DETECT, gmode , errorcode;
   int maxx,maxy,x,y,color,count=0;
   char filename[20]="C:\\TC\\TRY.DAT";

   initgraph(&gdriver, &gmode, "C:\\TC\\BGI");
   maxx=getmaxx();
   maxy=getmaxy();
   color=getmaxcolor();

   fp=fopen(filename,"r");

   for(y=49; y<=101;y++)
      {
       for(x=49;x<=101;x++)
	  {
	   if(read_bit(count))
	      putpixel(x,y,color);
	   else
	      putpixel(x,y,0);
	   count=(count+1)%8;
	  }
      }

   fclose(fp);

   getch();
   closegraph();
}


int read_bit(int count)
{
 static unsigned char byte,temp;

 if(count==0)
    byte=fgetc(fp);

 temp = byte & 0x80;
 byte = byte << 1;

 if(temp==0)
    return 0;
 else
    return 1;
}
#include<graphics.h>
#include<stdio.h>
#include <stdlib.h>
#include <alloc.h>

void save_screen(void far *buf[4]);
void restore_screen(void far *buf[4]);

int maxx,maxy;

void main()
{
   int gdriver = DETECT, gmode;
   int x,y,color,count;
   char *filename="MANDEL.DAT";
   FILE *fp;
   void far *ptr[4];


   fp=fopen(filename,"r");
   initgraph(&gdriver, &gmode,"c:\\tc\\bgi");
   maxx=getmaxx();
   maxy=getmaxy();
   

   for(y=0; y<=240;y++)
       for(x=0;x<=640;x++)
	  {
	   fscanf(fp,"%d",&count);
	   color=count+1;
	   if(count==1000)
	      color=0;
	   putpixel(x,y,color);
	   putpixel(x,479-y,color);
	  }

   fclose(fp);
   getchar();
   save_screen(ptr);
   cleardevice();   
   restore_screen(ptr); 
   getchar();
   closegraph();
}

void save_screen(void far *buf[4])
{
   unsigned long size;
   int ystart=0, yend, yincr, block;

   yincr = (maxy+1) / 4;
   yend = yincr;
   size = imagesize(0, ystart, maxx, yend); /* get byte size of image */

   for (block=0; block<=3; block++)
   {
      if ((buf[block] = farmalloc(size)) == NULL)
      {
         closegraph();
         printf("Error: not enough heap space in save_screen().\n");
         exit(1);
      }

      getimage(0, ystart, maxx, yend, buf[block]);
      ystart = yend + 1;
      yend += yincr + 1;
   }
}

void restore_screen(void far *buf[4])
{
   int ystart=0, yend, yincr, block;

   yincr = (maxy+1) / 4;
   yend = yincr;

   for (block=0; block<=3; block++)
   {
      putimage(0, ystart, buf[block], COPY_PUT);
      farfree(buf[block]);
      ystart = yend + 1;
      yend += yincr + 1;
   }
}
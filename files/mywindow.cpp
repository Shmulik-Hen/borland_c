#include <mywindow.h>

wind::wind()
{
}

wind::wind(int xs, int ys, int xe, int ye)
{
}

wind::~wind()
{
}

void wind::save(int xs, int ys, int xe, int ye)
{
   unsigned size;

   size = imagesize(xs,ys,xe,ye);

   if ((buf=(void *)malloc(size)) == NULL)
      {
	 closegraph();
	 printf("Error: not enough heap space in save_screen().\n");
	 getch();
	 exit(1);
      }
   getimage(xs,ys,xe,ye,buf);
}

void wind::show(int x,int y)
{
 putimage(x,y,buf,COPY_PUT);
 free(buf);
}

void wind::hide()
{
}

void wind::puttext(int row, int col, char *str)
{
}
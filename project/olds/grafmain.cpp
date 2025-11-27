#include "graphics.h"
#include <conio.h>

void main()
{
	initgraph();
	/*
	for(int i=0;i<256;i+=16)
	  for(int j=0;j<16;j++)
	     {
	      setcolor(i+j);
	      bar(i,j*10,i+15,j*10+15);
		    }*/

	clearviewport();
	setcolor(255);
	bar(0, 0, 319, 199);
	/*
	line(0,0,319,0);
	line(319,0,319,199);
	line(319,199,0,199);
	line(0,199,0,0);
	*/
	int scratch[20] = {50, 50, 150, 50, 150, 150, 50, 150};
	setcolor(170);
	fillpoly(4, scratch);

	flip_page();
	getch();
	closegraph();
}

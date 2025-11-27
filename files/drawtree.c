#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>

void drawtree(int x, int y, int level, int len, int ang);

main()
{
	int gdriver = DETECT, gmode;
	initgraph(&gdriver, &gmode, "..\\bgi");
	setcolor(getmaxcolor());
	line(320, 480, 320, 300);
	drawtree(320, 300, 9, 150, 90);
	getch();
	closegraph();
}

void drawtree(int x, int y, int level, int len, int ang)
{
	int langle, rangle, length, lx, ly, rx, ry;

	if (!level)
		return;
	rangle = ang - 45;
	langle = ang + 45;
	length = len * 2 / 3;
	lx = x + (length * cos(langle * 3.14 / 180));
	ly = y - (length * sin(langle * 3.14 / 180));
	rx = x + (length * cos(rangle * 3.14 / 180));
	ry = y - (length * sin(rangle * 3.14 / 180));
	line(x, y, lx, ly);
	line(x, y, rx, ry);
	drawtree(lx, ly, level - 1, length, langle);
	drawtree(rx, ry, level - 1, length, rangle);
}

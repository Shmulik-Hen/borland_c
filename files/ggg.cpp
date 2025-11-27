#include <graphics.h>
#include <conio.h>

void main()
{
	int gd, gm;
	gd = CGA;
	gm = CGAC0;
	initgraph(&gd, &gm, "d:\\bc\\bgi");
	rectangle(0, 0, 319, 199);
	rectangle(0, 20, 319, 150);
	line(0, 85, 319, 85);
	line(70, 100, 250, 100);
	rectangle(150, 80, 170, 100);
	circle(160, 175, 23);
	getch();
	closegraph();
}

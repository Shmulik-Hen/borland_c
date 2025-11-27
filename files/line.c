#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <conio.h>

void myline(int x1, int y1, int x2, int y2);

int main(void)
{
	/* request auto detection */
	int gdriver = DETECT, gmode, errorcode;

	/* initialize graphics and local variables */
	initgraph(&gdriver, &gmode, "d:\\bc\\bgi");

	/* read result of initialization */
	errorcode = graphresult();
	/* an error occurred */
	if (errorcode != grOk) {
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);
	}

	/* draw a diagonal line */
	// getch();
	myline(639, 479, 0, 0);
	// getch();
	myline(639, 0, 0, 479);

	/* clean up */
	getch();
	closegraph();
	return 0;
}

void myline(int x1, int y1, int x2, int y2)
{
	int d_x, d_y, i;
	float x, y, a, dx, dy;

	dx = x2 - x1;
	dy = y2 - y1;
	d_x = abs(dx);
	d_y = abs(dy);
	a = dy / dx;
	x = x1;
	y = y1;

	if (d_x >= d_y)
		for (i = 0; i <= d_x; i++) {
			putpixel(x, y, WHITE);
			x += 1.0 / a;
			y += a;
		}
	else
		for (i = 0; i <= d_y; i++) {
			putpixel(x, y, WHITE);
			x = 1.0 / a;
			y += a;
		}
}

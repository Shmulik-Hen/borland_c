#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <alloc.h>

void save_screen(void far *buf[4]);
void restore_screen(void far *buf[4]);
void circ(void);
void rect(void);

int maxx, maxy;

main()
{
	void far *ptr[4];
	int gdriver = DETECT, gmode;

	initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
	maxx = getmaxx();
	maxy = getmaxy();

	switch (getch()) {
	case 'c':
		circ();
		break;
	case 'r':
		rect();
		break;
	default:
		break;
	}
	save_screen(ptr);    /* save the current screen */
	getch();	     /* pause screen */
	cleardevice();	     /* clear screen */
	restore_screen(ptr); /* restore the screen */
	getch();	     /* pause screen */

	closegraph();
}

void save_screen(void far *buf[4])
{
	unsigned long size;
	int ystart = 0, yend, yincr, block;

	yincr = (maxy + 1) / 4;
	yend = yincr;
	size = imagesize(0, ystart, maxx, yend); /* get byte size of image */

	for (block = 0; block <= 3; block++) {
		if ((buf[block] = farmalloc(size)) == NULL) {
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
	int ystart = 0, yend, yincr, block;

	yincr = (maxy + 1) / 4;
	yend = yincr;

	for (block = 0; block <= 3; block++) {
		putimage(0, ystart, buf[block], COPY_PUT);
		farfree(buf[block]);
		ystart = yend + 1;
		yend += yincr + 1;
	}
}

void circ(void)
{
	int midx, midy, angle = 0, radius, color;
	radius = 200;
	midx = getmaxx() / 2;
	midy = getmaxy() / 2;
	setcolor(0);

	for (color = 1; color < 16; color++) {
		setfillstyle(SOLID_FILL, color);
		pieslice(midx, midy, angle, angle + 24, radius);
		angle += 24;
	}
}

void rect(void)
{
	maxx = getmaxx();
	maxy = getmaxy();

	rectangle(0, 0, maxx, maxy);
	line(0, 0, maxx, maxy);
	line(0, maxy, maxx, 0);
	setfillstyle(SOLID_FILL, 9);
	floodfill(320, 1, getmaxcolor());
	setfillstyle(SOLID_FILL, 14);
	floodfill(638, 240, getmaxcolor());
	setfillstyle(SOLID_FILL, 2);
	floodfill(320, 478, getmaxcolor());
	setfillstyle(SOLID_FILL, 12);
	floodfill(1, 240, getmaxcolor());
}

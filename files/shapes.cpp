#include <graphics.h>
#include <iostream.h>
#include <stdlib.h>
#include <conio.h>
#include <wind.h>
#include <menu.h>
#define ROWS 6

union key
{
	int i;
	char c[2];
};

void do_line();
void do_rect();
void do_circle();
void do_elipse();
void do_poligon();
void do_quit();
char *get_string(int x, int y, int len);

int main()
{
	int gdriver = DETECT, gmode, errorcode;
	int chs;
	char *topics[ROWS] = {"LINE", "RECTANGLE", "CIRCLE", "ELIPSE", "POLIGON", "QUIT"};

	initgraph(&gdriver, &gmode, "");
	errorcode = graphresult();
	if (errorcode != grOk) {
		cout << "Graphics error:" << grapherrormsg(errorcode) << endl;
		cout << "Press any key to halt:";
		getch();
		exit(1);
	}
	settextstyle(SMALL_FONT, HORIZ_DIR, 0);
	setusercharsize(3, 2, 2, 1);

	my_menu m(0, 0, ROWS, topics);
	while (1) {
		chs = m.choice();
		if (chs) {
			cleardevice();
			switch (chs) {
			case 1:
				do_line();
				break;
			case 2:
				do_rect();
				break;
			case 3:
				do_circle();
				break;
			case 4:
				do_elipse();
				break;
			case 5:
				do_poligon();
				break;
			case 6:
				do_quit();
			}
		}
		outtextxy(0, 450, "PRESS ANY KEY...");
		getch();
		cleardevice();
	}
}

void do_line()
{
	line(0, 0, 100, 100);
}

void do_rect()
{
	rectangle(0, 0, 100, 100);
}

void do_circle()
{
	int x, y, r;
	char *str;

	outtextxy(10, 10, "ENTER X CENTER:");
	x = atoi(str = get_string(150, 10, 3));
	outtextxy(10, 20, "ENTER Y CENETR:");
	y = atoi(str = get_string(150, 20, 3));
	outtextxy(10, 30, "ENTER RADIUS:");
	r = atoi(str = get_string(150, 30, 3));
	cleardevice();
	circle(x, y, r);
}

void do_elipse()
{
	ellipse(320, 240, 0, 360, 200, 100);
}

void do_poligon()
{
	int maxx, maxy;
	int poly[10];
	maxx = getmaxx();
	maxy = getmaxy();
	poly[0] = 20; /* 1st vertext */
	poly[1] = maxy / 2;
	poly[2] = maxx - 20; /* 2nd */
	poly[3] = 20;
	poly[4] = maxx - 50; /* 3rd */
	poly[5] = maxy - 20;
	poly[6] = maxx / 2; /* 4th */
	poly[7] = maxy / 2;
	poly[8] = poly[0];
	poly[9] = poly[1];
	drawpoly(5, poly);
}

void do_quit()
{
	closegraph();
	exit(0);
}

char *get_string(int x, int y, int len)
{
	union key k;
	char str[10];
	int j;

	for (j = 0, k.i = getch(); j < len && k.c[0] != '\r'; j++) {
		k.c[1] = '\0';
		if (k.c[0]) {
			outtextxy(x, y, k.c);
			str[j] = k.c[0];
			x += 10;
		}
		k.i = getch();
	}
	str[j] = '\0';
	return str;
}

#include <iostream.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <mouse.h>
#include <mymenu.h>
#include <utils.h>
#include <drawing.h>
#include <dbox.h>

BODY b;
POINT p;
FILE *fp;
char filename[] = "project.dat";
double zoom, angle;
int close_flag, save_flag, color_flag, draw_flag, offsetx, offsety;

void main()
{
	int gd = DETECT, gm;

	if (!InitMouse()) {
		cout << "mouse driver not found";
		exit(1);
	}

	initgraph(&gd, &gm, "");
	if (graphresult() != grOk) {
		cout << "error initialising graphics mode";
		exit(1);
	}

	close_flag = 0;
	save_flag = 1;
	color_flag = 0;
	draw_flag = 0; // set initial values for global variables
	offsetx = 270;
	offsety = 210;
	zoom = 1.0;
	angle = 0.0;

	setvisualpage(0);
	setactivepage(1); // prepare items without showing
	prepare_menu();
	prepare_dbox();
	setactivepage(0);
	cleardevice();
	draw_screen();
	ShowMouse();

	while (1) // main loop of the program
	{
		while (!MousePressed() && !kbhit())
			;
		if (kbhit())
			keyboard_things(); // things to do when keyboard is used
		if (MousePressed())
			mouse_things(); // things to do when mouse is used
	}
}

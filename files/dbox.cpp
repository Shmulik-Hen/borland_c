#include <graphics.h>
#include <iostream.h>
#include <conio.h>
#include <process.h>
#include <alloc.h>
#include <dbox.h>
#include <mouse.h>
#include <utils.h>

extern POINT p;
extern int close_flag, save_flag;
void *f_g, *b_g, *bar_1, *bar_2; // places to hold images

void prepare_dbox() // creates a dialog box
{
	int size, bar_size;

	size = imagesize(0, 0, 150, 100);	  // size of dialog box
	bar_size = imagesize(0, 0, 40, 15);	  // size of highlight bar
	if ((f_g = (void *)malloc(size)) == NULL) // for dialog box
	{
		closegraph();
		cout << "not enough memory in prepare_dbox()";
		exit(1);
	}
	if ((b_g = (void *)malloc(size)) == NULL) // for background
	{
		closegraph();
		cout << "not enough memory in prepare_dbox()";
		exit(1);
	}
	if ((bar_1 = (void *)malloc(bar_size)) == NULL) // for highlight bar
	{
		closegraph();
		cout << "not enough memory in prepare_dbox()";
		exit(1);
	}
	if ((bar_2 = (void *)malloc(bar_size)) == NULL) // for highlighted item
	{
		closegraph();
		cout << "not enough memory in prepare_dbox()";
		exit(1);
	}
	settextstyle(SMALL_FONT, HORIZ_DIR, 0);
	setusercharsize(3, 2, 2, 1);
	setfillstyle(1, 15);
	rectangle(200, 0, 350, 100);	   // draw dialog box frame
	outtextxy(225, 18, "SAVE FILE ?"); // output text of d_box
	outtextxy(225, 55, "[Yes]   [No]");
	getimage(200, 0, 350, 100, f_g);   // save current image of d_box
	bar(225, 60, 265, 75);		   // draw highlight bar
	getimage(225, 60, 265, 75, bar_1); // save it's image
}

void draw_dbox()
{
	char c;
	int yes = 1, done = 0;

	HideMouse();
	getimage(100, 100, 250, 200, b_g);   // save background
	putimage(100, 100, f_g, COPY_PUT);   // display d_box
	getimage(124, 160, 164, 175, bar_2); // save selected item
	putimage(124, 160, bar_1, XOR_PUT);  // select default item
	ShowMouse();
	while (MousePressed())
		;
	while (!done) {
		while (!kbhit() && !MousePressed())
			;    // wait for action
		if (kbhit()) // keyboard selection
		{
			c = getch(); // regular key
			if (c == 0)  // special key
				c = getch();
			switch (c) {
			case 'y': // YES was selected
			case 'Y':
				do_yes(); // do it
				done = 1;
				break;
			case 'n': // NO was selected
			case 'N':
				do_no(); // do it
				done = 1;
				break;
			case '\r':
				if (yes)
					do_yes(); // ENTER was pressed
				else
					do_no(); // perform selection
				done = 1;
				break;
			case 77:
				if (yes) // right arrow
				{	 // select NO
					yes = 0;
					HideMouse();
					putimage(124, 160, bar_2, COPY_PUT);
					getimage(184, 160, 224, 175, bar_2);
					putimage(184, 160, bar_1, XOR_PUT);
					ShowMouse();
				}
				break;
			case 75:
				if (!yes) // left arrow
				{	  // select YES
					yes = 1;
					HideMouse();
					putimage(184, 160, bar_2, COPY_PUT);
					getimage(124, 160, 164, 175, bar_2);
					putimage(124, 160, bar_1, XOR_PUT);
					ShowMouse();
				}
				break;
			case 27:
				HideMouse();			   // ESCAPE was pressed
				putimage(100, 100, b_g, COPY_PUT); // abort mission
				ShowMouse();
				close_flag = 0;
				done = 1;
				break;
			default:
				break;
			}
		}
		else if (MouseDownLeft()) // mouse selection
		{
			GetMouseLocation(&p);
			if (between(p, 124, 160, 164, 175)) // YES selected
			{
				if (!yes) // if not allready highlighted
				{
					HideMouse(); // highlight YES
					putimage(184, 160, bar_2, COPY_PUT);
					getimage(124, 160, 164, 175, bar_2);
					putimage(124, 160, bar_1, XOR_PUT);
					ShowMouse();
				}
				while (MousePressed())
					; // keep highlighting until release
				do_yes(); // do it
				done = 1;
			}
			else if (between(p, 184, 160, 224, 175)) // NO selected
			{
				if (yes) // if not allready highlighted
				{
					HideMouse(); // highlight NO
					putimage(124, 160, bar_2, COPY_PUT);
					getimage(184, 160, 224, 175, bar_2);
					putimage(184, 160, bar_1, XOR_PUT);
					ShowMouse();
				}
				while (MousePressed())
					; // keep highlighting until release
				do_no();  // do it
				done = 1;
			}
			else if (!between(p, 100, 100, 250, 200) || MouseDownRight()) // escape
			{
				while (MousePressed())
					;
				HideMouse();
				putimage(100, 100, b_g, COPY_PUT); // restore previous image
				ShowMouse();
				close_flag = 0;
				done = 1;
			}
		}
	}
}

void do_yes() // things to do when YES selected
{
	HideMouse();
	putimage(100, 100, b_g, COPY_PUT); // restore previous image
	ShowMouse();
	do_save();
	close_flag = 1;
	do_close();
}

void do_no()
{
	HideMouse();
	putimage(100, 100, b_g, COPY_PUT); // restore previous image
	ShowMouse();
	save_flag = 1;
	close_flag = 1;
	do_close();
}

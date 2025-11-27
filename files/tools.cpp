#include <tools.h>
#include <mouse.h>
#include <drawing.h>

extern POINT p;
extern int draw_flag, offsetx, offsety;
extern BODY b;
extern double zoom, angle;

void choose_tool() // choose action to perform on element
{
	if (!draw_flag) // if no element is present do nothing
		return;
	if (between(p, 540, 17, 590, 107)) // zoom in
		do_zoom('i');
	else if (between(p, 590, 17, 639, 107)) // zoom out
		do_zoom('o');
	else if (between(p, 540, 107, 590, 197)) // rotate ccw
		rotate('l');
	else if (between(p, 590, 107, 639, 197)) // rotate cw
		rotate('r');
	else if (between(p, 540, 197, 590, 287)) // move up
		move('u');
	else if (between(p, 590, 197, 639, 287)) // move down
		move('d');
	else if (between(p, 540, 287, 590, 377)) // move left
		move('l');
	else if (between(p, 590, 287, 639, 377)) // move right
		move('r');
}
// pretty much self explainatory from here on

void do_zoom(char z)
{
	switch (z) {
	case 'i':
		zoom *= 1.1;
		break;
	case 'o':
		zoom *= 0.9;
		break;
	}
}

void move(char dir)
{
	switch (dir) {
	case 'u':
		offsety -= 10;
		break;
	case 'd':
		offsety += 10;
		break;
	case 'l':
		offsetx -= 10;
		break;
	case 'r':
		offsetx += 10;
		break;
	}
}

void rotate(char d)
{
	switch (d) {
	case 'l':
		angle -= 0.05;
		break;
	case 'r':
		angle += 0.05;
		break;
	}
}

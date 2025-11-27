#include <wind.h>
#include <graphics.h>
#include <iostream.h>
#include <process.h>

my_window::my_window()
{
}

my_window::my_window(int h, int w, int f)
{
	height = h;
	width = w;
	frame = f;
	visible = 0;
	first = 1;
	size = imagesize(0, 0, width, height);
	if ((foreground = (void *)new char[size]) == NULL) {
		closegraph();
		cout << "Error: not enough heap space in my_window::my_window().";
		exit(1);
	}
	if ((background = (void *)new char[size]) == NULL) {
		closegraph();
		cout << "Error: not enough heap space in my_window::my_window().";
		exit(1);
	}
}

my_window::~my_window()
{
	delete[] foreground;
	delete[] background;
}

void my_window::show(int x, int y)
{
	pos_x = x;
	pos_y = y;
	visible = 1;
	getimage(x, y, x + width, y + height, background);
	putimage(x, y, foreground, COPY_PUT);
	if (first && frame)
		rectangle(x, y, x + width, y + height);
}

void my_window::hide()
{
	if (!visible)
		return;
	putimage(pos_x, pos_y, background, COPY_PUT);
	visible = 0;
}

void my_window::save()
{
	getimage(pos_x, pos_y, pos_x + width, pos_y + height, foreground);
	first = 0;
}

void my_window::put_char(int x, int y, char c)
{
	char cc[2];

	if (!visible)
		return;
	cc[0] = c;
	cc[1] = '\0';
	setviewport(pos_x, pos_y, pos_x + width, pos_y + height, CLIP_ON);
	outtextxy(x, y, cc);
	setviewport(0, 0, getmaxx(), getmaxy(), CLIP_OFF);
}

void my_window::put_str(int x, int y, char *s)
{
	int i = 0;

	while (s[i]) {
		put_char(x, y, s[i++]);
		x += textwidth("H");
	}
}
/*
void my_window::highlight(int x1,int y1,int x2,int y2)
{
}

void my_window::de_highlight(int x1,int y1,int x2,int y2)
{
}
*/

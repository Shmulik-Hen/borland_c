#include <stdio.h>
#include <conio.h>

class win
{
private:

	unsigned int *buffer, *temp, *b, *t;
	unsigned int far *screen, far *s;
	int dx, dy, f_col, bk_col, size, row, col;

public:

	win();
	~win();
	void create(int d_x, int d_y, int fcol, int bcol, int border);
	void show(int x, int y);
	void save();
	void hide();
	void close();
	void _putch(char c, int x, int y, int fcol);
	void put_str(char *str, int x, int y, int fcol);
};

win::win()
{
}

win::~win()
{
	delete buffer;
	delete temp;
}

void win::create(int d_x, int d_y, int fcol, int bcol, int border)
{
	unsigned char c;

	dx = d_x;
	dy = d_y;
	f_col = fcol;
	bk_col = bcol;
	size = dx * dy;

	b = buffer = new unsigned int[size];

	for (row = 0; row < dy; row++) {
		for (col = 0; col < dx; col++) {
			if (border) {
				c = 0x20;
				if (row == 0 || row == dy - 1)
					c = 0xcd;
				if (col == 0 || col == dx - 1)
					c = 0xba;
				if (row == 0 && col == 0)
					c = 0xc9;
				if (row == 0 && col == dx - 1)
					c = 0xbb;
				if (row == dy - 1 && col == 0)
					c = 0xc8;
				if (row == dy - 1 && col == dx - 1)
					c = 0xbc;
			}
			else
				c = 0x20;
			*b++ = (((bk_col << 4) + f_col) << 8) + c;
		}
	}
}

void win::save()
{
	b = buffer;
	s = screen;

	for (row = 0; row < dy; row++) {
		for (col = 0; col < dx; col++) {
			*b++ = *s++;
		}
		s += (80 - dx);
	}
}

void win::show(int x, int y)
{
	s = (unsigned int far *)0xb8000000L;

	t = temp = new unsigned int[size];
	screen = s += (80 * (y - 1) + x - 1);
	b = buffer;

	for (row = y; row < (y + dy); row++) {
		for (col = x; col < (x + dx); col++) {
			*t++ = *s++;
		}
		s += (80 - dx);
	}

	t = temp;
	s = screen;

	for (row = y; row < (y + dy); row++) {
		for (col = x; col < (x + dx); col++) {
			*s++ = *b++;
		}
		s += (80 - dx);
	}
}

void win::hide()
{
	s = screen;
	t = temp;

	for (row = 0; row < dy; row++) {
		for (col = 0; col < dx; col++) {
			*s++ = *t++;
		}
		s += (80 - dx);
	}
	delete temp;
}

void win::close()
{
	t = temp;
	s = screen;

	for (row = 0; row < dy; row++) {
		for (col = 0; col < dx; col++)
			*s++ = *t++;
		s += (80 - dx);
	}
	delete buffer;
	delete temp;
}

void win::_putch(char c, int x, int y, int fcol)
{
	if (x <= (dx - 1) && y < (dy - 1)) {
		s = screen;
		s += (80 * y + x);
		*s = (((bk_col << 4) + fcol) << 8) + c;
	}
}

void win::put_str(char *str, int x, int y, int fcol)
{
	char c;
	while ((c = *str++) != NULL) {
		if (x >= (dx - 1)) {
			y++;
			x -= (dx - 2);
		}
		_putch(c, x++, y, fcol);
	}
}

void main()
{
	win a, b, d;
	char *str = "The quick brown fox jumps over the lazy dog.";
	char c;
	int x, y;

	clrscr();
	a.create(80, 25, 0x3, 0x3, 0);
	b.create(12, 7, 0xf, 0x4, 1);
	d.create(22, 10, 0xf, 0x1, 1);
	a.show(1, 1);
	b.show(x = 35, y = 10);
	d.show(50, 10);
	a.put_str(str, 1, 5, 0xf);
	b.put_str(str, 1, 1, 0xf);
	d.put_str(str, 1, 1, 0xf);
	b.save();
	do {
		c = getch();
		if (!c)
			c = getch();
		switch (c) {
		case 72:
			b.hide();
			b.show(x, --y);
			break;
		case 75:
			b.hide();
			b.show(--x, y);
			break;
		case 77:
			b.hide();
			b.show(++x, y);
			break;
		case 80:
			b.hide();
			b.show(x, ++y);
			break;
		}
	} while (c != 27);
	b.close();
	a.close();
	d.close();
}

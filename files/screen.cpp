#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

class win
{
protected:

	unsigned int *buffer, *temp, *b, *t;
	unsigned int far *screen, far *s;
	int width, length, fcolor, bcolor, buf_size;

public:

	win();
	~win();
	void create(int wid, int len, int fcol, int bcol, int border);
	void show(int col, int row);
	void save();
	void hide();
	void put_ch(char c, int col, int row, int fcol);
	void put_str(char *str, int col, int row, int fcol);
	void chg_attr(int col, int row, int len, int fcol, int bcol);
	void fill(int start_row, int end_row, char c, int fcol, int bcol);
};

win::win()
{
}

win::~win()
{
	delete buffer;
	delete temp;
}

void win::create(int wid, int len, int fcol, int bcol, int border)
{
	unsigned char c;
	int row, col;

	width = wid;
	length = len;
	fcolor = fcol;
	bcolor = bcol;
	buf_size = width * length;

	b = buffer = new unsigned int[buf_size];

	for (row = 0; row < length; row++) {
		for (col = 0; col < width; col++) {
			if (border) {
				c = 0x20;
				if (row == 0 || row == length - 1)
					c = 0xcd;
				if (col == 0 || col == width - 1)
					c = 0xba;
				if (row == 0 && col == 0)
					c = 0xc9;
				if (row == 0 && col == width - 1)
					c = 0xbb;
				if (row == length - 1 && col == 0)
					c = 0xc8;
				if (row == length - 1 && col == width - 1)
					c = 0xbc;
			}
			else
				c = 0x20;
			*b++ = (((bcolor << 4) + fcolor) << 8) + c;
		}
	}
}

void win::save()
{
	int row, col;
	b = buffer;
	s = screen;

	for (row = 0; row < length; row++) {
		for (col = 0; col < width; col++) {
			*b++ = *s++;
		}
		s += (80 - width);
	}
}

void win::show(int col, int row)
{
	s = (unsigned int far *)0xb8000000L;
	int x, y;

	t = temp = new unsigned int[buf_size];
	screen = s += (80 * (row - 1) + col - 1);
	b = buffer;

	for (y = row; y < (row + length); y++) {
		for (x = col; x < (col + width); x++) {
			*t++ = *s++;
		}
		s += (80 - width);
	}

	t = temp;
	s = screen;

	for (y = row; y < (row + length); y++) {
		for (x = col; x < (col + width); x++) {
			*s++ = *b++;
		}
		s += (80 - width);
	}
}

void win::hide()
{
	int row, col;
	s = screen;
	t = temp;

	for (row = 0; row < length; row++) {
		for (col = 0; col < width; col++) {
			*s++ = *t++;
		}
		s += (80 - width);
	}
	delete temp;
}

void win::put_ch(char c, int col, int row, int fcol)
{
	if (col <= (width - 1) && row <= length) {
		s = screen;
		s += (80 * row + col);
		*s = (((bcolor << 4) + fcol) << 8) + c;
	}
}

void win::put_str(char *str, int col, int row, int fcol)
{
	char c;
	while ((c = *str++) != NULL) {
		if (col >= (width - 1)) {
			row++;
			col -= (width - 2);
		}
		put_ch(c, col++, row, fcol);
	}
}

void win::chg_attr(int col, int row, int len, int fcol, int bcol)
{
	s = screen;

	s += (80 * row + col);
	while (len--) {
		*s = (*s & 0x00ff) + (((bcol << 4) + fcol) << 8);
		s++;
	}
}

void win::fill(int start_row, int end_row, char c, int fcol, int bcol)
{
	int row, col;
	s = screen;

	s += 80 * (start_row - 1);
	for (row = start_row; row <= end_row; row++) {
		for (col = 0; col < width; col++) {
			*s++ = (((bcol << 4) + fcol) << 8) + c;
		}
		s += (80 - width);
	}
}

class menu : public win
{
private:

	win w;
	int maxopt, width, fcolor, bcolor;

public:

	menu();
	menu(int wid, int max_opt, int fcol, int bcol);
	int get_opt(int col, int row, char *str[]);
};

menu::menu()
{
}

menu::menu(int wid, int max_opt, int fcol, int bcol)
{
	maxopt = max_opt;
	width = wid;
	fcolor = fcol;
	bcolor = bcol;
	w.create(width + 2, max_opt + 2, fcol, bcol, 1);
}

int menu::get_opt(int col, int row, char *str[])
{
	int opt, flag;
	char c;

	w.show(col, row);
	for (opt = 0; opt < maxopt; opt++)
		w.put_str(str[opt], 1, opt + 1, fcolor);
	w.save();

	flag = row = 1;
	w.chg_attr(1, row, width, 0xf, 0x0);
	do {
		c = getch();
		if (!c)
			c = getch();
		switch (c) {
		case 72:
			if (row > 1)
				w.chg_attr(1, row--, width, fcolor, bcolor);
			break;
		case 80:
			if (row < maxopt)
				w.chg_attr(1, row++, width, fcolor, bcolor);
			break;
		case 13:
			opt = row;
			flag = 0;
			break;
		case 27:
			opt = flag = 0;
			break;
		}
		w.chg_attr(1, row, width, 0xf, 0x0);
	} while (flag);
	w.hide();
	return opt;
}

class message : public win
{
private:

	win m;
	int maxopt, fcolor, bcolor, width, length;

public:

	message();
	message(int wid, int len, int max_opt, int fcol, int bcol);
	int get_opt(int col, int row, char *msg, char *str[]);
};

message::message()
{
}

message::message(int wid, int len, int max_opt, int fcol, int bcol)
{
	maxopt = max_opt;
	fcolor = fcol;
	bcolor = bcol;
	width = wid;
	length = len;
	m.create(wid + 2, len, fcol, bcol, 1);
}

int message::get_opt(int col, int row, char *msg, char *str[])
{
	int opt, flag;
	char c;

	m.show(col, row);
	m.put_str(msg, 2, 1, fcolor);
	row = length - 2;
	col = 5;
	for (opt = 0; opt < maxopt; opt++) {
		m.put_str(str[opt], col, row, fcolor);
		col += strlen(str[opt]) + 4;
	}
	m.save();

	flag = 1;
	col = 5;
	opt = 1;
	m.chg_attr(col - 1, row, strlen(str[0]) + 2, 0xf, 0x0);
	do {
		c = getch();
		if (!c)
			c = getch();
		switch (c) {
		case 75:
			if (opt > 1) {
				opt--;
				m.chg_attr(col - 1, row, strlen(str[opt]) + 2, fcolor, bcolor);
				col -= strlen(str[opt - 1]) + 4;
			}
			break;
		case 77:
			if (opt < maxopt) {
				opt++;
				m.chg_attr(col - 1, row, strlen(str[opt - 2]) + 2, fcolor, bcolor);
				col += strlen(str[opt - 2]) + 4;
			}
			break;
		case 13:
			flag = 0;
			break;
		case 27:
			opt = flag = 0;
			break;
		}
		if (opt)
			m.chg_attr(col - 1, row, strlen(str[opt - 1]) + 2, 0xf, 0x0);
	} while (flag);
	m.hide();
	return opt;
}

void main()
{
	win w;
	menu m[3];
	message mes;
	int opt;
	char ch;
	char *menu_opt[3][6] = {{"OPEN", "NEW", "SAVE", "SAVE AS", "PRINT", "QUIT"}, {"CUT", "COPY", "PASTE", "CLEAR"},
		{"FIND", "REPLACE", "GO TO", "SEARCH"}};
	char *str[2] = {"FILE       EDIT        SEARCH", "ALL FILES WILL BE DELETED !"};
	char *msg_opt[3] = {"CANCEL", "OK", "SKIP"};

	clrscr();
	w.create(80, 25, 0x0, 0x7, 0);
	w.show(1, 1);
	w.fill(2, 24, 0xb0, 0x1, 0x7);
	w.put_str(str[0], 1, 0, 0x0);
	m[0] = menu(10, 6, 0x0, 0x3);
	m[1] = menu(10, 3, 0x0, 0x3);
	m[2] = menu(10, 4, 0x0, 0x3);
	mes = message(30, 6, 3, 0xf, 0x4);
	do {
		ch = getch();
		switch (ch) {
		case 'f':
			opt = m[0].get_opt(1, 2, menu_opt[0]);
			gotoxy(1, 25);
			printf("%c-%d", ch, opt);
			break;
		case 'e':
			opt = m[1].get_opt(10, 2, menu_opt[1]);
			gotoxy(1, 25);
			printf("%c-%d", ch, opt);
			break;
		case 's':
			opt = m[2].get_opt(23, 2, menu_opt[2]);
			gotoxy(1, 25);
			printf("%c-%d", ch, opt);
			break;
		}
	} while (ch != 27);
	opt = mes.get_opt(10, 5, str[1], msg_opt);
	gotoxy(1, 25);
	printf("opt=%d", opt);
	getch();
	exit(0);
}

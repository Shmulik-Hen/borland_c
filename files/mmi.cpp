#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
	char *get_str(int col, int row);
	void chg_attr(int col, int row, int len, int fcol, int bcol);
	void fill(int start_row, int end_row, char c, int fcol, int bcol);
	int find_next(int col, int row);
	int find_prev(int col, int row);
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

char *win::get_str(int col, int row)
{
	char c, *str;
	int count;

	s = screen;
	s += (80 * row + col);
	while (!isupper(c = *s++))
		;
	s--;
	count = 0;
	while (isupper(str[count++] = *s++))
		;
	str[--count] = 0x0;
	return str;
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

int win::find_next(int col, int row)
{
	char c;

	s = screen;
	s += (80 * row + col);
	while (isupper(c = *s++))
		col++;
	while (!isupper(c = *s++))
		col++;
	return ++col;
}

int win::find_prev(int col, int row)
{
	char c;

	s = screen;
	s += (80 * row + --col);
	while (!isupper(c = *s--))
		col--;
	while (isupper(c = *s--))
		col--;
	return col;
}

class menu : public win
{
private:

	win w;
	int maxopt, width, fcolor, bcolor, row, col;

public:

	menu();
	menu(int wid, int max_opt, int fcol, int bcol, int m_col, int m_row, char *s[]);
	int get_opt();
};

menu::menu()
{
}

menu::menu(int wid, int max_opt, int fcol, int bcol, int m_col, int m_row, char *str[])
{
	int i;

	maxopt = max_opt;
	width = wid;
	fcolor = fcol;
	bcolor = bcol;
	row = m_row;
	col = m_col;
	w.create(width + 2, max_opt + 2, fcol, bcol, 1);
	w.show(col, row);
	for (i = 0; i < maxopt; i++)
		w.put_str(str[i], 1, i + 1, fcolor);
	w.save();
	w.hide();
}

int menu::get_opt()
{
	int opt, flag, y;
	char c;

	w.show(col, row);
	flag = y = 1;
	w.chg_attr(1, y, width, 0xf, 0x0);
	do {
		c = getch();
		if (!c)
			c = getch();
		switch (c) {
		case 72:
			if (y > 1)
				w.chg_attr(1, y--, width, fcolor, bcolor);
			break;
		case 75:
			opt = 75;
			flag = 0;
			break;
		case 77:
			opt = 77;
			flag = 0;
			break;
		case 80:
			if (y < maxopt)
				w.chg_attr(1, y++, width, fcolor, bcolor);
			break;
		case 13:
			opt = y;
			flag = 0;
			break;
		case 27:
			opt = flag = 0;
			break;
		}
		w.chg_attr(1, y, width, 0xf, 0x0);
	} while (flag);
	w.hide();
	return opt;
}

class message : public win
{
private:

	win m;
	int maxopt, fcolor, bcolor, width, length, row, col;

public:

	message();
	message(int wid, int len, int max_opt, int fcol, int bcol, int m_col, int m_row, char *msg, char *str[]);
	int get_opt();
};

message::message()
{
}

message::message(int wid, int len, int max_opt, int fcol, int bcol, int m_col, int m_row, char *msg, char *str[])
{
	int x, y, i;

	maxopt = max_opt;
	fcolor = fcol;
	bcolor = bcol;
	width = wid;
	length = len;
	row = m_row;
	col = m_col;
	m.create(wid + 2, len, fcol, bcol, 1);
	m.show(col, row);
	m.put_str(msg, 2, 1, fcolor);
	y = length - 2;
	x = 5;
	for (i = 0; i < maxopt; i++) {
		m.put_str(str[i], x, y, fcolor);
		x += strlen(str[i]) + 4;
	}
	m.save();
	m.hide();
}

int message::get_opt()
{
	int opt, flag, x, y;
	char c, *str;

	m.show(col, row);
	flag = 1;
	y = length - 2;
	x = 5;
	opt = 1;
	str = m.get_str(x, y);
	m.chg_attr(x - 1, y, strlen(str) + 2, 0xf, 0x0);
	do {
		c = getch();
		if (!c)
			c = getch();
		switch (c) {
		case 75:
			if (opt > 1) {
				opt--;
				m.chg_attr(x - 1, y, strlen(str) + 2, fcolor, bcolor);
				x = m.find_prev(x, y);
				str = m.get_str(x, y);
			}
			break;
		case 77:
			if (opt < maxopt) {
				opt++;
				m.chg_attr(x - 1, y, strlen(str) + 2, fcolor, bcolor);
				x = m.find_next(x, y);
				str = m.get_str(x, y);
			}
			break;
		case 13:
			flag = 0;
			break;
		case 27:
			opt = flag = 0;
			break;
		}
		m.chg_attr(x - 1, y, strlen(str) + 2, 0xf, 0x0);
	} while (flag);
	m.hide();
	return opt;
}

class dialog : public win
{
private:

	win d;
	char *str;
	int length, width;

public:

	dialog();
	dialog(int wid, int len, int fcol, int bcol, char *msg);
	char *get_txt();
};

dialog::dialog()
{
}

dialog::dialog(int wid, int len, int fcol, int bcol, char *msg)
{
	length = len;
	width = wid;
	d.create(wid, len, fcol, bcol, 1);
	d.show(1, 1);
	d.put_str(msg, 1, 1, fcol);
	d.save();
	d.hide();
}

char *dialog::get_txt()
{
	char c;
	int pos = 0;

	d.show(10, 12);
	d.chg_attr(1, 2, width - 2, 0x0, 0x3);
	while ((c = getch()) != '\r') {
		str[pos++] = c;
		d.put_ch(c, pos, 2, 0x0);
	}
	d.hide();
	str[pos] = 0x0;
	return str;
}

void main()
{
	win w;
	menu m[3];
	message mes;
	dialog d;
	int opt, i, x;
	char ch;
	char *filename;
	char *menu_opt[3][6] = {{"OPEN", "NEW", "SAVE", "SAVE AS", "PRINT", "QUIT"}, {"CUT", "COPY", "PASTE", "CLEAR"},
		{"FIND", "REPLACE", "GO TO", "SEARCH"}};
	char *str[3] = {"FILE       EDIT        SEARCH", "ALL FILES WILL BE DELETED !", "ENTER FILE NAME"};
	char *msg_opt[3] = {"CANCEL", "OK", "SKIP"};

	w.create(80, 25, 0x0, 0x7, 0);
	m[0] = menu(10, 6, 0x0, 0x3, 1, 2, menu_opt[0]);
	m[1] = menu(10, 3, 0x0, 0x3, 10, 2, menu_opt[1]);
	m[2] = menu(10, 4, 0x0, 0x3, 23, 2, menu_opt[2]);
	mes = message(30, 6, 3, 0xf, 0x4, 10, 5, str[1], msg_opt);
	d = dialog(30, 4, 0x0, 0x7, str[2]);

	clrscr();
	w.show(1, 1);
	w.fill(2, 24, 0xb0, 0x1, 0x7);
	w.put_str(str[0], 1, 0, 0x0);
	do {
		ch = getch();
		if (!ch)
			ch = getch();
redo:
		switch (ch) {
		case 33:
			i = 0;
			break;
		case 18:
			i = 1;
			break;
		case 31:
			i = 2;
			break;
		case 75:
			if (i > 0)
				i--;
			break;
		case 77:
			if (i < 2)
				i++;
			break;
		default:
			continue;
		}
		opt = m[i].get_opt();
		if (opt == 75 || opt == 77) {
			ch = opt;
			goto redo;
		}
		gotoxy(1, 25);
		printf("opt=%d", opt);
	} while (ch != 27);
	opt = mes.get_opt();
	gotoxy(1, 25);
	printf("opt=%d", opt);
	filename = d.get_txt();
	gotoxy(1, 25);
	printf("%s", filename);
	getch();
	exit(0);
}

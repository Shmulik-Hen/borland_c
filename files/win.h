#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <colors.h>

class win
{
protected:

	unsigned int *buffer, *temp, *b, *t;
	unsigned int far *screen, far *s;
	int width, length, fcolor, bcolor, buf_size;

public:

	win();
	~win();
	win(int wid, int len, int fcol, int bcol, int border);
	void show(int col, int row);
	void save();
	void hide();
	void put_ch(char c, int col, int row, int fcol);
	void put_str(char *str, int col, int row, int fcol);
	void get_str(char s[], int col, int row, int len, int fcol);
	void chg_attr(int col, int row, int len, int fcol, int bcol);
	void fill(int start_row, int end_row, char c, int fcol, int bcol);
	int find_next(int col, int row);
	int find_prev(int col, int row);
};

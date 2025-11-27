#ifndef _WIN.H
#define _WIN .H
class win
{
	int x, y, width, height, size;
	int xc, yc, fcolor, bcolor;
	int *fg, *bg;
	static int count;
	int id;

public:

	win();
	~win();
	win(int, int, int);
	void show(int, int);
	void hide();
	void save();
	void select();
	void unselect();
	int ch2int(int);
	void type_in();
};
#endif

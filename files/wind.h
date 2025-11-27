#ifndef _WIND.H
#define _WIND	 .H
#define CLIP_ON	 1
#define CLIP_OFF 0

class my_window
{
private:

	int height, width;
	int pos_x, pos_y;
	unsigned int size;
	int visible, first, frame;
	void *foreground, *background;
	void *curr, *prev;

public:

	my_window();
	~my_window();
	my_window(int h, int w, int f);
	void show(int x, int y);
	void hide();
	void save();
	void put_char(int x, int y, char c);
	void put_str(int x, int y, char *s);
	void highlight(int x1, int y1, int x2, int y2);
	void de_highlight(int x1, int y1, int x2, int y2);
};
#endif

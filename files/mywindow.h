#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <alloc.h>

class wind{
	   private:
	     void *buf;
	     int xstart, ystart;
	     int xend, yend;
	   public:
	     wind();
	     wind(int xs, int ys, int xe, int ye);
	     ~wind();
	     void save(int xs, int ys, int xe, int ye);
	     void show(int x,int y);
	     void hide();
	     void puttext(int row, int col, char *str);
	  };

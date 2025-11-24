#ifndef _MENU.H
#define _MENU.H
#include <wind.h>

class my_menu:public my_window{
	   private:
	     int x_pos,y_pos;
	     int y_inc;
	     int rows;
	     int width,height;
	   public:
	     my_menu();
	     ~my_menu();
	     my_menu(int x,int y,int r,char *s[]);
	     int choice();
	     friend int longest(int r,char *s[]);
	  };
#endif
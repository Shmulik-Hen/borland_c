#ifndef _UTILS.H
#define _UTILS.H
#include <point.h>
void LocToStr(char *s,int x, int y);
void keyboard_things();
void mouse_things();
void standart_things();
void draw_screen();
void identify_location(POINT p);
void beep();
void do_open();
void do_close();
void do_save();
void do_exit();
void do_average();
void message(char *s);
#endif

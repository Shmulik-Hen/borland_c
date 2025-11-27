/**************************************************************************
 * SUBJECT:    FLIGHT SIMULATOR.                                           *
 *                                                                         *
 * TITLE:      GRADUATION PROJECT.                                         *
 *                                                                         *
 * FILE NAME:  graphics.h                                                  *
 *                                                                         *
 * PURPOSE:    function declarations for fast SVGA graphics library.       *
 **************************************************************************/
#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#define MAX_X 320
#define MAX_Y 200
typedef char palette[3];
void setcolor(char color);
void line(int left, int top, int right, int bottom);
void lineto(int x, int y);
void bar(int left, int top, int right, int bottom);
void fillpoly(int numpoints, int far *polypoints);
void cleardevice();
void outtextxy(int x, int y, char *str);
void putch(int x, int y, char c);
void initgraph();
void closegraph();
void setviewport(int left, int top, int right, int bottom);
void clearviewport();
void getpalette(palette buff[], int colors);
void setpalette(palette buff[], int colors);
void init_palette();
void flip_page();
#endif

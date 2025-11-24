#ifndef _MOUSE.H
#define _MOUSE.H
#include <point.h>
int InitMouse();
void ShowMouse();
void HideMouse();
int MouseDownLeft();
int MouseDownRight();
int MousePressed();
void GetMouseLocation(POINT *p);
void SetMouseLocation(POINT p);
int between(POINT v,int x1,int y1,int x2,int y2);
#endif

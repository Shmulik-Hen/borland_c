#include <dos.h>
#include <mouse.h>

int InitMouse()
{
	union REGS r;

	r.x.ax = 0;
	int86(0x33, &r, &r);
	return r.x.ax;
}

void HideMouse()
{
	union REGS r;

	r.x.ax = 2;
	int86(0x33, &r, &r);
}

void ShowMouse()
{
	union REGS r;

	r.x.ax = 1;
	int86(0x33, &r, &r);
}

int MousePressed()
{
	union REGS r;

	r.x.ax = 3;
	int86(0x33, &r, &r);
	return (r.x.bx & 0x03);
}

int MouseDownLeft()
{
	union REGS r;

	r.x.ax = 3;
	int86(0x33, &r, &r);
	return (r.x.bx & 0x01);
}

int MouseDownRight()
{
	union REGS r;

	r.x.ax = 3;
	int86(0x33, &r, &r);
	return (r.x.bx & 0x02);
}

void GetMouseLocation(POINT *p)
{
	union REGS r;

	r.x.ax = 3;
	int86(0x33, &r, &r);
	p->x = r.x.cx;
	p->y = r.x.dx;
}

void SetMouseLocation(POINT p)
{
	union REGS r;

	r.x.ax = 4;
	r.x.cx = p.x;
	r.x.dx = p.y;
	int86(0x33, &r, &r);
}

int between(POINT v, int x1, int y1, int x2, int y2)
{
	if (v.x >= x1 && v.x <= x2 && v.y >= y1 && v.y <= y2)
		return 1;
	return 0;
}

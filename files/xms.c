#include <dos.h>
#include <stdio.h>
typedef struct
{
	long count;
	int srchndl;
	unsigned long srcoff;
	int dsthndl;
	unsigned long dstoff;
} MovStruc;
void far (*XMS_routine)();
int XMS_kayam()
{
	union REGS r;
	r.x.ax = 0x4300;
	int86(0x2f, &r, &r);
	return (r.h.al == 0x80);
}

void XMS_getentry()
{
	_AX = 0x4310;
	geninterrupt(0x2f);
	(void far *)XMS_routine = MK_FP(_ES, _BX);
}
int XMS_alloc(int kilobyte)
{
	_AH = 0x9;
	_DX = kilobyte;
	(*XMS_routine)();
	return (_AX == 1);
}

int XMS_releas(int handle)
{
	_AX = 0xa;
	_DX = handle;
	(*XMS_routine)();
	return (_AX == 1);
}

int XMS_move(MovStruc *m)
{
	union REGS r;
	_AH = 0xb;
	_SI = FP_OFF(m);
	(*XMS_routine)();
	return (_AX == 1);
}

long XMS_avail()
{
	long retval;
	_AH = 8;
	(*XMS_routine)();
	return (1);
}

main()
{
	int handle;
	printf("%d", XMS_kayam());
	XMS_getentry();
	XMS_alloc(20);
	XMS_avail();
}

#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <string.h>
char far *pscr = (char far *)0xb8000000L;

void interrupt (*int_67)(...);

int EMS_kayam()
{
	static char *em_name = "EMMXXXX0";
	char far *drvrp;
	int i;
	int_67 = getvect(0x67);
	drvrp = (char far *)MK_FP(_ES, 0xa);
	for (i = 0; i < strlen(em_name); i++)
		if (em_name[i] != drvrp[i])
			return (0);
	return (1);
}

int EMS_avail()
{
	if (EMS_kayam()) {
		_AH = 0x42;
		geninterrupt(0x67);
		if (!_AH)
			return (_BX);
	}
	return (0);
}

int EMS_total()
{
	if (EMS_kayam()) {
		_AH = 0x42;
		geninterrupt(0x67);
		if (!_AH)
			return (_DX);
	}
	return (0);
}
unsigned EMS_alloc(int numpages)
{
	if (EMS_kayam) {
		_AH = 0x43;
		_BX = numpages;
		geninterrupt(0x67);
		if (!_AH)
			return (_DX);
	}
	return (0);
}

int EMS_release(unsigned handle)
{
	union REGS my;
	my.h.ah = 0x45;
	my.x.dx = handle;
	if (EMS_kayam()) {
		int86(0x67, &my, &my);
		if (!my.h.ah)
			return (1);
	}
	return (0);
}
int EMS_map_pages(unsigned handle, char p_page, int l_page)
{
	if (EMS_kayam()) {
		_AH = 0x44;
		_AL = p_page;
		_BX = l_page;
		_DX = handle;
		geninterrupt(0x67);
		if (!_AH)
			return (1);
	}
	return (0);
}

char far *EMS_pg0_ptr()
{
	char far *rptr;
	if (EMS_kayam()) {
		_AH = 0x41;
		geninterrupt(0x67);
		if (!_AH) {
			rptr = (char far *)MK_FP(_BX, 0);
			return (rptr);
		}
	}
	return (0);
}

char far *EMS_pg1_ptr()
{
	char far *rptr;
	if (EMS_kayam()) {
		_AH = 0x41;
		geninterrupt(0x67);
		if (!_AH) {
			rptr = (char far *)MK_FP(_BX, 0x4000);
			return (rptr);
		}
	}
	return (0);
}

char far *EMS_pg2_ptr()
{
	char far *rptr;
	if (EMS_kayam()) {
		_AH = 0x41;
		geninterrupt(0x67);
		if (!_AH) {
			rptr = (char far *)MK_FP(_BX, 0x8000);
			return (rptr);
		}
	}
	return (0);
}

char far *EMS_pg3_ptr()
{
	char far *rptr;
	if (EMS_kayam()) {
		_AH = 0x41;
		geninterrupt(0x67);
		if (!_AH) {
			rptr = (char far *)MK_FP(_BX, 0xc000);
			return (rptr);
		}
	}
	return (0);
}
main()
{
	int a;
	int handle;
	char far *my;
	int status;
	a = EMS_kayam();
	clrscr();
	printf("\na=%d\n", a);
	handle = EMS_alloc(4);
	printf("handle=%d\n", handle);
	status = EMS_map_pages(handle, 0, 0);
	printf("status=%d\n", status);
	status = EMS_map_pages(handle, 1, 1);
	printf("status=%d\n", status);
	status = EMS_map_pages(handle, 2, 2);
	printf("status=%d\n", status);
	status = EMS_map_pages(handle, 3, 3);
	printf("status=%d\n", status);
	getch();
	my = EMS_pg0_ptr();
	*my = '0';
	*pscr = *my;
	pscr += 2;
	my = EMS_pg1_ptr();
	*my = '1';
	*pscr = *my;
	pscr += 2;
	my = EMS_pg2_ptr();
	*my = '2';
	*pscr = *my;
	pscr += 2;
	my = EMS_pg3_ptr();
	*my = '3';
	*pscr = *my;
	pscr += 2;
	getch();
	status = EMS_release(handle);
	printf("status=%d\n", status);
	getch();
}

#include <dos.h>
#include <string.h>

class ems
{
	static char *em_name;
	static char far *drvrp;
	int handle;
	void interrupt (*int_67)(...);
	unsigned alloc(int numpages);
	int kayam();
	int release(unsigned handle);
	int map_pages(unsigned handle, char p_page, int l_page);
	char far *get(int page);
	char far *pg0_ptr();
	char far *pg1_ptr();
	char far *pg2_ptr();
	char far *pg3_ptr();

public:

	ems(int numpages);
	~ems();
	void write(char *buffer, int count, int pos, int page);
	void read(char *buffer, int count, int pos, int page);
	int avail();
	int total();
};

int ems::kayam()
{
	int i;
	em_name = "EMMXXXX0";
	int_67 = getvect(0x67);
	drvrp = (char far *)MK_FP(_ES, 0xa);
	for (i = 0; i < strlen(em_name); i++)
		if (em_name[i] != drvrp[i])
			return (0);
	return (1);
}

int ems::total()
{
	if (kayam()) {
		_AH = 0x42;
		geninterrupt(0x67);
		if (!_AH)
			return (_DX);
	}
	return (0);
}

int ems::avail()
{
	if (kayam()) {
		_AH = 0x42;
		geninterrupt(0x67);
		if (!_AH)
			return (_BX);
	}
	return (0);
}

unsigned ems::alloc(int numpages)
{
	if (kayam()) {
		_AH = 0x43;
		_BX = numpages;
		geninterrupt(0x67);
		if (!_AH)
			return (_DX);
	}
	return (0);
}

ems::ems(int numpages)
{
	if (kayam())
		handle = alloc(numpages);
	else
		handle = 0;
}

char far *ems::pg0_ptr()
{
	char far *rptr;
	if (kayam()) {
		_AH = 0x41;
		geninterrupt(0x67);
		if (!_AH) {
			rptr = (char far *)MK_FP(_BX, 0);
			return (rptr);
		}
	}
	return (0);
}

int ems::map_pages(unsigned handle, char p_page, int l_page)
{
	if (kayam()) {
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

void ems::write(char *buffer, int count, int pos, int page)
{
	char far *p;
	int i;

	p = get(page);
	p += pos;
	for (i = 0; i < count; i++)
		*p++ = *buffer++;
}

void ems::read(char *buffer, int count, int pos, int page)
{

	char far *p;
	int i;

	p = get(page);
	p += pos;
	for (i = 0; i < count; i++)
		*buffer++ = *p++;
}

char far *ems::get(int page)
{
	if (map_pages(handle, page, 0)) {
		return (pg0_ptr());
	}
	return (0);
}

ems::~ems()
{
	release(handle);
}

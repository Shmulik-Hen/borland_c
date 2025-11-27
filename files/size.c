#include <stdio.h>
#include <conio.h>

void main()
{
	int size;

	clrscr();
	char *p1;
	unsigned char *p2;
	int *p3;
	unsigned int *p4;
	short *p5;
	unsigned short *p6;
	long *p7;
	unsigned long *p8;
	float *p9;
	double *p10;
	long double *p11;
	size = sizeof(*p1);
	printf("size of \"char\" in bytes is %d\n", size);
	size = sizeof(*p2);
	printf("size of \"unsigned char\" in bytes is %d\n", size);
	size = sizeof(*p3);
	printf("size of \"int\" in bytes is %d\n", size);
	size = sizeof(*p4);
	printf("size of \"unsigned int\" in bytes is %d\n", size);
	size = sizeof(*p5);
	printf("size of \"short\" in bytes is %d\n", size);
	size = sizeof(*p6);
	printf("size of \"unsigned short\" in bytes is %d\n", size);
	size = sizeof(*p7);
	printf("size of \"long\" in bytes is %d\n", size);
	size = sizeof(*p8);
	printf("size of \"unsigned long\" in bytes is %d\n", size);
	size = sizeof(*p9);
	printf("size of \"float\" in bytes is %d\n", size);
	size = sizeof(*p10);
	printf("size of \"double\" in bytes is %d\n", size);
	size = sizeof(*p11);
	printf("size of \"long double\" in bytes is %d\n", size);
}

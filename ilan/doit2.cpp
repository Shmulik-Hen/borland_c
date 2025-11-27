
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>

FILE *f1, *f2;
int number, counter;

int main(void)
{
	/* select a driver and mode that supports the use */
	/* of the setrgbpalette function.                 */
	int gdriver = VGA, gmode = VGAHI, errorcode;

	initgraph(&gdriver, &gmode, "d:\\bc\\bgi");

	/* read result of initialization */

	errorcode = graphresult();
	if (errorcode != grOk) /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1); /* terminate with an error code */
	}

	setrgbpalette(1, 0, 0, 0);
	setfillstyle(1, 1);

	if ((f1 = fopen("d:\\bc\\ilan\\file1.cpp", "rt")) == NULL)
		exit(1);
	for (counter = 0; counter < 6; counter++) {
		fscanf(f1, "%d\n", &number);
		bar(counter * 100, 479, counter * 100 + 60, 479 - number);
	}
	for (counter = 0; counter < 64; counter++)
		setrgbpalette(1, counter, 0, counter);
	delay(1000);
	for (counter = 63; counter > 0; counter--)
		setrgbpalette(1, counter, 0, counter);
	cleardevice();
	if ((f2 = fopen("file2.cpp", "rt")) == NULL)
		exit(1);
	for (counter = 0; counter < 6; counter++) {
		fscanf(f2, "%d\n", &number);
		bar(counter * 100, 479, counter * 100 + 60, 479 - number);
	}
	for (counter = 0; counter < 64; counter++)
		setrgbpalette(1, counter, 0, counter);
	delay(1000);
	for (counter = 63; counter > 0; counter--)
		setrgbpalette(1, counter, 0, counter);

	closegraph();
	return 0;
}

#include <stdio.h>
#include <conio.h>
#include <process.h>
#include <dos.h>

void main()
{
	int c = 0x00, c1;
	int d3, d2, d1, i;
	char str[10] = "";

	clrscr();
	do {
		c1 = c;
		d3 = d2 = d1 = 3;

		for (i = 0; i < 8; i++) {
			if (c1 & 0x80) {
				d3++;
				if (d3 == 4)
					d3 = 1;
				d2++;
				if (d2 == 4)
					d2 = 1;
				str[i] = 'L';
				str[i + 1] = NULL;
			}
			else {
				d1++;
				if (d1 == 4)
					d1 = 1;
				d2++;
				if (d2 == 4)
					d2 = 1;
				str[i] = 'R';
				str[i + 1] = NULL;
			}
			// delay(100);
			if ((d3 == 2 && d2 == 2 && d1 == 1) || (d3 == 1 && d2 == 2 && d1 == 2)) {
				printf("%c", 0x07);
				printf("%s", str);
				exit(0);
			}
			c1 = c1 << 1;
		}
		printf("%4d %4d %2d %2d %2d %s\n", c, c1, d3, d2, d1, str);
		c++;
	} while (c < 256);
}

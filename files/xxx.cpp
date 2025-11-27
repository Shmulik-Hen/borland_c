#include <stdio.h>
#include <conio.h>

void main()
{
	char c;
	int i = 0;

	clrscr();
	while (!i) {
		c = getch();
		// if(!c)
		// c=getch();
		printf("%c %d\n", c, c);
		if (c == 27)
			i = 1;
	}
}

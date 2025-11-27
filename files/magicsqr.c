#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define ARRAY 5

typedef struct
{
	int num;
	int full;
} spot;

void main()
{
	int x, y, nextx, nexty;
	int i, row, col;
	spot table[ARRAY][ARRAY];

	clrscr();
	if (((i = ARRAY) % 2) == 0) {
		puts("only odd numbers are allowed");
		puts("press any key");
		getch();
		exit(i);
	}
	for (y = 0; y < ARRAY; y++)
		for (x = 0; x < ARRAY; x++) {
			table[x][y].full = 0;
			table[x][y].num = 0;
		}
	x = y = 0;
	nextx = (ARRAY + 1) / 2;
	nexty = 1;
	i = 1;
	while (i <= (ARRAY * ARRAY)) {
		nextx--;
		if (nextx < 0)
			nextx = (ARRAY - 1);
		nexty--;
		if (nexty < 0)
			nexty = (ARRAY - 1);
		if (table[nextx][nexty].full != 1) {
			x = nextx;
			y = nexty;
			table[x][y].num = i;
			table[x][y].full = 1;
		}
		else {
			y++;
			table[x][y].num = i;
			table[x][y].full = 1;
			nextx = x;
			nexty = y;
		}
		i++;
	}
	row = (25 - ARRAY) / 2;
	col = (80 - ARRAY * 4) / 2;
	for (y = 0; y < ARRAY; y++) {
		gotoxy(col, row);
		for (x = 0; x < ARRAY; x++) {
			printf("%4d", table[x][y].num);
			if (x % ARRAY == 0)
				row++;
		}
	}
	gotoxy(1, 23);
	puts("press any key");
	getch();
}

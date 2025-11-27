#include <stdio.h>
#include <conio.h>
#include <dos.h>

int neighbours(int row, int col);
void prnt(void);
void copy_array(void);
void get_life(void);
void grid(void);
void initial(void);

int old_gen[12][12];
int new_gen[12][12];
int first;

void main()
{
	int row, col, n, flag, gen, count;

	initial();
	do {
		for (row = 0; row <= 11; row++) {
			for (col = 0; col <= 11; col++)
				old_gen[row][col] = new_gen[row][col] = 0;
		}
		get_life();
		gotoxy(1, 11);
		puts("enter number of");
		puts("generations");
		scanf("%d", &count);
		puts("");
		puts("press any key");
		puts("to start");
		getch();
		first = 1;
		gen = 1;
		do {
			flag = 0;
			for (row = 1; row <= 10; row++) {
				for (col = 1; col <= 10; col++) {
					n = neighbours(row, col);
					if ((n > 1) && (n <= 3)) {
						new_gen[row][col] = 1;
						flag = 1;
					}
					else
						new_gen[row][col] = 0;
				}
			}
			prnt();
			copy_array();
			if (flag == 0) {
				prnt();
				gotoxy(1, 22);
				puts("pupolation is dead.");
				break;
			}
			gotoxy(1, 22);
			printf("generation No.%d", gen++);
			delay(1000);
			count--;
		} while (count);
		gotoxy(1, 23);
		puts("press any key");
		puts("or Q to quit");
	} while (getch() != 'q');
}

int neighbours(int row, int col)

{
	int x, y, n = 0;

	for (y = (row - 1); y <= (row + 1); y++) {
		for (x = (col - 1); x <= (col + 1); x++) {
			if (old_gen[y][x] == 1)
				n++;
		}
	}
	if (old_gen[row][col] == 1)
		return n - 1;
	else
		return n;
}

void prnt(void)

{
	int row, col, x, y;

	if (first) {
		clrscr();
		grid();
		gotoxy(35, 2);
		puts("LIFE - GAME");
		first = 0;
	}
	y = 4;
	for (row = 1; row <= 10; row++) {
		x = 22;
		for (col = 1; col <= 10; col++) {
			if (new_gen[row][col] == 1) {
				gotoxy(x, y);
				textcolor(12);
				putch('*');
				textcolor(15);
			}
			else {
				gotoxy(x, y);
				putch(32);
			}
			x += 4;
		}
		y += 2;
	}
	gotoxy(1, 24);
}

void copy_array(void)

{
	int row, col;

	for (row = 1; row <= 10; row++) {
		for (col = 1; col <= 10; col++)
			old_gen[row][col] = new_gen[row][col];
	}
}

void get_life(void)
{

	int x, y, row, col, flag;
	char key;

	clrscr();
	grid();
	gotoxy(35, 2);
	puts("LIFE - GAME");
	gotoxy(1, 3);
	puts("use arraaows");
	puts("and use +,-");
	puts("to fill the");
	puts("first generation.");
	puts("");
	puts("press Q to stop");
	x = 22;
	y = 4;
	row = 1;
	col = 1;
	flag = 1;
	gotoxy(x, y);
	do {
		switch (key = getch()) {
		case '8':
			if (row <= 1)
				break;
			y -= 2;
			row--;
			gotoxy(x, y);
			break;
		case '2':
			if (row >= 10)
				break;
			y += 2;
			row++;
			gotoxy(x, y);
			break;
		case '6':
			if (col >= 10)
				break;
			x += 4;
			col++;
			gotoxy(x, y);
			break;
		case '4':
			if (col <= 1)
				break;
			x -= 4;
			col--;
			gotoxy(x, y);
			break;
		case '+':
			gotoxy(x, y);
			textcolor(12);
			putch('*');
			textcolor(15);
			old_gen[row][col] = 1;
			gotoxy(x, y);
			break;
		case '-':
			gotoxy(x, y);
			putch('');
			old_gen[row][col] = 0;
			gotoxy(x, y);
			break;
		case 'q':
			flag = 0;
			break;
		default:
			break;
		}
	} while (flag);
}

void grid(void)

{
	int x, y, i;

	x = 20;
	y = 3;
	clrscr();
	gotoxy(x, y);
	puts("���������������������������������������ͻ");
	for (i = 1; i < 10; i++) {
		gotoxy(x, ++y);
		puts("�   �   �   �   �   �   �   �   �   �   �");
		gotoxy(x, ++y);
		puts("���������������������������������������Ķ");
	}
	gotoxy(x, ++y);
	puts("�   �   �   �   �   �   �   �   �   �   �");
	gotoxy(x, ++y);
	puts("���������������������������������������ͼ");
}

void initial(void)

{

	int row, col;
	clrscr();
	gotoxy(30, 2);
	puts("LIFE - GAME");
	puts("");
	puts("the object of this game is to calculate the population of microbs.");
	puts("the program, based on an existing generation, will find the next");
	puts("generation by few simple rules as the following:");
	puts("");
	puts("1. A MICROB THAT HAS NO NEIGHBOURS WILL DYE OF LONELINESS");
	puts("2. A MICROB WITH TO MENY NEIGHBOURS WILL DYE OF OVER POPULATION");
	puts("3. A MICROB WITH ONLY TWO NEIGHBOURS WILL SURVIVE");
	puts("4. BETWEEN EVERY TWO MICROBS A NEW ONE WILL BE BORN");
	puts("");
	puts("press any key to start.");
	getch();
}

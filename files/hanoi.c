#include <stdio.h>
#include <conio.h>

void towers(int num, char pole_A, char pole_C, char pole_B);

main()
{
	int disk_num;

	clrscr();
	gotoxy(30, 1);
	puts("TOWERS OF HANOI");
	printf("\n\n\n");
	puts("enter the number of disks - ");
	gotoxy(29, 5);
	scanf("%d", &disk_num);

	towers(disk_num, 'A', 'C', 'B');
}

void towers(int num, char pole_A, char pole_C, char pole_B)
{
	if (num == 1)
		printf("move disk 1 form %c to %c\n", pole_A, pole_C);
	else {
		towers(num - 1, pole_A, pole_B, pole_C);
		printf("move disk %d from %c to %c\n", num, pole_A, pole_C);
		towers(num - 1, pole_B, pole_C, pole_A);
	}
}

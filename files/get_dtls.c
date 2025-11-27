#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define SIZE 3
typedef struct
{
	char name[10];
	char lastname[10];
	long id;
	int grade;
} record;

void main()
{
	record person[SIZE], *ptr[SIZE];
	int i;

	clrscr();
	for (i = 0; i < SIZE; i++) {
		ptr[i] = &person[i];
		scanf("%10s %10s %ld %d", ptr[i]->name, ptr[i]->lastname, &ptr[i]->id, &ptr[i]->grade);
	}
	clrscr();
	for (i = 0; i < SIZE; i++)
		printf("%s\t%s\t%ld\t%d\n", ptr[i]->name, ptr[i]->lastname, ptr[i]->id, ptr[i]->grade);
	getch();
}

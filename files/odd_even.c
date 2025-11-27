/*this program finds wether a number is odd or even*/

#include <stdio.h>
#include <conio.h>

void main()
{
	int a;
	clrscr();
	puts("this program finds wether a number is odd  or even");
	puts("input a number");
	scanf("%d", &a);
	if ((a % 2) == 1)
		printf("odd\n");
	else
		printf("even\n");
}

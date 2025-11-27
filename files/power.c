#include <stdio.h>
#include <conio.h>

int power(int base, int exp);

void main()
{
	int result, base, exp;

	clrscr();
	puts("this program calculates the power of base ^ exp");
	puts("input the base number");
	scanf("%d", &base);
	puts("input the exp");
	scanf("%d", &exp);
	result = power(base, exp);
	printf(" %d ^ %d = %d", base, exp, result);
}

int power(int base, int exp)
{
	int i, result;

	result = 1;
	for (i = 1; i <= exp; i++)
		result *= base;
	return result;
}

#include <stdio.h>
#include <conio.h>
#include <math.h>
#define FALSE 0
#define TRUE  1

int prime(int num);

void main()
{
	int i, number, count;

	clrscr();
	puts("this program finds the N'th prime number");
	puts("input a number");
	scanf("%d", &number);
	i = count = 0;
	while (count < number) {
		if (prime(++i) == TRUE)
			count++;
	}
	printf("the %d'th prime number is %d", number, i);
}

int prime(int num)
{
	int i, flag, top_val;

	i = 2;
	flag = TRUE;
	top_val = floor(sqrt(num));
	while ((flag == TRUE) && (i <= top_val)) {
		if (num % i == 0)
			flag = FALSE;
		i++;
	}
	return flag;
}

#include <stdio.h>
#include <conio.h>
#include <math.h>
#define TRUE  1
#define FALSE 0

int fprime(int num);

void main()
{
	int i, count, num;
	count = 0;
	clrscr();
	puts("this program calculates the amount of prime numbers between 1 and N");
	puts("input N");
	scanf("%d", &num);
	for (i = 1; i <= num; i++) {
		if (fprime(i) == TRUE)
			count++;
	}
	printf("the amount of prime numbers from 1 to %d is %d", num, count);
}

int fprime(int num)
{
	int i, flag, top_val;

	i = 2;
	flag = TRUE;
	top_val = (floor(sqrt(num)));
	while ((flag == TRUE) && (i <= top_val)) {
		if (num % i == 0)
			flag = FALSE;
		i++;
	}
	return flag;
}

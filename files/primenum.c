#include <stdio.h>
#include <conio.h>
#include <math.h>

void main()
{
	int i, num, flag, top_val;

	do {
		i = 2;
		flag = 1;
		clrscr();
		puts("this program finds wether a number is prime or composite");
		puts("input a number");
		scanf("%d", &num);
		top_val = (floor(sqrt(num)));
		while ((flag == 1) && (i <= top_val)) {
			if (num % i == 0)
				flag = 0;
			i++;
		}
		if (flag == 1)
			puts("this is a prime number\n");
		else
			puts("this is a composite number\n");
		puts("press 'q' to quit");
		puts("any other key yo continue");
	} while (getch() != 'q');
}

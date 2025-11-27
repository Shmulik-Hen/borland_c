#include <stdio.h>
#include <conio.h>

int fib(int num);

main()
{
	int n, res;

	do {
		clrscr();
		puts("input a number");
		scanf("%d", &n);
		res = fib(n);
		printf("the %d'th FIBONACI'S number is %d", n, res);
	} while (getch() != 'q');
}

int fib(int num)
{
	int i, a, b, c;
	a = 0;
	b = 1;
	if (num == 1)
		return 0;
	if (num == 2)
		return 1;
	for (i = 1; i <= (num - 2); i++) {
		c = a + b;
		a = b;
		b = c;
	}
	return c;
}

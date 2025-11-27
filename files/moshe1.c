#include <stdio.h>
#include <conio.h>
#include <math.h>

int is_primary(int x);

void main()
{
	int n, i, j, flag1, flag2;

	clrscr();
	printf("this program checks orbach's assumption\n");

	n = 2;
	flag1 = 1;
	while (flag1 != 0 && n <= 10000) {
		i = 1;
		flag2 = 1;
		while (flag2 != 0 && i <= (n / 2)) {
			j = n - i;
			if (is_primary(i) && is_primary(j))
				flag2 = 0;
			else
				i = i + 1;
		}
		if (flag2 == 1)
			flag1 = 0;
		else
			n = n + 2;
	}
	if (flag1 == 0)
		printf("wrong assumption");
	else
		printf("right assumption");
}

int is_primary(int x)
{
	int i, flag, root;

	root = (int)floor(sqrt(x));
	flag = 1;
	i = 2;
	while (flag != 0 && i <= root)
		if ((x % i) == 0)
			flag = 0;
	return flag;
}

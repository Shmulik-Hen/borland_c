/*SHEVER VER 1.0*/
#include <stdio.h>
#include <conio.h>

class fraction
{
private:

	int num;
	int den;

public:

	fraction();
	fraction(int n, int d);
	fraction operator+(fraction &f);
	fraction operator-(fraction &f);
	fraction operator*(fraction &f);
	fraction operator/(fraction &f);
	void print();
};

fraction::fraction()
{
	num = 0;
	den = 1;
}

fraction::fraction(int n, int d)
{
	if (d == 0)
		d = 1;
	if (n > d)
		n %= d;
	num = n;
	den = d;
}

fraction fraction::operator+(fraction &f)
{
	return fraction((num * f.den) + (den * f.num), (den * f.den));
}

fraction fraction::operator-(fraction &f)
{
	return fraction((num * f.den) - (den * f.num), (den * f.den));
}

fraction fraction::operator*(fraction &f)
{
	return fraction((num * f.num), (den * f.den));
}

fraction fraction::operator/(fraction &f)
{
	return fraction((num * f.den), (den * f.num));
}

void fraction::print()
{
	printf("%2d\n", num);
	printf("---\n");
	printf("%2d\n\n", den);
}

void main()
{
	int n, d;
	fraction a, b, c;

	clrscr();
	printf("enter first fraction ");
	scanf("%d %d", &n, &d);
	a = fraction(n, d);
	printf("enter second fraction ");
	scanf("%d %d", &n, &d);
	b = fraction(n, d);
	c = a + b;
	c.print();
	c = a - b;
	c.print();
	c = a * b;
	c.print();
	c = a / b;
	c.print();
	getch();
}

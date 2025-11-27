/*POINT VER 2.0*/
/*CONSTRUCTOR ROUTINE*/
#include <stdio.h>
#include <conio.h>
#include <math.h>

class point
{
private:

	int x;
	int y;

public:

	point();
	point(int m_x, int m_y);
	void print();
	point operator+(point &p);
	double operator-(point &p);
};

point::point()
{
	x = y = 0;
}

point::point(int m_x, int m_y)
{
	x = m_x;
	y = m_y;
	if (x < 0)
		x = 0;
	if (x > 80)
		x = 80;
	if (y < 0)
		y = 0;
	if (y > 25)
		y = 25;
}

void point::print()
{
	printf("%d,%di\n", x, y);
}

point point::operator+(point &p)
{
	return point(x + p.x, y + p.y);
}

double point::operator-(point &p)
{
	return sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y));
}

void main()
{
	point a, b, c;
	double dist;
	int m_y, m_x;

	clrscr();
	printf("enter x_val and y_val of a ");
	scanf("%d %d", &m_x, &m_y);
	a = point(m_x, m_y);
	printf("enter x_val and y_val of b ");
	scanf("%d %d", &m_x, &m_y);
	b = point(m_x, m_y);
	c = a + b;
	dist = b - a;
	a.print();
	b.print();
	c.print();
	printf("%3.3f", dist);
	getch();
}

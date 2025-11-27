#include <stdio.h>
#include <conio.h>

void main()
{
	float radius, length, area;
	clrscr();
	puts("this program calculates the length and area of a circle");
	puts("input radius of a circle");
	scanf("%f", &radius);
	length = 2 * radius * 3.141592;
	area = radius * radius * 3.141592;
	printf("the radius is %5.3f\n", radius);
	printf("the length is %5.3f\n", length);
	printf("the area is %5.3f\n", area);
}

#include "vector.h"
#include <conio.h>

char make_color(char c1, unit c2)
{
	int color, t1, t2;
	t1 = c1 << 4;
	t2 = ((c2 >> 6) & 0x001f);
	t2 = ((t2 > 0) ? t2 - 1 : 0);
	color = t1 | t2;
	return (char)color;
}

void main()
{
	vector light(10240, 10240, 10240), normal(1024, 0, 0);
	unit light_angle;
	int force = 1;
	char color = 0, color2 = 15;

	clrscr();
	normalize(light);
	light_angle = normal * light;
	if ((light_angle > ZERO) || force) {
		light_angle = abs(light_angle);
		color = make_color(color2, light_angle);
	}
	cout << (int)color << endl;
}

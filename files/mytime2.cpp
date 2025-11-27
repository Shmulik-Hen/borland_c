#include <iostream.h>
#include <mytime.h>

void main()
{
	mytime a, b, c, d;
	int i;
	for (i = 0; i < 10; i++) {
		// cout<<"����� ��� ���:";
		cin >> a;
		// cout<<"����� ��� ���:";
		cin >> b;
		c = b - a;
		d = d + c;
		cout << c;
		cout << d;
	}
}

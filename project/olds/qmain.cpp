#include "queue.cpp"
#include <conio.h>
#include <iostream.h>

void main()
{
	queue<int> qi;
	int i, *pi;

	clrscr();
	for (i = 0; i < 10; i++) {
		pi = new int(i);
		cout << *pi << " ";
		qi.push(pi);
	}
	cout << endl;
	while (pi = qi.pop())
		cout << *pi << " ";
}

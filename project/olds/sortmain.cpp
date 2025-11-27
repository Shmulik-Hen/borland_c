#include "myclass.h"
#include <stdlib.h>
#include <iostream.h>
#include <conio.h>

void main()
{
	queue<myclass> q;
	myclass *p;
	randomize();
	clrscr();
	for (int i = 0; i < 100; i++) {
		int x = random(100);
		p = new myclass(x);
		q.push(p);
	}
	p = merge_sort(q);
	while (p) {
		p->print();
		p = p->next;
	}
}

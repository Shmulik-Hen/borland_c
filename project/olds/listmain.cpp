#include "list.cpp"
#include "types.def"
#include <iostream.h>
#include <conio.h>

/*
int int_comp(const void *i1, const void *i2)
{
 int *n1=(int *)i1,*n2=(int *)i2;

 return (*n1 - *n2);
}*/

int num;

int int_comp(const void *i)
{
	int *n = (int *)i;
	return (num == *n);
}

void main()
{
	list<int> li;
	int i, *p, x = 1;
	cmp fptr = int_comp;

	clrscr();
	for (i = 0; i < 10; i++) {
		p = new int(i);
		li.insert(p);
	}
	for (p = li.first(); p; p = li.next())
		cout << *p << endl;
	num = 5;
	p = li.find(fptr);
	if (p)
		cout << "found: " << *p << endl;
	else
		cout << x << ": not found" << endl;
}

#include "myclass1.h"
#include <iostream.h>
#include <string.h>

char *str;

myclass::myclass()
{
	name = NULL;
	num = 0;
}

myclass::~myclass()
{
	delete[] name;
}

myclass::myclass(int n, char *s)
{
	num = n;
	strcpy(name, s);
}

myclass *myclass::find(char *s)
{
	myclass *p;
	cmp fptr = my_comp;
	str = new char[strlen(s) + 1];
	strcpy(str, s);
	p = (myclass *)this->search(this, fptr);
	delete[] str;
	return p;
}

int my_comp(const void *node)
{
	myclass *p = (myclass *)node;
	return (!strcmp(str, p->name));
}

void myclass::print()
{
	cout << name << " " << num << endl;
}

void myclass::read()
{
	char s[80];
	cin >> s;
	cin >> num;
	name = new char[strlen(s) + 1];
	strcpy(name, s);
}

void printall(myclass *root)
{
	if (root) {
		root->print();
		printall((myclass *)root->son);
		printall((myclass *)root->next);
	}
}

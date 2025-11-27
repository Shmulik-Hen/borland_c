#include <mytree.h>

int condition(void *v1, void *v2)
{
	mydata *d1, *d2;

	d1 = (mydata *)v1;
	d2 = (mydata *)v2;

	return (d1->info - d2->info);
}

mydata::mydata() : btree()
{
	info = 0;
}

mydata::mydata(int num) : btree()
{
	info = num;
	cond = condition;
}

mydata::~mydata()
{
}

ostream &operator<<(ostream &out, mydata &t)
{
	int i;

	for (i = 0; i <= t.count; i++)
		out << t.info << t.dir << " ";
	return out;
}

istream &operator>>(istream &in, mydata &t)
{
	in >> t.info;
	return in;
}

void mydata::print()
{
	cout << *this;
}

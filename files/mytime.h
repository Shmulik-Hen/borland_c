#include <iostream.h>

class mytime
{
private:

	int hour;
	int min;

public:

	mytime();
	~mytime();
	mytime(int h, int m);
	mytime operator+(mytime &t);
	mytime operator-(mytime &t);
	mytime operator+=(mytime &t);
	friend istream &operator>>(istream &in, mytime &t);
	friend ostream &operator<<(ostream &out, mytime &t);
};

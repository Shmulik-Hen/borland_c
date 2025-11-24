#include <stdlib.h>
#include <mytime.h>


mytime::mytime()
{
 min=hour=0;
}

mytime::~mytime()
{
}

mytime::mytime(int h, int m)
{
 if (h<0) h+=24;
 if (m<0) {m+=60;h--;};
 min = (m % 60);
 hour = h + (m / 60);
}

mytime mytime::operator+(mytime &t)
{
 return mytime(hour+t.hour, min+t.min);
}

mytime mytime::operator-(mytime &t)
{
 return mytime(hour-t.hour, min-t.min);
}

mytime mytime::operator+=(mytime &t)
{
 *this=mytime(hour+=t.hour, min+=t.min);
 return *this;
}

istream& operator>>(istream &in, mytime &t)
{
 char str[5];
 int n;

 //cout<<"Enter time (hhmm):";
 in>>str;
 n=atoi(str);
 t=mytime(n/100, n%100);
 return in;
}

ostream& operator<<(ostream &out, mytime &t)
{
 out<<t.hour<<":"<<t.min<<"\n";
 return out;
}


/*SHEVER VER 2.0*/
/*INHERITANCE*/
#include<stdio.h>

class fraction {
    protected:
      int num;
      int den;
    public:
      fraction();
      fraction(int n, int d);
      fraction operator+(fraction &f);
      fraction operator-(fraction &f);
      void print();
         };
         
fraction::fraction()
{
 num=0;
 den=1;
}

fraction::fraction(int n, int d)
{
 num=n;
 den=d;
}

fraction fraction::operator+(fraction &f)
{ 
 return fraction( (num*f.den)+(den*f.num) , (den*f.den) );
}

fraction fraction::operator-(fraction &f)
{ 
 return fraction( (num*f.den)-(den*f.num) , (den*f.den) );
}


void fraction::print()
{
 printf("%2d\n",num);
 printf("---\n");
 printf("%2d\n\n",den);
 
}


class meorav:public fraction
      {
       private:
         int i;
       public:
         meorav();
         meorav(int n, int d, int m_i);
         meorav operator+(meorav &m);
         meorav operator-(meorav &m);              
         void print();
      };

meorav::meorav():fraction()
{
 i=0;
}

meorav::meorav(int n, int d, int m_i):fraction(n, d)
{
 i=m_i;
}

meorav meorav::operator+(meorav &m)
{
  fraction md1,md2;
  md1=fraction(i*den+num,den);
  md2=fraction(m.i*m.den+m.num,m.den);
  md1=md1+md2;
  return meorav( num/den, num%den, den);
}

meorav meorav::operator-(meorav &m)
{
 fraction md1,md2;
  md1=fraction(i*den+num, den);
  md2=fraction(m.i*m.den+m.num, m.den);
  md1=md1-md2;
  return meorav( num/den, num%den, den);
}

void meorav::print()
{
 fraction f;
 f=fraction(num,den);
 printf("%d",i);
 f.print();
}


void main()
{
 int n,d,i;
 meorav a,b,c;

 printf("enter first fraction ");
 scanf("%d %d %d",&n,&d,&i);
 a=meorav(n,d,i);
 printf("enter second fraction ");
 scanf("%d %d %d",&n,&d,&i);
 b=meorav(n,d,i);
 c=a+b;
 c.print();
 c=a-b;
 c.print();
}
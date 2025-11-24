#include <fstream.h>

class filearray:public fstream
	       {
		public:
		       int pos;
		       filearray(char *f_name);
		       ~filearray();
		       filearray& operator[] (int x);
		       filearray& operator= (char c);
		       operator char();
	       };


filearray::filearray(char *f_name):fstream(f_name, ios::in | ios::out | ios::binary)
{
}

filearray::~filearray()
{
}

filearray& filearray::operator[] (int x)
{
 pos=x;
 return(*this);
}

filearray& filearray::operator= (char c)
{
 seekg(pos,ios::beg);
 write(&c,1);
 return(*this);
}

filearray::operator char()
{
 char c;

 seekp(pos,ios::beg);
 read(&c,1);
 return c;
}

void main()
{
 filearray m("a:\\try.txt");
 char b;
 int i=0;

 for(b='A';b<='Z';b++)
     m[i++]=b;
 for(i=0;i<28;i++)
    {
     b=m[i];
     cout<<b;
    }
 cout<<endl;
}
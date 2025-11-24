#include "polygon.h"
#include "utils.h"
#include <string.h>
#include <stdlib.h>

list<polygon> poly_list;
char* str;

static far char poly_buff[64000];
unsigned poly_idx=0;
void* polygon::operator new(size_t s)
{
 void* p=&poly_buff[poly_idx];
 poly_idx+=s;
 return p;
}

vector polygon::find_fill()
{
 vector *p,temp;
 long num=0;

 temp-=temp;
 for(p=points.first();p;p=points.next())
   {
    temp+=*p;
    num++;
   }
 unit n(num<<10);
 temp.coord[X]/=n;
 temp.coord[Y]/=n;
 temp.coord[Z]/=n;
 return temp;
}

polygon* find_poly(list<polygon>& lst,char* s)
{
 polygon* p;
 cmp fptr=poly_comp;
 str=new char[strlen(s)+1];
 strcpy(str,s);
 p=lst.search(fptr);
 delete[] str;
 return p;
}

int poly_comp(const void* link)
{
 polygon *p=(polygon*)link;
 return(!strcmp(str,p->name));
}

void polygon::read(ifstream& f)
{
 LINE line;
 vector *vp;
 int finish=0;

 while(!f.eof() && !finish)
   {
    while( (!read_word(f,line)) && (!f.eof()) );
    if(f.eof())
      break;
    switch(line[1])
      {
       case 'n': read_word(f,line);
		 strcpy(name,line);
		 break;
       case 'c': read_word(f,line);
		 color=atoi(line);
		 break;
       case 'f': read_word(f,line);
		 force=atoi(line);
		 break;
       case 'o': normal.read(f);
		 break;
       case 'v': vp=new vector;
		 vp->read(f);
		 points.insert(vp);
		 break;
       default : finish=1;
		 f.seekg(-4,ios::cur);
		 break;
      }
   }
 fill=find_fill();
}

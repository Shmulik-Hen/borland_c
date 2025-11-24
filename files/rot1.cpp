#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#define MAXRECS 5

typedef int (*comp)(const void*, const void*);

typedef struct{
	       char name [20];
	       long id;
	       int age;
	      }student;

student std[MAXRECS];
comp funcptr[3];

int comp_by_name(const void *s1, const void *s2);
int comp_by_id(const void *s1, const void *s2);
int comp_by_age(const void *s1, const void *s2);
void fill();

void main()
{
 int i,j;

 funcptr[0]=comp_by_name;
 funcptr[1]=comp_by_id;
 funcptr[2]=comp_by_age;
 fill();
 clrscr();
 for(i=0;i<3;i++)
    {
     qsort( (void**)std, MAXRECS, sizeof(student), funcptr[i] );
     for(j=0;j<MAXRECS;j++)
	{
	 cout<<"name: "<<std[j].name;
	 cout<<" id: "<<std[j].id;
	 cout<<" age: "<<std[j].age<<endl;
	}
     cout<<endl;
    }
}

void fill()
{
 int i;
 for(i=0;i<MAXRECS;i++)
    {
     cin>>std[i].name;
     cin>>std[i].id;
     cin>>std[i].age;
    }
}

int comp_by_name(const void *s1, const void *s2)
{
 student *std1,*std2;

 std1=(student *)s1;
 std2=(student *)s2;
 return strcmp(std1->name,std2->name);
}

int comp_by_id(const void *s1, const void *s2)
{
 student *std1,*std2;

 std1=(student *)s1;
 std2=(student *)s2;
 if(std1->id == std2->id)
    return 0;
 else if(std1->id < std2->id)
	 return -1;
      else return 1;
}

int comp_by_age(const void *s1, const void *s2)
{
 student *std1,*std2;

 std1=(student *)s1;
 std2=(student *)s2;
 return (std1->age - std2->age);
}

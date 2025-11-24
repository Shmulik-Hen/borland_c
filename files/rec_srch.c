#include<stdio.h>
#include<conio.h>
#include<math.h>
#define SIZE 5

typedef struct
        {
	 char name[10];
	 char lastname [10];
	 long id_no;
	}record;

record person[SIZE],*ptr[SIZE];

int b_search(long num,int bottom,int top);
void sort_rec(void);

void main()
{
 int i,rec,num;

 clrscr();
 for(i=0;i<SIZE;i++)
    {
     ptr[i]=&person[i];
     scanf("%10s %10s %ld",ptr[i]->name,ptr[i]->lastname,&ptr[i]->id_no);
    }

 sort_rec();

 clrscr();
 for(i=0;i<SIZE;i++)
 printf("REC No.:%2d\tID No.:%ld\tNAME:%10s\t  LAST NAME:%10s\n",i+1,ptr[i]->id_no,ptr[i]->name,ptr[i]->lastname);

 printf("\n\n\n");
 printf("input ID No. you want to search for - ");
 scanf("%d",&num);

 rec=b_search(num,0,SIZE-1);
 if(rec==-1)
   printf("there is no such ID No. in the record\n");
 else
    printf("the ID No. you wanted is in record No. %d\n",rec+1);

 puts("press any key");
 getch();
}


void sort_rec(void)
{
int i,flag;
record *temp;

do{
flag=0;
for(i=0;i<SIZE;i++)
   {
    if(ptr[i]->id_no > ptr[i+1]->id_no)
      {
       temp=ptr[i];
       ptr[i]=ptr[(i+1)];
       ptr[(i+1)]=temp;
       flag=1;
      }
    }}
while(flag);
}


int b_search(long num,int bottom,int top)
{
int cell;


cell=floor((top+bottom)/2);
if((top-1==bottom)&&(ptr[cell]->id_no!=num))
   return -1;
if(ptr[cell]->id_no==num)
  return cell;
if(ptr[cell]->id_no>num)
  return(b_search(num,bottom,cell));
if(ptr[cell]->id_no<num)
  return(b_search(num,cell,top));
}
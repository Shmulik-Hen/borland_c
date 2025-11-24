#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#define ARRAY 20

void sort_array(void);
int b_search(int num,int bottom,int top);
int array[ARRAY];

void main()
{
int i,num,cell;

randomize();
clrscr();
for(i=0;i<ARRAY;i++)
    array[i]=random(100);
sort_array();
for(i=0;i<ARRAY;i++)
    printf("%d=>%d\n",i,array[i]);

printf("enter the number you want to find - ");
scanf("%d",&num);
cell=b_search(num,0,ARRAY-1);
if(cell==-1)
  printf("this number does not exist");
else
  printf("the number you wanted is in cell No.%d",cell);
}

void sort_array()
{
int i,flag,temp;

do{
flag=0;
for(i=0;i<ARRAY;i++)
   {
    if(array[i]>array[i+1])
      {
       temp=array[i];
       array[i]=array[i+1];
       array[i+1]=temp;
       flag=1;
      }
    }}
while(flag);
}


int b_search(int num,int bottom,int top)
{
int cell;

cell=floor((top+bottom)/2);
if((top-1==bottom)&&(array[cell]!=num))
   return -1;
if(array[cell]==num)
  return cell;
if(array[cell]>num)
  return(b_search(num,bottom,cell));
if(array[cell]<num)
  return(b_search(num,cell,top));

}
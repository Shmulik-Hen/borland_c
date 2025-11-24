#include<stdio.h>
#include<conio.h>


int array[100];
int array_size;

void fill_array(void);
void sort_array(int array_size);


main()
{
 int i;

 do{
 clrscr();
 printf("\n\n");
 puts("this program recieves an array of integer numbers and then sorts them,");
 puts("so the first number is the smallest, and the last number is the biggest.");
 printf("\n\n\n");
 puts("press any key to start filling the array.");
 while(getch()==''){}
 fill_array();
 clrscr();
 printf("the random array.\n\n");
 for(i=1;i<=array_size;i++)
    {
     printf("%6d",array[(i-1)]);
     if((i%10)==0)
       printf("\n");
    }
 sort_array(array_size);
 printf("\n\n\n");
 puts("press any key to see result.");
 while(getch()==''){}
 clrscr();
 printf("the sorted array.\n\n");
 for(i=1;i<=array_size;i++)
    {
    printf("%6d",array[(i-1)]);
    if((i%10)==0)
      printf("\n");
    }
 printf("\n\n\n");
 printf("there are %d elements in the array.\n",array_size);
 printf("\n\n\n");
 puts("press any key to start over.");
 puts("press Q to Quit.");}
 while(getch()!='q');
}



void fill_array(void)
{
 int n,i;
 n=0;

 clrscr();
 puts("enter numbers into array.");
 puts("enter '0' to stop.");
 puts("");
 for(i=0;i<100;i++)
  {
   printf("input element No.%2d=>",(i+1));
   scanf("%d",&array[i]);
   if(array[i]==0)
     break;
   n++;
  }
 array_size=n;
}


void sort_array(int array_size)
{
 int i,j,temp;

 for(j=0;j<array_size;j++)
    for(i=0;i<(array_size-j-1);i++)
       if(array[i]>array[(i+1)])
	 {
	  temp=array[i];
	  array[i]=array[(i+1)];
	  array[(i+1)]=temp;
	 }
}

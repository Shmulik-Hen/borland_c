#include<stdio.h>
#include<conio.h>

void main()
{
 int n,num,temp;

 num=temp=0;
 clrscr();
 puts("this program finds the biggest number from a series of numbers");
 puts("input the amount of numbers");
 scanf("%d",&n);
 while (n>=1)
       {
       puts("input a number");
       scanf("%d",&num);
       if (num>=temp)
	  temp=num;
       n--;
       }
 printf("the biggest number was %d\n",temp);
}





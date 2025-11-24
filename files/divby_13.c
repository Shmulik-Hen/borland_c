#include<stdio.h>
#include<conio.h>

void main()
{
 int i;
 clrscr();
 puts("this program prints all numbers from 1 to 300 that divides by 13");
 for (i=13;i<=300;i++)
	 {
	 if (i%13==0)
	 printf("%d\n",i);
	 }
}
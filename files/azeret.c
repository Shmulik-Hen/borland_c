#include<stdio.h>
#include<conio.h>

void main()
     {
     int i,product,number;
     clrscr();
     product=1;
     puts("this program calculates the product of a number");
     puts("input a number");
     scanf("%d",&number);
     for (i=1;i<=number;++i)
	 product*=i;
     printf("the product of %d! is %d",number,product);
     }
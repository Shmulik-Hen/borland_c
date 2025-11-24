
		     /*this program calculates the sum and*/
		     /*multiplication of two numbers	  */

#include<stdio.h>
#include<conio.h>

void main()
     {
     int a,b,c;
     clrscr();
     puts("this program calculates the sum and ");
     puts("multiplication of two numbers");
     puts("input a");
     scanf("%d",&a);
     puts("input b");
     scanf("%d",&b);
     c=a+b;
     printf("the sum of a and b is %d\n",c);
     c=a*b;
     printf("the multiplication of a and b is %d\n",c);
     }
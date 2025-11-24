#include<stdio.h>
#include<conio.h>

void main()
{
 int i;

 clrscr();
 puts("this program prints a table of numbers and their squares");
 puts("  n   |  n^2 ");
 puts("------|------");
 for (i=1;i<=20;++i)
     printf(" %3d  |  %3d\n",i,i*i);
}


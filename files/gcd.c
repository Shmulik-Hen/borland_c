#include<stdio.h>
#include<conio.h>

int gcd(int a,int b);

void main()
{
 int num1,num2,res;

 do{
 clrscr();
 puts("input the first number -");
 gotoxy(26,1);
 scanf("%d",&num1);
 puts("input the second number -");
 gotoxy(26,2);
 scanf("%d",&num2);
 res=gcd(num1,num2);
 printf("the G.C.D of %d and %d is %d",num1,num2,res);}
 while(getch()!='q');
}

int gcd(int a,int b)
{
 if((a%b)==0)
   return b;
 else
   return(gcd(b,(a%b)));
}
#include<stdio.h>
#include<conio.h>

#define ODD 1
#define EVEN 0

int ftype(int i,char chr);
int fodd(int num);

void main()
{
int i;
char chr;

clrscr();
puts("this program prints a triangle made of characters with a chosen base");
puts("type the character you want");
chr=getch();
putch(chr);
puts("");
puts("input the base width");
scanf("%d",&i);
if (fodd(i)==EVEN)
   i++;
if (i>50)
   i=49;
ftype(i,chr);
}

int fodd(int num)
{
int result;
if((num/2)==0)
  result=EVEN;
else
  result=ODD;
return result;
}

int ftype(int i,char chr)
{
int x,x1,x2,x3;
int j,y,z;
x=40;
x3=0;
y=1;
z=1;
clrscr();
while(z<=i)
  {
  x1=x-x3;
  x2=x+x3;
  for(j=x1;j<=x2;j++)
     {
     gotoxy(j,y);
     putch(chr);
     }
     y++;
     x3++;
     z+=2;
  }
return 0;
}

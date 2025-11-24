#include<stdio.h>
#include<conio.h>

typedef struct
	{
	 float real;
	 float img;
	}cmplx;

void add(cmplx *a,cmplx *b,cmplx *c);
void mult(cmplx *a,cmplx *b,cmplx *c);

void main()
{
 cmplx a,b,c,d;

 clrscr();
 puts("this program recieves two complex numbers and calculates");
 puts("their complex sum and complex multiplication.");
 printf("input the real part of first number: ");
 scanf("%f",&a.real);
 printf("input the imagenary part of first number: ");
 scanf("%f",&a.img);
 printf("input the real part of second number: ");
 scanf("%f",&b.real);
 printf("input the imagenary part of first number: ");
 scanf("%f",&b.img);
 add(&a,&b,&c);
 mult(&a,&b,&d);
 clrscr();
 printf("the first number:  a = %5.2f + %5.2fi\n",a.real,a.img);
 printf("the second number: b = %5.2f + %5.2fi\n",b.real,b.img);
 printf("\n\n");
 printf("the sum of a and b is:   %5.2f + %5.2fi\n",c.real,c.img);
 printf("the mult. of a and b is: %5.2f + %5.2fi\n",d.real,d.img);
 getch();
}


void add(cmplx *a,cmplx *b,cmplx *c)
{
 c->real=(a->real + b->real);
 c->img=(a->img + b->img);
}

void mult(cmplx *a,cmplx *b,cmplx *c)
{
 c->real=(a->real * b->real - a->img * b->img);
 c->img=(a->real * b->img + a->img * b->real);
}
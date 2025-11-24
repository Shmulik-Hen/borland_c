
#include<stdio.h>
#include <conio.h>

int array[10];

void fill_array(void);
int bignum(void);
float average(void);

void main()
{
	int i,biggest;
	float avrg;
	avrg = 0.0;

	clrscr();
	puts("this program recieves 10 numbers to an array, ");
	puts("and then finds the biggest number and the average");

	fill_array();
	biggest = bignum();
	avrg = average();

	clrscr();
	puts("the numbres in the array are ");
	for(i=0;i<10;i++)
		printf("%d, ",array[i]);
	puts("");
	printf("the biggest number is %d\nand the average is %5.3f",biggest,avrg);
}



void fill_array(void)
{
	int i;
	for(i=0;i<10;i++){
		printf("input element No. %d =>",(i+1));
		scanf("%d",&array[i]);
	}
}



int bignum(){
	int i,a,b;
	b=0;

	for(i=0;i<10;i++){
		a=array[i];
		if(a>b)
			b=a;
	}
	return b;
}


float average()
{
	int i,sum;
	float average;
	sum=0;                         			

	for(i=0;i<10;i++)
	    sum+=array[i];
	average = (sum / 10.0);
	return average;
}
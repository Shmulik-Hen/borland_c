#include <stdio.h>

void main()
{
 int sum_even, biggest_odd, total, num, n, i;
 float avrg;

 printf("please enter the No. of numbers: ");
 scanf("%d", &num);
 sum_even=biggest_odd=total=0;
 for(i=0; i<n; i++)
    {
     printf("please enter item No. %d: ", i+1);
     scanf("%d", &n);
     total += n;
     if((n%2)==0)
       sum_even += n;
     else if(n > biggest_odd)
	    biggest_odd=n;
    }
 if(num==0)
    avrg=0;
 else avrg=total / num;
 printf("the sum of all numbers is %d\n", sum_even);
 printf("the biggest odd number is %d\n", biggest_odd);
 printf("the average of all numbers is %f", avrg);
}



struct student{
	       char name[20];
	       long id_num;
	       int age;
	       int grade[10];
	      };




struct student std[30];



{
 int age, i, j, total;
 float avrg;

 age=100;
 total=0;
 for(i=0; i<30; i++)
    {
     if(age > std[i].age)
       {
	age=std[i].age;
	j=i;
       }
    }
 for(i=0; i<10; i++)
    total+=std[j].grades[i];
 avrg=total / 10;
 printf("the youngest student is %s and his average is %f\n",std[j].name,avrg);
}

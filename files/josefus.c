#include<stdio.h>
#include<conio.h>
#define NO  0
#define YES 1

typedef struct
		{
		 char name[10];
		 int dead;
		}person;

void main()
{
 person group[10];
 int i,j,count,step,deads;

 clrscr();
 for(i=0;i<10;i++)
	{
	 printf("type name of person No.%d:",i+1);
	 gets(group[i].name);
	 group[i].dead=NO;
	}
 printf("\n\nenter the step - ");
 scanf("%d",&step);

 clrscr();
 i=count=deads=0;
 while(deads<9)
      {
       if(group[i].dead!=YES)
          count++;
       if(count==step)
          {
           group[i].dead=YES;
           printf("%s is dead. may he rest in peace.\n",group[i].name);
           deads++;
           count=0;
          }
       i=(i+1)%10;
      }

for(i=0;i<10;i++)
   {
    if(group[i].dead!=YES)
       printf("\n%s is the survivor\n",group[i].name);
   }
printf("\n\npress any key");
getch();
}
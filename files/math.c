#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define FALSE 0
#define TRUE 1

typedef struct{
	char name[10];
	int id;
	float grade;
	}person;

person p1,p2;

void main()
{
 int x,y,z,answer;
 char key;
 FILE *fp;
 char filename[]="grades.dat";
 long pos=0;
 int count=0;
 int right=0;
 int loop=0;
 float tgrade=0.0;

 clrscr();
 printf("this program teaches the four basic functions of mathematics\n\n");
 printf("enter your name:");
 scanf("%9s",p1.name);
 printf("\nenter your id:");
 scanf("%d",&p1.id);

 if(!(fp=fopen(filename,"r")))
    fp=fopen(filename,"a");

 while(!feof(fp))
   {
    if(fread(&p2,sizeof(person),1,fp))
      {
       if(!strcmp(p1.name,p2.name))
	 {
	  pos=ftell(fp);
	  break;
	 }
      }
   }
 fclose(fp);

 while(count<=0 || count>20)
   {
    printf("\nhow many trys do you want? ");
    scanf("%d",&count);
    if(count<=0 || count>20)
      printf("out of range, please try again.\n");
   }


 do{
    randomize();
    x=random(100);
    y=random(100);
    if(y>x)		  /*if y > x  - swap values of x and y 	    */
      {
       z=x;
       x=y;
       y=z;
      }

    z=0;
    clrscr();
    puts("choose an exercize first");             /*choosing an exercize*/
    printf("\n");
    puts("for summation exercize       - press +");
    puts("for substuction exercize     - press -");
    puts("for multiplication exercize  - press *");
    puts("for division execize         - press /");
    printf("\n");

    switch(key=getch())
      {
       case '+':			        /*summation*/
	       printf(" %d + %d =",x,y);
	       scanf("%d",&z);
	       if(z==(answer=(x+y)))
		 {
		  puts("that's correct,very nice");
		  right++;
		 }
	       else
		 printf("that's wrong, the correct answer is  %d",answer);
	       break;
       case '-':                                /*substruction*/
	       printf(" %d - %d =",x,y);
	       scanf("%d",&z);
	       if(z==(answer=(x-y)))
		 {
		  puts("that's correct,very nice");
		  right++;
		 }
	       else
		 printf("that's wrong, the correct answer is  %d",answer);
	       break;
       case '*':                                /*multiplication*/
	       printf(" %d * %d =",x,y);
	       scanf("%d",&z);
	       if(z==(answer=(x*y)))
		 {
		  puts("that's correct,very nice");
		  right++;
		 }
	       else
		 printf("that's wrong, the correct answer is  %d",answer);
	       break;
       case '/':                                /*division*/
	       printf(" %d / %d =",x,y);
	       scanf("%d",&z);
	       if(z==(answer=(x/y)))
		 {
		  puts("that's correct,very nice");
		  right++;
		 }
	       else
		 printf("that's wrong, the correct answer is  %d",answer);
	       printf("and the remainder is - ");   /*the remainder*/
	       scanf("%d",&z);
	       if(z==(answer=(x%y)))
		 puts("that's correct,very nice");
	       else
		 printf("that's wrong, the correct answer is  %d",answer);
	       break;
       default:                                     /*wrong choice!*/
	       puts("illegal selection,see menu");
	       continue;
      }
    loop++;
    if(loop==count)
      break;
    printf("\n\n\n");				    /*quiting or staying*/
    puts("press Q to Quit");
    puts("press any other key to start over");
 }while(( (key=getch()) != 'q') );

 if(loop<count)
   {
    printf("you didn't finish the test\n");
    tgrade=right / loop;
   }
 else
   tgrade=(float)right / (float)count;

 tgrade=tgrade * 100;

 printf("\n\ndo you want to save the new grades? [Y/N]");
 key=getch();
 if(key=='y')
   {
    p1.grade=tgrade;
    if(pos==0)
       fp=fopen(filename,"a");
    else
      {
       fp=fopen(filename,"r+");
       fseek(fp,pos-sizeof(person),SEEK_SET);
      }
    fwrite(&p1,sizeof(person),1,fp);
    fclose(fp);
   }

 tgrade=0.0;
 count=0;
 fp=fopen(filename,"r");
 clrscr();
 while(!feof(fp))
   {
    fread(&p2,sizeof(person),1,fp);
    if(!feof(fp))
      {
       printf("name: %s\tid: %3d\t\tgrade: %3.2f\n",p2.name,p2.id,p2.grade);
       tgrade=tgrade+p2.grade;
       count++;
      }
   }
 tgrade=tgrade/count;
 printf("\nyour grade is %3.2f\n",p1.grade);
 printf("the class avarage is %3.2f\n",tgrade);
 if(p1.grade>=tgrade)
   printf("you are above the avarage");
 else
   printf("you are below the avarage");
}

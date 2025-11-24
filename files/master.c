#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

int cmptr[4];
int plyr[4];
int result[3];
int first;

void initial(void);
void computer(void);
void dsply(void);
void player(void);
void compare(void);
void prnt_rslt(void);

void main()

{
int i;

randomize();
initial();
do{
computer();
first=1;
for(i=1;i<=20;i++)
{
dsply();
player();
compare();
if(result[2]==1)
  {
  clrscr();
  gotoxy(30,10);
  puts("YOU WIN");
  prnt_rslt();
  break;
  }
}
if(result[2]==0)
{
clrscr();
gotoxy(30,10);
puts("NO LUCK THIS TIME ");
prnt_rslt();
}
gotoxy(53,23);
printf("press any key to play again");
gotoxy(53,24);
printf("or press Q to Quit         \n");}
while(getch()!='q');
}



void initial(void)

{
clrscr();
puts("                         MASTER - MIND");
puts("                        ---------------");
printf("\n\n");
puts("the object of this game is to guess four different numbers");
puts("that the computer has chosen.");
puts("");
puts("the numbers are from 0 to 9.");
puts("");
puts("each time, you will enter your choice of four numbers");
puts("and the computer will tell you how you did like this:");
puts("");
puts("HOTS  - for guessed numbers that were correct both in value and in place.");
puts("WARMS - for guessed numbers that were correct in value only.");
puts("");
puts("your task is to achieve four HOTS in 20 plays.");
printf("\n\n");
puts("                         GOOD - LUCK");
printf("\n\n");
puts("press any key.");
while(getch()==''){}
}


void computer(void)

{
int i,j;

for(i=0;i<4;i++)
   cmptr[i]=random(10);

for(i=0;i<4;i++)
   {
    for(j=0;j<4;j++)
       {
	if((i!=j)&&(cmptr[i]==cmptr[j]))
	  {
	   cmptr[j]=random(10);
	   j=0;
	   i=0;
	   break;
	  }
       }
   }
clrscr();
puts("");
puts("the computer has chosen it's numbers.");
printf("\n\n\n\n");
puts("press any key to start the game.");
while(getch()==''){}
}


void dsply(void)

{
int i,x;
static int n,y;

while(first)
  {
   y=5;
   n=1;

   clrscr();
   puts("                             MASTER - MIND");
   puts("                            ---------------");
   puts("                   YOUR GUESS           HOTS  WARMS");
   puts("                   ----------           ----  -----");
   gotoxy(55,23);
   puts("enter your choice here");
   first=0;
   return;
  }
x=1;
gotoxy(x,y);
printf("PLAY No.%d",n);
n++;
x=21;
for(i=0;i<4;i++)
   {
    gotoxy(x,y);
    printf("%d",plyr[i]);
    x+=2;
   }
x=43;
gotoxy(x,y);
printf("%d",result[0]);
x=49;
gotoxy(x,y);
printf("%d",result[1]);
y++;

/*
x=1;
z=23;
gotoxy(x,z);
puts("the computer's choice");
z++;
for(i=0;i<4;i++)
   {
    gotoxy(x,z);
    printf("%d",cmptr[i]);
    x+=2;
   }
*/
}


void player(void)

{
int i,x;
char chr;

x=65;
for(i=0;i<4;i++)
   {
    gotoxy(x,24);
    chr=getch();
    if((chr>='0')||(chr<='9'))
      {
       putch(chr);
       plyr[i]=(chr-48);
       x+=2;
      }
    else
      i--;
   }
}


void compare(void)

{
int i,j,hots,warms,win;

hots=warms=win=0;

for(i=0;i<4;i++)
   for(j=0;j<4;j++)
      {
      if(plyr[i]==cmptr[j])
	if(i==j)
	    hots++;
	else
	    warms++;
      }
if(hots==4)
  win=1;
result[0]=hots;
result[1]=warms;
result[2]=win;
}


void prnt_rslt(void)
{
int i,x;

gotoxy(30,11);
puts("the number was:");
x=33;
for(i=0;i<4;i++)
   {
    gotoxy(x,12);
    printf("%d",cmptr[i]);
    x+=2;
   }
}
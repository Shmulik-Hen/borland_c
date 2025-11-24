#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<mylib.h>


extern record *ptr[NUM];
extern FILE *fp;
extern char *filename;
extern int maxnum;


void initial(void)
{
 gotoxy(1,25);
 cprintf(" et    ead    ave    rint    ind    lear    uit");
 textcolor(CYAN);
 gotoxy(1,25); putch('G');
 gotoxy(7,25); putch('R');
 gotoxy(14,25); putch('S');
 gotoxy(21,25); putch('P');
 gotoxy(29,25); putch('F');
 gotoxy(36,25); putch('C');
 gotoxy(44,25); putch('Q');
 textcolor(WHITE);
 gotoxy(1,1);
}


int numcmp(char *s1,char *s2)
{
 double v1,v2;

 v1=atof(s1);
 v2=atof(s2);
 if(v1 < v2)
    return -1;
 else if(v1 > v2)
    return 1;
 else 
    return 0;
}


void swap(void *v[], int i, int j)
{
 void *temp;

 temp=v[i];
 v[i]=v[j];
 v[j]=temp;
}


void clear(void)
{
 int i;
 static int max=0;

 if (maxnum > max)
     max=maxnum;
 for(i=0;i<=max;i++)
     ptr[i]=NULL;
 maxnum=0;
}


void find_scr(void)
{
 clrscr();
 puts("Find what ?");
 gotoxy(1,25);
 cprintf(" ame     astname     ge     d");
 textcolor(CYAN);
 gotoxy(1,25); putch('N');
 gotoxy(9,25); putch('L');
 gotoxy(21,25); putch('A');
 gotoxy(28,25); putch('I');
 textcolor(WHITE);
 gotoxy(12,1);
}

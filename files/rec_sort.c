#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define NUM 1000

typedef struct
        {
	 char name[10];
	 char lastname[10];
	 char age[10];
	 char id[10];
	}record;

record *ptr[NUM];
FILE *fp;
char *filename;
int maxnum=0;

void rec_qsort(void *ptr[] ,int left ,int right
	       ,int (*comp)(void*,void*));
int numcmp(char *s1,char *s2);
int sort_cmp1(record *p1,record *p2);
int sort_cmp2(record *p1,record *p2);
int sort_cmp3(record *p1,record *p2);
int sort_cmp4(record *p1,record *p2);
int srch_cmp1(record *p,char *str);
int srch_cmp2(record *p,char *str);
int srch_cmp3(record *p,char *str);
int srch_cmp4(record *p,char *str);
void initial(void);
void prnt_rcd(void);
void save_rcd(void);
void dspl_rcd(void);
void get_dtls(void);
void rd_file(void);
void clear(void);


void main()
{
 char key;

 clrscr();
 do{
    initial();
    switch(key=getch())
	  {
	   case 'a':rec_qsort((void **)ptr , 0 , maxnum
			  ,(int(*)(void*, void*))(sort_cmp3));
		    break;
	   case 'i':rec_qsort((void **) ptr , 0 , maxnum
			  ,(int(*)(void*, void*))(sort_cmp4));
		    break;
	   case 'l':rec_qsort((void **) ptr , 0 , maxnum
			  ,(int(*)(void*, void*))(sort_cmp2));
		    break;
	   case 'n':rec_qsort((void **) ptr , 0 , maxnum
			  ,(int(*)(void*, void*))(sort_cmp1));
		    break;
	   case 'g':get_dtls();
		    break;
	   case 'p':prnt_rcd();
		    break;
	   case 'r':rd_file();
		    break;
	   case 's':save_rcd();
		    break;
	   case 'c':clear();
	   defualt:break;
	  }
    dspl_rcd();
   }
 while(key != 'q');
}


void initial(void)
{
 gotoxy(1,25);
 cprintf(" et    ead    ave    rint    ge    d    ame    astname    lear    uit");
 textcolor(CYAN);
 gotoxy(1,25); putch('G');
 gotoxy(7,25); putch('R');
 gotoxy(14,25); putch('S');
 gotoxy(21,25); putch('P');
 gotoxy(29,25); putch('A');
 gotoxy(35,25); putch('I');
 gotoxy(40,25); putch('N');
 gotoxy(47,25); putch('L');
 gotoxy(58,25); putch('C');
 gotoxy(66,25); putch('Q');
 textcolor(WHITE);
 gotoxy(1,1);
}


void rec_qsort(void *v[],int left,int right
	       ,int(*comp)(void *,void *))
{ 
 int i,last;
 void swap(void *v[],int,int);

 if(left >= right)
    return;
 swap(v,left,(left+right)/2);
 last=left;
 for (i=left+1; i<=right; i++)
      if ((*comp)(v[i] ,v[left] ) < 0)
	  swap(v, ++last, i);
 swap(v, left, last);
 rec_qsort(v, left, last-1, comp);
 rec_qsort(v, last+1, right, comp);
}


int sort_cmp1(record *p1,record *p2)
{
 return(strcmp(p1->name,p2->name));
}


int sort_cmp2(record *p1,record *p2)
{
 return(strcmp(p1->lastname,p2->lastname));
}


int sort_cmp3(record *p1,record *p2)
{
 return(numcmp(p1->age,p2->age));
}


int sort_cmp4(record *p1,record *p2)
{
 return(numcmp(p1->id,p2->id));
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


void get_dtls(void)
{
 int i=0;
 char *str;

 clear();
 clrscr();
 while(1)
      {
       ptr[i]=(record*)malloc(sizeof(record));
       gets(str);
       if(sscanf(str,"%s %s %s %s",ptr[i]->name
				  ,ptr[i]->lastname
				  ,ptr[i]->age
				  ,ptr[i]->id) == -1)
	 {
	  ptr[i]=NULL;
	  i--;
	  break;
	 }
       i++;
      }
 maxnum=i;
}


void dspl_rcd(void)
{
 int i;

 clrscr();
 for(i=0;i<=maxnum;i++)
     printf("%s %s %s %s\n",ptr[i]->name
			   ,ptr[i]->lastname
			   ,ptr[i]->age
			   ,ptr[i]->id);
}


void save_rcd(void)
{
 int i;

 clrscr();
 puts("input file name:");
 gotoxy(17,1);
 gets(filename);
 fp=fopen(filename,"w");
 for(i=0;i<=maxnum;i++)
     fprintf(fp,"%s %s %s %s\n",ptr[i]->name
			       ,ptr[i]->lastname
			       ,ptr[i]->age
			       ,ptr[i]->id);
 fclose(fp);
}


void rd_file(void)
{
 int i=0;

 clrscr();
 puts("input file name:");
 gotoxy(17,1);
 gets(filename);
 fp=fopen(filename,"r");
 clear();
 while(1)
      {
       ptr[i]=(record*)malloc(sizeof(record));
       if(fscanf(fp,"%s %s %s %s",ptr[i]->name
				 ,ptr[i]->lastname
				 ,ptr[i]->age
				 ,ptr[i]->id) == EOF)
	 {
	  ptr[i]=NULL;
	  i--;
	  break;
	 }
       i++; 
      }
 maxnum=i;
 fclose(fp);
}


void prnt_rcd(void)
{
 int i;

 for(i=0;i<=maxnum;i++)
     fprintf(stdprn,"%s %s %s %s\n",ptr[i]->name
				   ,ptr[i]->lastname
				   ,ptr[i]->age
				   ,ptr[i]->id);
}


void clear(void)
{
 int i;
 static int max;

 if (maxnum > max)
     max=maxnum;
 for(i=0;i<=max;i++)
     ptr[i]=NULL;
 maxnum=0;
}



int rec_bsrch(void *v[],int bottom,int top,char *item
	     ,int (*comp)(void*,void*))
{
int cell;

cell=floor((top+bottom)/2);
if( (top-1 == bottom ) && ( (*comp)(v[cell],item) != 0 ) )
   return -1;
if( (*comp)(v[cell],item) == 0 )
  return cell;
if( (*comp)(v[cell],item) == 1 )
   rec_bsrch(v,bottom,cell,item,comp);
if( (*comp)(v[cell],item) == -1 )
   rec_bsrch(v,cell,top,item,comp);
}


int srch_cmp1( record *p , char *str)
{
 return(strcmp(p->name,str));
}

int srch_cmp2( record *p , char *str)
{
 return(strcmp(p->lastname,str));
}

int srch_cmp3( record *p , char *str)
{
 return(numcmp(p->age,str));
}

int srch_cmp4( record *p , char *str)
{
 return(strcmp(p->id,str));
}
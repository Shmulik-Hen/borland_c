#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>

void main(int argc, char *argv[])
{

FILE *fp;
char filename[20],c;
int chrs,words,lines;

chrs=words=0;
lines=1;
strcpy(filename,argv[1]);
fp=fopen(filename,"r");

while((c=fgetc(fp))!=EOF)
	  {
	   if( (isalnum(c)) || (ispunct(c)) )
		  chrs++;
	   if( (isspace(c) || (c==EOF)) && chrs>1 )
		  words++;
	   if(c=='\n')
		  lines++;
	   if(chrs==0)
		 words=lines=0;
	  }
fclose(fp);

clrscr();
printf("the file %s has:\n %d characters\n %d words\n %d lines\n",filename
		,chrs,words,lines);
puts("press any key");
getch();
}
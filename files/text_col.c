#include<stdio.h>
#include<conio.h>
#include<string.h>

void main()
{
int color;
char name[15];
clrscr();
for(color=0;color<=15;color++)
   {
    switch(color)
	  {
	   case 0: strcpy(name,"black");
		   break;
	   case 1: strcpy(name,"blue");
		   break;
	   case 2: strcpy(name,"green");
		   break;
	   case 3: strcpy(name,"cyan");
		   break;
	   case 4: strcpy(name,"red");
		   break;
	   case 5: strcpy(name,"magenta");
		   break;
	   case 6: strcpy(name,"brown");
		   break;
	   case 7: strcpy(name,"light grey");
		   break;
	   case 8: strcpy(name,"dark grey");
		   break;
	   case 9: strcpy(name,"light blue");
		   break;
	   case 10: strcpy(name,"light green");
		   break;
	   case 11: strcpy(name,"light cyan");
		   break;
	   case 12: strcpy(name,"light red");
		   break;
	   case 13: strcpy(name,"light magenta");
		   break;
	   case 14: strcpy(name,"yellow");
		   break;
	   case 15: strcpy(name,"white");
		   break;
	  }
   textcolor(color);
   cprintf("this text is in %s\n\r",name);
   }
getch();
}
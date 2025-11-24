#include "tar_win.h"
#include <conio.h>

void main()
{
 char ch;
 int count=0;

 textcolor(BLACK);
 textbackground(BLACK);
 clrscr();

 win a(25,10,RED);
 win b(25,10,GREEN);
 win c(35,12,BLUE);
 a.show(1,1);
 b.show(51,1);
 c.show(26,12);
 a.select();
 a.type_in();
 while( (ch=getch()) != 27)
   {
    if (ch=='\t')
      count=(count+1)%3;
    switch(count)
	  {
       case 0: c.unselect();
	       a.select();
	       a.type_in();
	       break;
       case 1: a.unselect();
	       b.select();
	       b.type_in();
	       break;
       case 2: b.unselect();
	       c.select();
	       c.type_in();
	       break;
      };
   }
 a.hide();
 b.hide();
 c.hide();
}
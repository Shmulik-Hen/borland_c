#include<win.h>
#include <stdio.h>
#define DOWN 0
#define UP 1

void main()
{
 win a(40,10,WHITE,BLUE,1);
 char *str1=":";
 char *str2=":";
 char *str3="";
 char *str4="";
 char s[5];
 char c;
 int i,dir;

 clrscr();
 a.show(20,7);
 a.put_str(str1,28,2,WHITE);
 a.put_str(str2,28,4,WHITE);
 a.put_str(str3,25,7,WHITE);
 a.put_str(str4,11,7,WHITE);
 a.save();
 a.chg_attr(21,2,7,BLACK,LGREY);
 i=1;

 while( (c=getch() ) != 27)
      {
       if(c==0)
	 {
	  c=getch();
	  switch(c)
	   {
	    case 80:i++;
		    if(i>4)
		    i=1;
		    dir=DOWN;
		    break;
	    case 72:i--;
		    if(i<1)
		    i=4;
		    dir=UP;
		    break;
	    default:break;
	   }
	  switch(i)
	   {
	    case 1:switch(dir)
		    {
		     case DOWN:a.chg_attr(10,7,6,WHITE,BLUE);
			       break;
		     case UP:a.chg_attr(21,4,7,WHITE,BLUE);
			     break;
		    }
		   a.chg_attr(21,2,7,BLACK,LGREY);
		   break;
	    case 2:switch(dir)
		    {
		     case DOWN:a.chg_attr(21,2,7,WHITE,BLUE);
			       break;
		     case UP:a.chg_attr(24,7,6,WHITE,BLUE);
			     break;
		    }
		   a.chg_attr(21,4,7,BLACK,LGREY);
		   break;
	    case 3:switch(dir)
		    {
		     case DOWN:a.chg_attr(21,4,7,WHITE,BLUE);
			       break;
		     case UP:a.chg_attr(10,7,6,WHITE,BLUE);
			     break;
		    }
		   a.chg_attr(24,7,6,BLACK,LGREY);
		   break;
	    case 4:switch(dir)
		    {
		     case DOWN:a.chg_attr(24,7,6,WHITE,BLUE);
			       break;
		     case UP:a.chg_attr(21,2,7,WHITE,BLUE);
			     break;
		    }
		   a.chg_attr(10,7,6,BLACK,LGREY);
		   break;
	   }

	 }
       else
	 {
	  ungetch(c);
	  switch(i)
	   {
	    case 1:a.get_str(s,22,2,4,YELLOW);
		   break;
	    case 2:a.get_str(s,22,4,4,YELLOW);
		   break;
	    case 3:break;
	    case 4:break;
	   }
	 }
      }
 a.hide();
}

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

void initial( void );
void total( void );
void prj( void );
void third( void );
float convert( int num );

float start_time,end_time,total_time,proj_time,add_time;
char *str,c;

void main()
{
 initial();
}
 
void initial( void )
{
 clrscr();
 gotoxy(67,1);puts(".1");
 gotoxy(65,2);puts(".2");
 gotoxy(66,3);puts(".3");
 gotoxy(67,6);puts("'");
 gotoxy(67,7);puts("Q");
 gotoxy(79,8);

 switch ( getch() )
	{
	 case '1': total();       
	 case '2': prj();
	 case '3': third();
	 case 'q': clrscr();
		   exit(0);
	 case 'Q': clrscr();
		   exit(0);
	 default:  initial();
	}			  
}


void total( void )
{
 clrscr();
 gotoxy(69,1); puts("\"");

 gotoxy(59,3); puts(":(hhmm)"); 
 gotoxy(54,3);
 start_time=convert(atoi(gets(str)));

 gotoxy(59,4); puts(":(hhmm)"); 
 gotoxy(54,4);
 end_time=convert(atoi(gets(str)));

 total_time=end_time-start_time;
 if ( total_time<0 )
      total_time=total_time+24.00;

 gotoxy(59,7); puts(":()\""); 
 gotoxy(56,7); printf("%2.2f",total_time);

 if ( total_time<9.25 )
    {
     proj_time=total_time-0.5;
     if( start_time>=22.00 )
	 add_time=7.43-proj_time;
     else
	 add_time=8.75-proj_time;

     gotoxy(57,8); puts(":()"); 
     gotoxy(51,8); printf("%2.2f",proj_time);

     if ( add_time>0.0 )
	{
	 gotoxy(61,9); puts(":()"); 
	 gotoxy(55,9); printf("%2.2f",add_time);
	}
    }

 gotoxy(61,12); puts("");
 gotoxy(67,13); puts("Q"); 
 gotoxy(79,14);

 if ( (c=getch()) == 'q' || c == 'Q')
     initial();
 else
     total();
}


void prj( void )
{
 clrscr();
 gotoxy(67,1); puts("");
 gotoxy(60,3); puts(":(h.mm)"); 
 gotoxy(55,3);

 total_time=atof(gets(str));
 if ( total_time<0.5 )
    {
     total_time=0.0;
     initial();
    }

 proj_time=total_time-0.5;
 add_time=8.75-proj_time;

 gotoxy(57,7); puts(":()"); 
 gotoxy(51,7); printf("%2.2f",proj_time);

 if ( add_time>0.0 )
    {
     gotoxy(61,8); puts(":()"); 
     gotoxy(55,8); printf("%2.2f",add_time);
    }

 gotoxy(61,12); puts("");
 gotoxy(67,13); puts("Q"); 
 gotoxy(79,14);

 if( (c=getch()) == 'q' || c == 'Q')
    initial();
 else
    prj();
}


void third( void )
{
 clrscr();
 gotoxy(68,1); puts("");
 gotoxy(60,3); puts(":(h.mm)"); 
 gotoxy(55,3);

 total_time=atof(gets(str));
 if ( total_time<0.5 )
    {
     total_time=0.0;
     initial();
    }

 proj_time=total_time-0.5;
 add_time=7.43-proj_time;

 gotoxy(57,7); puts(":()"); 
 gotoxy(51,7); printf("%2.2f",proj_time);

 if ( add_time>0.0 )
    {
     gotoxy(61,8); puts(":()"); 
     gotoxy(55,8); printf("%2.2f",add_time);
    }

 gotoxy(61,12); puts("");
 gotoxy(67,13); puts("Q"); 
 gotoxy(79,14);

 if( (c=getch()) == 'q' || c == 'Q')
    initial();
 else
     third();
}


float convert( int num )
{
 float a;

 a=num%100;
 return ((num-a)/100+(a/60));
}

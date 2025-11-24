#include <graphics.h>
#include <iostream.h>
#include <stdlib.h>
#include <conio.h>
#include <wind.h>
#include <menu.h>
#define ROWS 6

int main()
{
 int gdriver = DETECT, gmode, errorcode;
 char *topics[ROWS]={"LINE",
		     "RECTANGLE",
		     "CIRCLE",
		     "ELIPSE",
		     "POLIGON",
		     "QUIT"};

 initgraph(&gdriver, &gmode, "");
 errorcode = graphresult();
 if(errorcode != grOk)
   {
    cout<<"Graphics error:" << grapherrormsg(errorcode)<<endl;
    cout<<"Press any key to halt:";
    getch();
    exit(1);
   }
 settextstyle(SMALL_FONT,HORIZ_DIR,0);
 setusercharsize(3,2,2,1);

 my_menu m(0,0,ROWS,topics);
 cleardevice();
 m.show(100,100);
 getch();
 m.hide();
 closegraph();
 return 0;
}

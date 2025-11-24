#include <iostream.h>
#include <graphics.h>
#include <process.h>
#include <alloc.h>
#include <mouse.h>
#include <mymenu.h>
#include <utils.h>
#include <drawing.h>

extern POINT p;
extern int close_flag;
void *fg,*bg,*bar1,*bar2;                              //places to hold images

void prepare_menu()
{
 unsigned int size,bar_size;
 char *str[]={"NEW","OPEN","CLOSE","SAVE","EXIT"};         //items in the manu
 int i,x,y;

 size=imagesize(1,17,57,117);                                   //size of menu
 bar_size=imagesize(1,39,57,57);                       //size of highlight bar
 if( (fg=(void*)malloc(size)) == NULL)                              //for menu
   {
    closegraph();
    cout<<"not enough memory in prepare_menu()";
    exit(1);
   }
 if( (bg=(void*)malloc(size))  == NULL)                       //for background
   {
    closegraph();
    cout<<"not enough memory in prepare_menu()";
    exit(1);
   }
 if( (bar1=(void*)malloc(bar_size))  == NULL)              //for highlight bar
   {
    closegraph();
    cout<<"not enough memory in prepare_menu()";
    exit(1);
   }
 if( (bar2=(void*)malloc(bar_size))  == NULL)           //for highlighted item
   {
    closegraph();
    cout<<"not enough memory in prepare_menu()";
    exit(1);
   }

 settextstyle(SMALL_FONT,HORIZ_DIR,0);
 setusercharsize(3,2,2,1);
 setcolor(WHITE);
 rectangle(1,17,57,117);                                     //draw menu frame
 x=4;
 y=19;
 for(i=0;i<5;i++)                                    //write items in a column
    {
     outtextxy(x,y,str[i]);
     y+=textheight("H");
    }
 getimage(1,17,57,117,fg);                        //save current image of menu
 setfillstyle(1,WHITE);
 bar(1,39,57,57);                                         //draw highlight bar
 getimage(1,39,57,57,bar1);                                  //save it's image
}

void draw_menu()
{
 HideMouse();
 getimage(1,17,57,117,bg);                                   //save background
 putimage(1,17,fg,COPY_PUT);                                    //display menu
 ShowMouse();
 while(!MousePressed());
 GetMouseLocation(&p);                                       //get chosen item
 if(between(p,1,17,57,39))                                            // "NEW"
   {
    HideMouse();
    getimage(1,21,57,39,bar2);                               //save background
    putimage(1,21,bar1,XOR_PUT);                         //highlight selection
    while(MousePressed());                   //keep highlightind until release
    putimage(1,17,bg,COPY_PUT);                       //restore previous image
    ShowMouse();
    do_close();                                                        //do it
    do_drawing();
   }
 else if(between(p,1,39,57,57))                                      // "OPEN"
   {
    HideMouse();
    getimage(1,39,57,57,bar2);
    putimage(1,39,bar1,XOR_PUT);
    while(MousePressed());
    putimage(1,17,bg,COPY_PUT);
    ShowMouse();
    do_close();
    do_open();
   }
 else if(between(p,1,57,57,75))                                     // "CLOSE"
   {
    HideMouse();
    getimage(1,57,57,75,bar2);
    putimage(1,57,bar1,XOR_PUT);
    while(MousePressed());
    putimage(1,17,bg,COPY_PUT);
    ShowMouse();
    close_flag=1;
    do_close();
   }
 else if(between(p,1,75,57,93))                                      // "SAVE"
   {
    HideMouse();
    getimage(1,75,57,93,bar2);
    putimage(1,75,bar1,XOR_PUT);
    while(MousePressed());
    putimage(1,17,bg,COPY_PUT);
    ShowMouse();
    do_save();
   }
 else if(between(p,1,93,57,111))                                     // "EXIT"
   {
    HideMouse();
    getimage(1,93,57,111,bar2);
    putimage(1,93,bar1,XOR_PUT);
    while(MousePressed());
    putimage(1,17,bg,COPY_PUT);
    ShowMouse();
    do_exit();
   }
 else putimage(1,17,bg,COPY_PUT);                                  // "ESCAPE"
}

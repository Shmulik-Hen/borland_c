#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <iostream.h>
#include <dos.h>
#include <mymenu.h>
#include <mouse.h>
#include <utils.h>
#include <tools.h>
#include <drawing.h>
#include <dbox.h>
#define ESC 27

extern BODY b;
extern POINT p;
extern FILE *fp;
extern char filename[];
extern int close_flag,save_flag,draw_flag,offsetx,offsety;
extern double angle,zoom;

void draw_screen()
{
 int i;

 cleardevice();
 setcolor(WHITE);
 rectangle(0,0,getmaxx(),getmaxy());                                   //frame
 line(0,17,639,17);                                                  //top bar
 setfillstyle(1,RED);
 floodfill(42,2,WHITE);
 line(40,0,40,17);                                                  //menu bar
 setfillstyle(1,BLUE);
 settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
 outtextxy(5,5,"MENU");
 floodfill(2,2,WHITE);
 line(540,17,540,479);                                                 //tools
 line(590,17,590,377);
 for(i=1;i<5;i++)
    line(540,17+i*90,639,17+i*90);
 setfillstyle(1,WHITE);
 rectangle(545,40,560,55);                                           //zoom in
 bar(555,50,585,80);
 rectangle(595,40,625,70);                                          //zoom out
 bar(615,65,630,80);
 bar(564,215,568,265);                                               //move up
 line(556,220,576,220);
 line(556,220,566,207);
 line(576,220,566,207);
 floodfill(566,209,WHITE);
 bar(614,215,618,265);                                             //move down
 line(606,260,626,260);
 line(606,260,616,273);
 line(626,260,616,273);
 floodfill(616,271,WHITE);
 bar(550,330,580,334);                                             //move left
 line(555,322,555,342);
 line(555,322,545,332);
 line(555,342,545,332);
 floodfill(547,332,WHITE);
 bar(600,330,630,334);                                            //move right
 line(625,322,625,342);
 line(625,322,635,332);
 line(625,342,635,332);
 floodfill(633,332,WHITE);
 arc(565,152,0,270,10);                                           //rotate ccw
 arc(565,152,0,270,14);
 line(575,152,579,152);
 line(565,162,565,157);
 line(565,166,565,171);
 line(565,157,570,164);
 line(565,171,570,164);
 floodfill(568,164,WHITE);
 arc(615,152,270,180,10);                                          //rotate cw
 arc(615,152,270,180,14);
 line(601,152,605,152);
 line(615,162,615,157);
 line(615,166,615,171);
 line(615,157,610,164);
 line(615,171,610,164);
 floodfill(617,164,WHITE);
 line(0,430,540,430);                                              //color bar
 for(i=0;i<15;i++)
    {
     setfillstyle(1,i+1);
     bar3d(i*36,430,(i+1)*36,479,0,0);
    }
 setfillstyle(1,BLACK);                                    //chosen color icon
 bar3d(550,385,629,470,0,0);
}

void keyboard_things()                    //things to do when keyboard is used
{
 char c;

 if((c=getch())==ESC)                            //trap the escape key to exit
   {
    closegraph();
    exit(0);
   }
}

void mouse_things()                          //things to do when mouse is used
{
 char str[8];

 if(MouseDownRight())       //things to do when right mouse button was pressed
   {
    //nothing at the moment
   }
 if(MouseDownLeft())         //things to do when left mouse button was pressed
   {
    while(MouseDownLeft());
    GetMouseLocation(&p);
    //LocToStr(str,p.x,p.y);                      this was very helpfull when
    //HideMouse();                                deciding on item's positions
    //outtextxy(p.x,p.y,str);                     but not used in the program
    //ShowMouse();                                any more
    identify_location(p);                           //perform the current task
   }
}

void standart_things() //things to do when no action is taken
{
 //nothing at the moment
}

void LocToStr(char *s,int x, int y)   //transforms an x,y position to a string
{                                                         //not in use anymore
 char str1[3],str2[3];

 strcpy(s,"");
 itoa(x,str1,10);
 itoa(y,str2,10);
 strcat(s,str1);
 strcat(s,",");
 strcat(s,str2);
 strcat(s,"\0");
}

void identify_location(POINT p)                  //switch to the chosen action
{
 if(between(p,0,0,40,17))                                            //top bar
   draw_menu();
 else if(between(p,0,430,540,479))                                 //color bar
   {
    choose_color();
    put_image();
   }
 else if(between(p,540,17,639,378))                                //tools bar
   {
    choose_tool();
    put_image();
   }
 else beep();                                                //any other place
}

void beep()                                                  //sound the alarm
{
 sound(440);
 delay(100);
 nosound();
}

void do_open()                              //open a file and build an element
{
 VECTOR *temp,*temp2;
 int i;
 angle=0.0;
 zoom=1.0;                                                    //default values
 offsetx=270;
 offsety=210;

 if((fp=fopen(filename,"rb"))==NULL)
   {
    message("file not found");
    return;
   }
 fread(&b,sizeof(BODY),1,fp);      //read element's color and number of points
 b.first_vector=NULL;
 for(i=0;i<b.num_points;i++)                  //create a linked list of points
   {
    if((temp=(VECTOR*)malloc(sizeof(VECTOR)))==NULL)
      {
       closegraph();
       cout<<"not enough memory in do_open()";
       exit(1);
      }
    fread(temp,sizeof(VECTOR),1,fp);
    if(b.first_vector==NULL)                                      //first time
       b.first_vector=temp2=temp;
    else                                                         //concatenate
      {
       temp2->next_vector=temp;
       temp2=temp2->next_vector;
      }
   }
 temp->next_vector=NULL;
 setcolor(b.color);
 fclose(fp);
 draw_flag=1;
 save_flag=1;
 put_image();
}

void do_close()                                             //close an element
{
 VECTOR *temp1,*temp2;

 if(!save_flag)                              //if current element wasn't saved
    draw_dbox();
 if(close_flag)                                               //if ok to close
   {
    HideMouse();
    setviewport(1,18,539,429,1);                      //clear the drawing area
    clearviewport();
    setviewport(0,0,getmaxx(),getmaxy(),0);
    ShowMouse();
    if(draw_flag)                            //if an element was already drawn
      {
       draw_flag=0;
       temp1=b.first_vector;
       while(temp1 != NULL)                //release all it's allocated memory
	 {
	  temp2=temp1;
	  free(temp2);
	  temp1=temp1->next_vector;
	 }
      }
   }
}

void do_save()                                         //save an image to file
{
 VECTOR *temp;
 int i;

 if(save_flag)                                  //if allready saved do nothing
   return;
 if((fp=fopen(filename,"wb"))==NULL)
   {
    message("could not create file");
    return;
   }
 fwrite(&b,sizeof(BODY),1,fp);              //write color and number of points
 temp=b.first_vector;
 while(temp != NULL)                          //for every point in the element
    {
     fwrite(temp,sizeof(VECTOR),1,fp);               //write point coordinates
     temp=temp->next_vector;
    }
 fclose(fp);
 save_flag=1;
}

void do_exit()                                                      //shutdown
{
 do_close();
 HideMouse();
 closegraph();
 exit(0);
}

void do_average()         //find element center and normalize every coordinate
{
 double sum_x=0,sum_y=0;
 VECTOR *temp,avg;

 temp=b.first_vector;
 while(temp != NULL)                            //total all coordinates values
   {
    sum_x+=temp->x;
    sum_y+=temp->y;
    temp=temp->next_vector;
   }
 avg.x=(double)sum_x/b.num_points;                       //calculate average x
 avg.y=(double)sum_y/b.num_points;                       //calculate average y
 temp=b.first_vector;
 while(temp != NULL)                //go through all points and normalize them
   {
    temp->x-=avg.x;
    temp->y-=avg.y;
    temp=temp->next_vector;
   }
 offsetx=avg.x;                                //set initial center of display
 offsety=avg.y;
}

void message(char *s)                     //output a message string to top bar
{
 int oldcolor=getcolor();                     //preserve current drawing color

 setviewport(41,1,638,16,1);                           //focus on top bar only
 setcolor(WHITE);
 settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
 outtextxy(5,5,s);
 beep();
 while(!kbhit() && !MousePressed());                       //wait for response
 clearviewport();
 setfillstyle(1,RED);
 floodfill(1,1,WHITE);
 setviewport(0,0,getmaxx(),getmaxy(),0);                    //return to normal
 setcolor(oldcolor);                                       //restore old color
}

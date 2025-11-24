#include <iostream.h>
#include <graphics.h>
#include <math.h>
#include <process.h>
#include <alloc.h>
#include <drawing.h>
#include <mouse.h>
#include <utils.h>

extern POINT p;
extern BODY b;
extern double zoom,angle;
extern int save_flag,color_flag,draw_flag,offsetx,offsety;

void do_drawing()                                         //draw a new element
{
 VECTOR *temp1,*temp2;
 int first=1;

 if(!color_flag)                           //must choose color before anything
   {
    message("choose color first");
    return;
   }
 temp1=temp2=NULL;
 message("left button draws, right button quits");
 HideMouse();
 setviewport(1,18,539,429,1);                     //focus on drawing area only
 clearviewport();
 ShowMouse();
 while(!MouseDownRight())                                //while still drawing
   {
    if(MouseDownLeft())
      {
       if(first)                                      //in case of first point
	 {
	  while(MouseDownLeft());
	  GetMouseLocation(&p);
	  first=0;
	  draw_flag=1;                                  //initialize variables
	  save_flag=0;
	  b.num_points=1;
	  angle=0.0;
	  zoom=1.0;
	  p.y-=17;                                      //??? - don't know why
	  if(between(p,1,18,539,429))                             //ok to draw
	    {
	     if((b.first_vector=(VECTOR*)malloc(sizeof(VECTOR)))==NULL)
	       {
		closegraph();
		cout<<"not enough memory in do_drawing()";
		exit(1);
	       }
	     b.first_vector->x=p.x;         //create first node of linked list
	     b.first_vector->y=p.y;
	     temp1=b.first_vector;
	     HideMouse();
	     putpixel(p.x,p.y,b.color);
	     ShowMouse();
	    }
	 }
       else                                                 //following points
	 {
	  while(MouseDownLeft());
	  GetMouseLocation(&p);
	  b.num_points++;
	  p.y-=17;                                      //??? - don't know why
	  if(between(p,1,18,539,429))
	    {
	     if((temp2=(VECTOR*)malloc(sizeof(VECTOR)))==NULL)
	       {
		closegraph();
		cout<<"not enough memory in do_drawing()";
		exit(1);
	       }
	     temp1->next_vector=temp2;          //create linked list of points
	     temp2->x=p.x;
	     temp2->y=p.y;
	     temp2->next_vector=NULL;
	     HideMouse();
	     line(temp1->x,temp1->y,temp2->x,temp2->y);       //connect points
	     ShowMouse();
	     temp1=temp2;
	    }
	 }
      }
   }
 if(draw_flag)
   {                                   //close polygon, prepare and display it
    line(temp2->x,temp2->y,b.first_vector->x,b.first_vector->y);
    do_average();
    put_image();
   }
 setviewport(0,0,getmaxx(),getmaxy(),0);
}

void choose_color()
{
 int color;

 color_flag=1;
 if(draw_flag)
    save_flag=0;
 color=floor(p.x/36);
 setfillstyle(1,color+1);
 setcolor(color+1);
 b.color=color+1;
 bar3d(550,385,629,470,0,0);
}

void put_image()             //draws element on screen with current attributes
{
 VECTOR *temp,start,end;
 int i;

 if(!draw_flag)
   return;
 HideMouse();
 setviewport(1,18,539,429,1);
 clearviewport();
 temp=b.first_vector;
 for(i=0;i<b.num_points;i++)                        //for all element's points
   {
    start.x=temp->x;                            //coordinates of current point
    start.y=temp->y;
    temp=temp->next_vector;                                 //go to next point
    if(temp==NULL)                           //last point returns to beggining
       temp=b.first_vector;
    end.x=temp->x;                                 //coordinates of next point
    end.y=temp->y;
    transform(&start);                  //apply attributes on both end of line
    transform(&end);
    line(start.x,start.y,end.x,end.y);                     //draw current line
   }
 setviewport(0,0,getmaxx(),getmaxy(),0);
 ShowMouse();
}

void transform(VECTOR *v)                  //calculates new position for point
{
 v->x=v->x*cos(angle)-v->y*sin(angle);                              //rotation
 v->y=v->y*cos(angle)+v->x*sin(angle);
 v->x*=zoom;                                                         //zooming
 v->y*=zoom;
 v->x+=offsetx;                                                     //movement
 v->y+=offsety;
}

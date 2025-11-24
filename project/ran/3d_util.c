/****************************************************************************
*                                                                           *
* SUBJECT:	Computer Graphics .                                         *
* --------                                                                  *
*                                                                           *
* TITLE:        3D Graphic Utility.                                         *
* ------                                                                    *
*                                                                           *
* FILE:		3d_util.c                                                   *
* -----                                                                     *
*                                                                           *
* WRITTEN BY:	Iron Ran	023914260	"iron"                      *
* -----------	Sholkis Moshe   059764993	"shool"                     *
*                                                                           *
* UPDATES:	1st writing - 26/11/94                                      *
* --------      Modify #1     26/12/94                                      *
*		Modify #2     03/01/95		"Z Sort",cleardevice        *
*		Modify #3     17/02/95		Palette initilizing.	    *
*                                                                           *
*****************************************************************************
*                                                                           *
* DESCRIPTION: this file contains all private procedures for initializing   *
* ------------ the graphics modes and all procedures for drawing the        *
*              structures.                                                  *
*                                                                           *
****************************************************************************/

#include <stdio.h>
#include <dos.h>
#include <mem.h>
#include <string.h>
#include <math.h>

#include "types.def"
#include "int_math.h"
#include "3d_util.h"
#include "util.h"


#define GRAPH_SEG	0xFFA0
#define GRAPH_OFF	0x006E




#define VGA320x200x256_SEG  0xA000
#define	VGA320x200x256_SIZE 64000
#define	Y_SIZE		200
#define	X_SIZE		320



/************************/
/* EXTERNAL VARIABLES   */
/************************/

extern int sky_color;			/* sky background color 	*/
extern int ground_color;		/* ground background color 	*/
extern VECTOR view ;			/* view point 			*/
extern VECTOR light;			/* light source			*/
extern VECTOR n_view ;			/* normelized view point 	*/
extern VECTOR n_light;			/* normelized light source	*/
extern MATRIX IDENT_MATRIX;


/*********************/
/* LOCAL VARIABLES   */
/*********************/

static int s_active_page;		/* current active page 		*/
static POLY_ELEM *s_draw_polyelem=NULL;	/* starting polyelem on z-sort  */
static int s_min_x;			/* minimum x cordinate          */
static int s_min_y;			/* minimum y cordinate          */
static int s_max_x;			/* maximum x cordinate          */
static int s_max_y;			/* maximum y cordinate          */
static int s_mid_x;                     /* center x cordinate           */
static int s_mid_y;                     /* center x cordinate		*/


static CORD_XY s_cord[20];		/* scrach-pad for polygons 	*/
static PALETTE s_color_16[16];		/* 16 colors palette table	*/
static PALETTE s_color_256[256];	/* 16 colors palette table	*/
static far char DISP[VGA320x200x256_SIZE];		// temp DISP buffer		*/
static far char *GRAPH_CHAR=MK_FP(GRAPH_SEG,GRAPH_OFF);	// graphic chars


static unsigned G_OFFSET=0;
static unsigned G_POS_X=0;
static unsigned G_POS_Y=0;
static unsigned G_COLOR=0;
static unsigned G_MAXWIN_X=319;
static unsigned G_MAXWIN_Y=199;
static unsigned G_MINWIN_X=0;
static unsigned G_MINWIN_Y=0;
static char G_EDGE_COLOR=0;		// special edge color
static char G_BLACK=0x0f;		// black color


#define offset(x,y)	x+G_MINWIN_X+(y+G_MINWIN_Y)*X_SIZE
#define putpixel(x,y,c) G_OFFSET=offset(x,y);DISP[G_OFFSET]=(char)c
#define getpixel(x,y)   (char)DISP[offset(x,y)]
#define	getdirect(o)	(char)DISP[o]
#define moveto(x,y)	G_OFFSET=offset(x,y);G_POS_X=x;G_POS_Y=y
#define setcolor(c)	G_COLOR=c
#define getcolor()	G_COLOR
#define	putdirect(o,c)	DISP[o]=(char)c
#define	update_screen(buf)   movedata(FP_SEG(buf), FP_OFF(buf),\
				 VGA320x200x256_SEG, 0,\
				 VGA320x200x256_SIZE)



/****************************************************************************
*                                                                           *
* Procedure: 	1.my_moveto  2.my_setcolor. 3.my_setfillstyle               *
* ---------                                                                 *
* Inputs:	1.new (x,y) position.  2.color number. 3. style , color     *
* -------                                                                   *
* Outputs:      1. & 2. &  3.- none.                                        *
* --------                                                                  *
* Description:  This two procedures are private update of CP and color.     *
* ------------  written for compitability with line drawing procedure.      *
*                                                                           *
* Date:		1st writing - 26/11/1994.                                   *
* -----                                                                     *
****************************************************************************/

void my_setcolor(int color)
{
 setcolor(color);
}


/****************************************************************************
*                                                                           *
* Procedure:	my_lineto.                                                  *
* ---------                                                                 *
* Inputs:       target (x,y) position.                                      *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  Draw line from the private CP to the target position        *
* ------------  pixel by pixel.                                             *
*                                                                           *
* Date:		1st writing - 26/11/1994.                                   *
* -----                                                                     *
****************************************************************************/


void my_line(int left,int top,int right,int bottom)
{
 moveto(left,top);
 lineto(right,bottom);
}


int lineto(int x,int y)
{
static int dx,dy,loopx,loopy,tempx,tempy,signx,signy,incy;

/* find the sign of dx & dy */

 dx=x-(int)G_POS_X;
 dy=y-(int)G_POS_Y;


 if (dx>0)
  signx=1;
 else
 if (dx<0)
  signx=-1;
 else
  signx=0;

 if (dy>0)
  {
   signy=1;
   incy=X_SIZE;
  }
 else
 if (dy<0)
  {
   signy=-1;
   incy=-X_SIZE;
  }
 else
  {
   signy=0;
   incy=0;
  }


 loopx=tempx=dx=abs(dx);
 loopy=tempy=dy=abs(dy);


 if (dx>dy)
  while(loopx--)
  {
   if ((G_POS_X<=s_max_x) && (G_POS_Y<=s_max_y) &&
       (G_POS_X>=s_min_x) && (G_POS_Y>=s_min_y))
	  putdirect(G_OFFSET,G_COLOR);

   G_POS_X+=signx;
   G_OFFSET+=signx;
   if ((tempx-=dy)<=0)
    {
     G_POS_Y+=signy;
     G_OFFSET+=incy;
     tempx+=dx;
    }
  }
 else
  while(loopy--)
  {
   if ((G_POS_X<=s_max_x) && (G_POS_Y<=s_max_y) &&
       (G_POS_X>=s_min_x) && (G_POS_Y>=s_min_y))
	  putdirect(G_OFFSET,G_COLOR);
   G_POS_Y+=signy;
   G_OFFSET+=incy;
   if ((tempy-=dx)<=0)
    {
     G_POS_X+=signx;
     G_OFFSET+=signx;
     tempy+=dy;
    }
  }
  return;
}



void my_bar(int x1,int y1,int x2,int y2)
{
unsigned origen=offset(x1,y1);
unsigned length=x2-x1+1;

 while(y1<=y2)
 {
  memset(DISP+origen, G_COLOR, length);
  y1++;
  origen+=X_SIZE;
 }
}


void fillpoly(int numpoints, int far *polypoints)
{
static int min_x,max_x,min_y,max_y,temp_color;
static int idx,sign_x,sign_y,dx,dy,pos_x,pos_y,pix_on,origen_x,origen_y;
static int i,j,start_x,end_x;

 temp_color=max(getcolor(),G_BLACK);
 setcolor(G_EDGE_COLOR);
 min_x=max_x=origen_x=polypoints[0];
 min_y=max_y=origen_y=polypoints[1];
 moveto(origen_x,origen_y);
 idx=2;
 while (--numpoints)
 {
  lineto(polypoints[idx],polypoints[idx+1]);
  if (min_x>polypoints[idx]) min_x=polypoints[idx];
  if (max_x<polypoints[idx]) max_x=polypoints[idx];
  idx++;
  if (min_y>polypoints[idx]) min_y=polypoints[idx];
  if (max_y<polypoints[idx]) max_y=polypoints[idx];
  idx++;
 }
 lineto(origen_x,origen_y);


 setcolor(temp_color);

 if (((min_x<s_min_x) && (max_x>s_max_x)) ||
     ((min_y<s_min_y) && (max_y>s_max_y))) return;

 min_x=max(min_x,s_min_x);
 max_x=min(max_x,s_max_x);
 min_y=max(min_y,s_min_y);
 max_y=min(max_y,s_max_y);


 for(i=min_y;i<=max_y;i++)
 {
  pix_on=OFF;
  for(j=min_x;j<=max_x;j++)
    if (getpixel(j,i)==G_EDGE_COLOR)
     {
      if (!pix_on) end_x=start_x=j;
      else end_x=j;
      pix_on=ON;
     }
  if (pix_on) my_bar(start_x,i,end_x,i);
 }
}


void clr_scr(char far *buf,char color)
{
 memset(buf, color, VGA320x200x256_SIZE);
}


void put_bin(int x,int y,char c)
{
int i,j;
long off=((long)c)*8;
char mask;


 for(j=0;j<8;j++)
 {
  mask=0x01;
  for (i=7;i>=0;i--)
  {
   if ((*(GRAPH_CHAR+off)) & mask) putpixel(x+i,y+j,G_COLOR);
   mask=(mask<<1);
  }
  off++;
 }
}

void my_outtextxy(int x,int y,char str[])
{
int i=0;

 while(str[i])
  {
   put_bin(x,y,str[i]);
   i++;
   x+=8;
  }
}


/****************************************************************************
*                                                                           *
* Procedure: 	opengraph.                                                  *
* ---------                                                                 *
* Inputs:	none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description: 	Private initgraph to initialize the screen graphic modes.   *
* ------------                                                              *
* Date:		1st writing - 26/12/1994.                                   *
* -----                                                                     *
****************************************************************************/

int opengraph()
{
union REGS inregs,outregs;

 inregs.h.ah=0;
 inregs.h.al=0x13;
 int86(0x10, &inregs,&outregs);

 // viewport settings

 s_max_x=X_SIZE;
 s_max_y=Y_SIZE;
 s_min_x=0;
 s_min_y=0;
 s_mid_x=s_max_x/2;
 s_mid_y=s_max_y/2;



 // real cordinates

 G_MINWIN_X=0;
 G_MAXWIN_X=X_SIZE;
 G_MINWIN_Y=0;
 G_MAXWIN_Y=Y_SIZE;

 init_palette();
 return;
}

int closegraph()
{
 return;
}





/****************************************************************************
*                                                                           *
* Procedure: 	f_project.                                                  *
* ---------                                                                 *
* Inputs:       v - view point vector                                       *
* -------       x - vector to project                                       *
*               y - two dimentional screen vector                           *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  project vector (x) to screen vector (y) by view point (v).  *
* ------------                                                              *
*                                                                           *
* Date:		1st writing - 26/12/1994.                                   *
* -----                                                                     *
****************************************************************************/

void f_project(VECTOR v,VECTOR x,VECTOR y)
{
 if (abs(v[Z_]-x[Z_])>=1)
 {
  y[X_]=((x[X_]-v[X_])*v[Z_])/(v[Z_]-x[Z_]);
  y[Y_]=((x[Y_]-v[Y_])*v[Z_])/(v[Z_]-x[Z_]);
 }
 else
 {
  y[X_]=((x[X_]-v[X_])*v[Z_])/(v[Z_]-x[Z_]+1);
  y[Y_]=((x[Y_]-v[Y_])*v[Z_])/(v[Z_]-x[Z_]+1);
 }
}

/****************************************************************************
*                                                                           *
* Procedure: 	draw_polygon.                                               *
* ---------                                                                 *
* Inputs:	p - pointer to the polygon structure.                       *
* ------- 	m - matrix[4,4] for transformation.                         *
*               v - the view point vector.                                  *
*               color - the color of the polygon.                           *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  this procedure draws the pointed polygon with the actual    *
* ------------  transformation , view point position and color.             *
*                                                                           *
* Date:		1st writing - 26/12/1994.                                   *
* -----                                                                     *
****************************************************************************/



int draw_polygon(POLYGON *p,MATRIX m,VECTOR v,int color)
{
int i;
VECTOR temp1,temp2,origen;
int xy_out;

 xy_out=-p->vector_no-p->vector_no;
 for(i=0;((i<p->vector_no) && (xy_out<0));i++)
  {
   f_mul_matrix_vector(m,(p->vector)[i],temp1);
   if (temp1[Z_]<=v[Z_]) xy_out=0;
   f_project(v,temp1,temp2);
   s_cord[i][X_]=s_mid_x+(int)temp2[X_];
   s_cord[i][Y_]=s_mid_y-(int)temp2[Y_];
//   if ((s_cord[i][X_]>s_max_x) || (s_cord[i][X_]<s_min_x)) xy_out++;
//   if ((s_cord[i][Y_]>s_max_y) || (s_cord[i][Y_]<s_min_y)) xy_out++;
   if ((s_cord[i][X_]>s_max_x) || (s_cord[i][X_]<s_min_x)) xy_out=0;
   if ((s_cord[i][Y_]>s_max_y) || (s_cord[i][Y_]<s_min_y)) xy_out=0;
  }

 if (xy_out<0)
  {
   setcolor(color);
   fillpoly(p->vector_no,(int *)s_cord);
  }
 return;
}



/****************************************************************************
*                                                                           *
* Procedure:	merge                                                       *
* ---------                                                                 *
* Inputs:       l1,l2 - linked lists of polygon elements                    *
* -------                                                                   *
* Outputs:      pointer to merged list.                                     *
* --------                                                                  *
* Description:  merge two lists of elements according to the average	    *
* ------------	depth of the polygon                                        *
*                                                                           *
* Date:		1st writing - 22/01/1995.                                   *
* -----                                                                     *
****************************************************************************/

POLY_ELEM *merge(POLY_ELEM *l1,POLY_ELEM *l2)
{
POLY_ELEM *first,*temp,*last=NULL;

 while ((l1!=NULL) && (l2!=NULL))
 {
  if (((l1->depth>l2->depth) && !(l2->hide_normal & 0x02)) || (l1->hide_normal & 0x02))
   {
    temp=l1;
    l1=l1->list;
   }
  else
   {
    temp=l2;
    l2=l2->list;
   }
  if (last==NULL) first=temp;
  else last->list=temp;

  last=temp;
 }
 if (last!=NULL)
  if (l1!=NULL) last->list=l1;
  else last->list=l2;
 else
  if (l1!=NULL) first=l1;
  else first=l2;

 return(first);
}

/****************************************************************************
*                                                                           *
* Procedure:    merge_sort                                                  *
* ---------                                                                 *
* Inputs:       queue - pointer to a queue of lists                         *
* -------                                                                   *
* Outputs:      list of sorted polygon elements.                            *
* --------                                                                  *
* Description:  this procedure sorts all the polygons elements by there     *
* ------------  Z averege point in O(log(n)) using merge sort algorithm     *
*                                                                           *
* Date:		1st writing - 22/01/1995.                                   *
* -----                                                                     *
****************************************************************************/

POLY_ELEM *merge_sort(POLY_ELEM **queue)
{
POLY_ELEM *l1,*l2,*l3;

 pop_q(queue,&l1);
 pop_q(queue,&l2);
 while (l2!=NULL)
 {
  l3=merge(l1,l2);
  push_q(queue,&l3);
  pop_q(queue,&l1);
  pop_q(queue,&l2);
 }
 return(l1);
}

/****************************************************************************
*                                                                           *
* Procedure:	draw_z_sort                                                 *
* ---------                                                                 *
* Inputs:	element - pointer to the first poly-elem structure.         *
* -------	m - matrix[4,4] for transformation.                         *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  draws all the polygons sorted by their Z averege point.     *
* ------------                                                              *
*                                                                           *
* Date:		1st writing - 26/12/1994.                                   *
* -----                                                                     *
****************************************************************************/

int draw_z_sort(ELEMENT *element)
{
POLY_ELEM *p=NULL;
POLY_ELEM *q=NULL;


 update_tree(element,IDENT_MATRIX,IDENT_MATRIX,&q);
 p=merge_sort(&q);

 while(p!=NULL)
 {
  draw_polygon(p->polygon,p->draw_mat,view ,p->color);
  p=p->list;
 }
 return;
}



/****************************************************************************
*                                                                           *
* Procedure:	update_tree                                                 *
* ---------                                                                 *
* Inputs:	p     - pointer to the element structure.                   *
* -------	m     - matrix[4,4] for transformation.                     *
*		rm    - matrix[4,4] for rotations only.                     *
*		queue - queue of poly-elements.                             *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description: 	this procedure updates all Element's polygon/s and          *
* ------------  recursivly all the Element's sons using DFS.                *
*                                                                           *
* Date:		1st writing - 03/01/1995.                                   *
* -----                                                                     *
****************************************************************************/

int update_tree(ELEMENT *p,MATRIX m,MATRIX rm,POLY_ELEM **queue)
{
POLY_ELEM *temp_poly_elem;

VECTOR 	normal;
VECTOR 	offset;
VECTOR 	fill;
VECTOR  dist;
VECTOR 	temp1,temp2;
FRUC	scalar;
MATRIX	rot,rot1;

 while(p!=NULL)
 {
 if (p->active_flag)
  {
   rotate_matrix(rot,p->attrib);
   f_mul_matrix_matrix(rm,rot,rot1);
   f_mul_matrix_matrix(m,p->mat,p->draw_mat);
   temp_poly_elem=p->poly_list;
   while(temp_poly_elem!=NULL)
   {
    mul_matrix_vector(p->draw_mat,temp_poly_elem->polygon->fill,fill);
    mul_matrix_vector(rot1,temp_poly_elem->normal,normal);

    sub_vector_vector(fill,view,dist);
    temp_poly_elem->depth=mul_vector_vector(dist,dist);

    scalar=mul_vector_vector(normal,light);
    if ((scalar<0) && !(temp_poly_elem->hide_normal & 0x08)) scalar=0;
    scalar=min(labs(scalar),0xfffffl);
    if  (!(temp_poly_elem->hide_normal & 0x04))
	    temp_poly_elem->color=(temp_poly_elem->color & 0x0f) | ((scalar>>12) & 0xf0);

    if  (!(temp_poly_elem->hide_normal & 0x01) || (mul_vector_vector(normal,dist)<0))
     {
      mul_matrix_vector(p->draw_mat,temp_poly_elem->polygon->fill,temp_poly_elem->fill);
      copy_matrix(p->draw_mat,temp_poly_elem->draw_mat);
      temp_poly_elem->list=NULL;
      push_q(queue,&temp_poly_elem);
     }
    temp_poly_elem=temp_poly_elem->next;
   }
   if (p->son!=NULL) update_tree(p->son,p->draw_mat,rot1,queue);
  }
  p=p->next;
 }
 return;
}

/****************************************************************************
*                                                                           *
* Procedure:	draw_z_sort_elem                                            *
* ---------                                                                 *
* Inputs:	element - pointer to the first poly-elem structure.         *
* -------	m - matrix[4,4] for transformation.                         *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  draws all the polygons sorted by their Z averege point.     *
* ------------                                                              *
*                                                                           *
* Date:		1st writing - 26/12/1994.                                   *
* -----                                                                     *
****************************************************************************/

int draw_z_sort_elem(ELEMENT *element)
{
POLY_ELEM *p=NULL;
POLY_ELEM *q=NULL;


 update_elem(element,IDENT_MATRIX,IDENT_MATRIX,&q);
 p=merge_sort(&q);

 while(p!=NULL)
 {
  draw_polygon(p->polygon,p->draw_mat,view ,p->color);
  p=p->list;
 }
 return;
}



/****************************************************************************
*                                                                           *
* Procedure:	update_elem                                                 *
* ---------                                                                 *
* Inputs:	p     - pointer to the element structure.                   *
* -------	m     - matrix[4,4] for transformation.                     *
*		rm    - matrix[4,4] for rotations only.                     *
*		queue - queue of poly-elements.                             *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description: 	this procedure updates all Element's polygon/s and          *
* ------------  recursivly all the Element's sons using DFS.                *
*                                                                           *
* Date:		1st writing - 03/01/1995.                                   *
* -----                                                                     *
****************************************************************************/

int update_elem(ELEMENT *p,MATRIX m,MATRIX rm,POLY_ELEM **queue)
{
POLY_ELEM *temp_poly_elem;

VECTOR 	normal;
VECTOR 	offset;
VECTOR 	fill;
VECTOR  dist;
VECTOR 	temp1,temp2;
FRUC	scalar;
MATRIX	rot,rot1;

 if(p!=NULL)
 {

  rotate_matrix(rot,p->attrib);
  f_mul_matrix_matrix(rm,rot,rot1);
  f_mul_matrix_matrix(m,p->mat,p->draw_mat);
  temp_poly_elem=p->poly_list;
  while(temp_poly_elem!=NULL)
  {
   mul_matrix_vector(p->draw_mat,temp_poly_elem->polygon->fill,fill);
   mul_matrix_vector(rot1,temp_poly_elem->normal,normal);

   sub_vector_vector(fill,view,dist);
   temp_poly_elem->depth=mul_vector_vector(dist,dist);

   scalar=mul_vector_vector(normal,light);
   if ((scalar<0) && !(temp_poly_elem->hide_normal & 0x08)) scalar=0;

   scalar=min(labs(scalar),0xfffffl);
   if  (!(temp_poly_elem->hide_normal & 0x04))
	   temp_poly_elem->color=(temp_poly_elem->color & 0x0f) | ((scalar>>12) & 0xf0);

   if  (!(temp_poly_elem->hide_normal & 0x01) || (mul_vector_vector(normal,dist)<0))
    {
     mul_matrix_vector(p->draw_mat,temp_poly_elem->polygon->fill,temp_poly_elem->fill);
     copy_matrix(p->draw_mat,temp_poly_elem->draw_mat);
     temp_poly_elem->list=NULL;
     push_q(queue,&temp_poly_elem);
    }
   temp_poly_elem=temp_poly_elem->next;
  }
  if (p->son!=NULL) update_tree(p->son,p->draw_mat,rot1,queue);
 }
 return;
}



/****************************************************************************
*                                                                           *
* Procedure:	push_queue                                                  *
* ---------                                                                 *
* Inputs:	queue - queue of poly-elements.                             *
* -------       element - queue element                                     *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  this procedure insert new element to the element queue      *
* ------------                                                              *
* Date:		1st writing - 22/01/1995.                                   *
* -----                                                                     *
****************************************************************************/


int push_q(POLY_ELEM **queue,POLY_ELEM **element)
{
 if (*queue!=NULL)
 {
  (*element)->next_list=(*queue)->next_list;
  (*queue)->next_list=(*element);
 }
 else (*element)->next_list=(*element);
 (*queue)=(*element);		/* queue allways point to last element */
 return;
}

/****************************************************************************
*                                                                           *
* Procedure:	pop_queue                                                   *
* ---------                                                                 *
* Inputs:	queue - queue of poly-elements.                             *
* -------       element - queue element                                     *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  this procedure pop an element from top of the element queue *
* ------------  into element.                                               *
*                                                                           *
* Date:		1st writing - 22/01/1995.                                   *
* -----                                                                     *
****************************************************************************/


int pop_q(POLY_ELEM **queue,POLY_ELEM **element)
{
 if ((*queue)==NULL) (*element)=NULL;
 else
 {
  (*element)=(*queue)->next_list;
  if ((*queue)->next_list==(*queue)) (*queue)=NULL;
  else (*queue)->next_list=(*element)->next_list;
 }
 return;
}



/****************************************************************************
*                                                                           *
* Procedure:	flip_page.                                                  *
* ---------                                                                 *
* Inputs:	none                      				    *
* -------                                                                   *
* Outputs:	none.                                                       *
* --------                                                                  *
* Description:  this procedure swap between the active page and the visual  *
* ------------  page.                                                       *
*                                                                           *
* Date:		1st writing - 26/11/1994.                                   *
* -----                                                                     *
****************************************************************************/

int flip_page()
{
 update_screen(DISP);
 return;
}

/****************************************************************************
*                                                                           *
* Procedure:	my_setviewport.                                             *
* ---------                                                                 *
* Inputs:	left,top,right,bottom - screen cordinates.                  *
* -------                                                                   *
* Outputs:	none.                                                       *
* --------                                                                  *
* Description:  this procedure set the graphic wiewport .                   *
* ------------                                                              *
*                                                                           *
* Date:		1st writing - 20/01/1995.                                   *
* -----                                                                     *
****************************************************************************/

int my_setviewport(int left,int top,int right,int bottom)
{
   s_min_x=0;
   s_min_y=0;
   s_max_x=right-left;
   s_max_y=bottom-top;
   s_mid_x=s_max_x/2;
   s_mid_y=s_max_y/2;

   G_MINWIN_X=left;
   G_MAXWIN_X=right;
   G_MINWIN_Y=top;
   G_MAXWIN_Y=bottom;

   return;
}


/****************************************************************************
*                                                                           *
* Procedure:	my_clearviewport.                                           *
* ---------                                                                 *
* Inputs:	none.                                                       *
* -------                                                                   *
* Outputs:	none.                                                       *
* --------                                                                  *
* Description:  this procedure clears the graphic wiewport .                *
* ------------                                                              *
*                                                                           *
* Date:		1st writing - 20/01/1995.                                   *
* -----                                                                     *
****************************************************************************/

int my_clearviewport()
{
 setcolor(sky_color);
 my_bar(s_min_x,s_min_y,s_max_x,s_mid_y);
 setcolor(ground_color);
 my_bar(s_min_x,s_mid_y,s_max_x,s_max_y);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:	init_pallete                                                *
* ---------                                                                 *
* Inputs:	none.                                                       *
* -------                                                                   *
* Outputs:	none.                                                       *
* --------                                                                  *
* Description:  this procedure reads the default vga palette & create 256   *
* ------------	colors from it. each of the 16 vga color is created with    *
*		16 intensity values.                                        *
*                                                                           *
*		color iiiicccc i-intensity bits,c-color bits                *
*                                                                           *
* Date:		1st writing - 17/02/1995.                                   *
* -----                                                                     *
****************************************************************************/

int init_palette()
{
int i,j;

 getvgapalette(s_color_16,16);
 for(i=0;i<16;i++)
  for(j=0;j<16;j++)
  {
   s_color_256[j*16+i][R_]=(char)(((int)(s_color_16[i][R_])*j)/15);
   s_color_256[j*16+i][G_]=(char)(((int)(s_color_16[i][G_])*j)/15);
   s_color_256[j*16+i][B_]=(char)(((int)(s_color_16[i][B_])*j)/15);
  }
 setvgapalette(s_color_256,256);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:	get vga pallete                                             *
* ---------                                                                 *
* Inputs:	colors - number of color to get from the vga palette.       *
* -------                                                                   *
* Outputs:	PalBuf - buffer of R.G.B triplets of the palette.           *
* --------                                                                  *
* Description:  this procedure reads the vga card palette from the vga      *
* ------------	bios service & retrive its palette.                         *
*                                                                           *
* Date:		1st writing - 17/02/1995.                                   *
* -----                                                                     *
****************************************************************************/

int getvgapalette(PALETTE PalBuf[],int colors)
{
  struct REGPACK reg;

  reg.r_ax = 0x1017;
  reg.r_bx = 0;
  reg.r_cx = colors;
  reg.r_es = FP_SEG(PalBuf);
  reg.r_dx = FP_OFF(PalBuf);
  intr(0x10,&reg);
  return;
}


/****************************************************************************
*                                                                           *
* Procedure:	set vga pallete                                             *
* ---------                                                                 *
* Inputs:	colors - number of color to set on the vga palette.         *
* -------       PalBuf - buffer of R.G.B triplets of the palette.           *
*                                                                           *
* Outputs:	none.                                                       *
* --------                                                                  *
* Description:  this procedure sets the vga card palette from the palette   *
* ------------	with thr bios service .                                     *
*                                                                           *
* Date:		1st writing - 17/02/1995.                                   *
* -----                                                                     *
****************************************************************************/

int setvgapalette(PALETTE PalBuf[],int colors)
{
  struct REGPACK reg;

  reg.r_ax = 0x1012;
  reg.r_bx = 0;
  reg.r_cx = colors;
  reg.r_es = FP_SEG(PalBuf);
  reg.r_dx = FP_OFF(PalBuf);
  intr(0x10,&reg);
  return;
}

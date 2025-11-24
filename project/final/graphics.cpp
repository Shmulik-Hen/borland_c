#include "graphics.h"
#include "types.def"
#include <math.h>
#include <mem.h>
#include <dos.h>
#include <stdio.h>

#define CHARS_SEG  0xFFA0
#define CHARS_OFF  0x006E
#define VGA_SEG    0xA000
#define VGA_SIZE   64000

enum rgb{R,G,B};
enum flag{OFF,ON};

static far char BUFFER[VGA_SIZE];
static far char *GRAPH_CHARS=(char*)MK_FP(CHARS_SEG,CHARS_OFF);
palette pal_16_colors[16];
palette pal_256_colors[256];
unsigned G_OFFSET=0;
unsigned G_POS_X=0;
unsigned G_POS_Y=0;
unsigned G_MIN_X=0;
unsigned G_MIN_Y=0;
unsigned G_MAX_X=320;
unsigned G_MAX_Y=200;
unsigned G_COLOR=0;
char G_EDGE_COLOR=0x00;
char G_BLACK=0x0f;
int vp_min_x;
int vp_min_y;
int vp_max_x;
int vp_max_y;
int vp_mid_x;
int vp_mid_y;

#define offset(x,y)          x+G_MIN_X+(y+G_MIN_Y)*MAX_X
//#define putpixel(x,y,c)      G_OFFSET=offset(x,y); BUFFER[G_OFFSET]=(char)c
#define putpixel(x,y,c)      BUFFER[offset(x,y)]=(char)c
#define getpixel(x,y)        (char)BUFFER[offset(x,y)]
#define m_setcolor(c)        G_COLOR=c
#define getcolor()           G_COLOR
#define moveto(x,y)          G_OFFSET=offset(x,y); G_POS_X=x; G_POS_Y=y
#define putdirect(o,c)       BUFFER[o]=(char)c
#define getdirect(o)         (char)BUFFER[o]
#define update_screen(buff)  movedata(FP_SEG(buff), FP_OFF(buff), \
				      VGA_SEG, 0, VGA_SIZE)


void setcolor(char color)
{
 m_setcolor(color);
}

void line(int left, int top, int right, int bottom)
{
 moveto(left,top);
 lineto(right,bottom);
}

void lineto(int x, int y)
{
 int dx,loopx,tempx,signx;
 int dy,loopy,tempy,signy;
 int y_inc;

 dx=x-(int)G_POS_X;
 dy=y-(int)G_POS_Y;
 if(dx>0)
   signx=1;
 else if(dx<0)
	 signx=-1;
      else signx=0;
 if(dy>0)
   {
    signy=1;
    y_inc=MAX_X;
   }
 else if(dy<0)
	{
	 signy=-1;
	 y_inc=-MAX_X;
	}
      else
	{
	 signy=0;
	 y_inc=0;
	}
 loopx=tempx=dx=abs(dx);
 loopy=tempy=dy=abs(dy);
 if(dx>dy)
   while(loopx--)
     {
      if((G_POS_X<=vp_max_x) && (G_POS_Y<=vp_max_y) &&
	 (G_POS_X>=vp_min_x) && (G_POS_Y>=vp_min_y) )
	  putdirect(G_OFFSET,G_COLOR);

      G_POS_X+=signx;
      G_OFFSET+=signx;
      if((tempx-=dy)<=0)
	{
	 G_POS_Y+=signy;
	 G_OFFSET+=y_inc;
	 tempx+=dx;
	}
     }
 else
   while(loopy--)
     {
      if((G_POS_X<=vp_max_x) && (G_POS_Y<=vp_max_y) &&
	 (G_POS_X>=vp_min_x) && (G_POS_Y>=vp_min_y) )
	  putdirect(G_OFFSET,G_COLOR);
      G_POS_Y+=signy;
      G_OFFSET+=y_inc;
      if((tempy-=dx)<=0)
	{
	 G_POS_X+=signx;
	 G_OFFSET+=signx;
	 tempy+=dy;
	}
     }
}

void bar(int left, int top, int right, int bottom)
{
 unsigned origin=offset(left,top);
 unsigned length=right-left;//+1;

 while(top<=bottom)
   {
    memset((void*)(BUFFER+origin), G_COLOR, length);
    top++;
    origin+=MAX_X;
   }
}

void fillpoly(int numpoints, int far *polypoints)
{
 static int min_x,max_x,min_y,max_y,temp_color;
 static int idx,pix_on,origen_x,origen_y;
 static int i,j,start_x,end_x;

 temp_color=max(getcolor(),G_BLACK);
 m_setcolor(G_EDGE_COLOR);
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

 m_setcolor(temp_color);

 if (((min_x<vp_min_x) && (max_x>vp_max_x)) ||
     ((min_y<vp_min_y) && (max_y>vp_max_y))) return;

 min_x=max(min_x,vp_min_x);
 max_x=min(max_x,vp_max_x);
 min_y=max(min_y,vp_min_y);
 max_y=min(max_y,vp_max_y);


 for(i=min_y;i<=max_y;i++)
 {
  pix_on=OFF;
  for(j=min_x;j<=max_x;j++)
    if (getpixel(j,i)==G_EDGE_COLOR)
     {
      if (!pix_on)
	end_x=start_x=j;
      else
	end_x=j;
      pix_on=ON;
     }
  if(pix_on)
    bar(start_x,i,end_x+1,i);
 }

}

void cleardevice()
{
 memset((void*)BUFFER, G_BLACK, VGA_SIZE);
}

void outtextxy(int x, int y, char *str)
{
 int i=0;

 while(str[i])
   {
    putch(x,y,str[i]);
    i++;
    x+=8;
   }
}

void putch(int x ,int y, char c)
{
 int i,j;
 long off=((long)c*8);
 char mask;

 for(j=0;j<8;j++)
   {
    mask=0x01;
    for(i=7;i>=0;i--)
      {
       if( (*(GRAPH_CHARS+off)) & mask)
	 putpixel(x+i,y+j,G_COLOR);
       mask=(mask<<1);
      }
    off++;
   }
}

void initgraph()
{
 union REGS inregs,outregs;

 inregs.h.ah=0;
 inregs.h.al=0x13;
 int86(0x10,&inregs,&outregs);

 vp_max_x=MAX_X;
 vp_max_y=MAX_Y;
 vp_min_x=0;
 vp_min_y=0;
 vp_mid_x=vp_max_x/2;
 vp_mid_y=vp_max_y/2;

 G_MAX_X=MAX_X;
 G_MAX_Y=MAX_Y;
 G_MIN_X=0;
 G_MIN_Y=0;

 init_palette();
}

void closegraph()
{
 union REGS inregs,outregs;

 inregs.h.ah=0;
 inregs.h.al=0x03;
 int86(0x10,&inregs,&outregs);
}

void setviewport(int left, int top, int right, int bottom)
{
 vp_min_x=0;
 vp_min_y=0;
 vp_max_x=right-left;
 vp_max_y=bottom-top;
 vp_mid_x=vp_max_x/2;
 vp_mid_y=vp_max_y/2;

 G_MIN_X=left;
 G_MAX_X=right;
 G_MIN_Y=top;
 G_MAX_Y=bottom;
}

void clearviewport()
{
 //m_setcolor(G_BLACK);
 //bar(vp_min_x,vp_min_y,vp_max_x,vp_max_y);
 m_setcolor(203);
 bar(vp_min_x,vp_min_y,vp_max_x,vp_mid_y);
 m_setcolor(150);
 bar(vp_min_x,vp_mid_y,vp_max_x,vp_max_y);
}

void init_palette()
{
 int i,j;

 getpalette(pal_16_colors,16);
 for(i=0;i<16;i++)
   for(j=0;j<16;j++)
     {
      pal_256_colors[j*16+i][R]=(char)(((int)(pal_16_colors[i][R])*j)/15);
      pal_256_colors[j*16+i][G]=(char)(((int)(pal_16_colors[i][G])*j)/15);
      pal_256_colors[j*16+i][B]=(char)(((int)(pal_16_colors[i][B])*j)/15);
     }
 setpalette(pal_256_colors,256);
}

void getpalette(palette buff[], int colors)
{
 struct REGPACK reg;

 reg.r_ax=0x1017;
 reg.r_bx=0;
 reg.r_cx=colors;
 reg.r_dx=FP_OFF(buff);
 reg.r_es=FP_SEG(buff);
 intr(0x10,&reg);
}

void setpalette(palette buff[], int colors)
{
 struct REGPACK reg;

 reg.r_ax=0x1012;
 reg.r_bx=0;
 reg.r_cx=colors;
 reg.r_dx=FP_OFF(buff);
 reg.r_es=FP_SEG(buff);
 intr(0x10,&reg);
}

void flip_page()
{
 update_screen(BUFFER);
}

void put_scr()
{
 FILE *stream;
 char ch;

 stream = fopen("PLANE.SCR", "r");
 for(int j=0;j<200;j++)
   for(int i=0;i<320;i++)
     {
      ch = fgetc(stream);
      putpixel(i,j,ch);
     }
 fclose(stream);
}

void getimage(int x1,int y1, int x2, int y2, char *buff)
{
 unsigned dx=x2-x1+1;
 unsigned off=0;

 for(int y=y1;y<=y2;y++)
   {
    movedata(FP_SEG(BUFFER),FP_OFF(BUFFER)+offset(x1,y),FP_SEG(buff),FP_OFF(buff)+off,dx);
    off+=dx;
   }
}

void putimage(int x1, int y1, int x2, int y2, char *buff)
{
 unsigned dx=x2-x1+1;
 unsigned off=0;

 for(int y=y1;y<=y2;y++)
   {
    movedata(FP_SEG(buff),FP_OFF(buff)+off,FP_SEG(BUFFER),FP_OFF(BUFFER)+offset(x1,y),dx);
    off+=dx;
   }
}
#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>

typedef char palette[3];
enum rgb{R,G,B};
palette pal_16_colors[16];
palette pal_256_colors[256];

void init_palette();
void get_palette(palette buff[], int colors);
void set_palette(palette buff[], int colors);
int huge DetectVGA256();

void main()
{
 int Gd = DETECT, Gm;
 installuserdriver("SVGA256",DetectVGA256);
 initgraph(&Gd,&Gm,"");
 init_palette();

 setviewport(0,0,319,199,1);
 //clearviewport();
 /*
 for(int i=0;i<256;i+=16)
   for(int j=0;j<16;j++)
      {
       setfillstyle(1,i+j);
       bar(i,j*11,i+25,j*11+25);
      }*/

 rectangle(0,0,319,199);
 setcolor(255);

 rectangle(40,2,280,152);
 rectangle(295,170,305,180);
 circle(260,180,19);
 circle(220,180,19);
 circle(180,180,19);
 circle(140,180,19);
 circle(100,180,19);
 circle(60,180,19);
 setfillstyle(1,123);
 floodfill(1,1,255);
 outtextxy(249,154,"RPM");
 outtextxy(209,154,"MPH");
 outtextxy(169,154,"HDG");
 outtextxy(129,154,"AOA");
 outtextxy(89,154,"ALT");
 outtextxy(49,154,"ADI");
 outtextxy(282,154,"GEAR");

 getch();

 FILE *stream;
 char ch;

 stream = fopen("PLANE.SCR", "w");
 for(int j=0;j<200;j++)
   for(int i=0;i<320;i++)
     {
      ch=(char)getpixel(i,j);
      fputc(ch,stream);
     }
 fclose(stream);

 closegraph();
}

void init_palette()
{
 int i,j;

 get_palette(pal_16_colors,16);
 for(i=0;i<16;i++)
   for(j=0;j<16;j++)
     {
      pal_256_colors[j*16+i][R]=(char)(((int)(pal_16_colors[i][R])*j)/15);
      pal_256_colors[j*16+i][G]=(char)(((int)(pal_16_colors[i][G])*j)/15);
      pal_256_colors[j*16+i][B]=(char)(((int)(pal_16_colors[i][B])*j)/15);
     }
 set_palette(pal_256_colors,256);
}

void get_palette(palette buff[], int colors)
{
 struct REGPACK reg;

 reg.r_ax=0x1017;
 reg.r_bx=0;
 reg.r_cx=colors;
 reg.r_dx=FP_OFF(buff);
 reg.r_es=FP_SEG(buff);
 intr(0x10,&reg);
}

void set_palette(palette buff[], int colors)
{
 struct REGPACK reg;

 reg.r_ax=0x1012;
 reg.r_bx=0;
 reg.r_cx=colors;
 reg.r_dx=FP_OFF(buff);
 reg.r_es=FP_SEG(buff);
 intr(0x10,&reg);
}

int huge DetectVGA256()
{
  return 0;/*
  int Vid;

  printf("Which video mode would you like to use? \n");
  printf("  0) 320x200x256\n");
  printf("  1) 640x400x256\n");
  printf("  2) 640x480x256\n");
  printf("  3) 800x600x256\n");
  printf("  4) 1024x768x256\n\n>");
  scanf("%d",&Vid);
  return Vid;*/
}

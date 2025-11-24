/* Sample program that initializes the SuperVGA driver */

#include <graphics.h>
#include <stdio.h>
#include <dos.h>
#include <conio.h>

int i,j;

int huge DetectVGA256()
{
  int Vid;

  printf("Which video mode would you like to use? \n");
  printf("  0) 320x200x256\n");
  printf("  1) 640x400x256\n");
  printf("  2) 640x480x256\n");
  printf("  3) 800x600x256\n");
  printf("  4) 1024x768x256\n\n>");
  scanf("%d",&Vid);
  return Vid;
}
/*
int huge DetectVGA16()
{
  int Vid;

  printf("Which video mode would you like to use? \n");
  printf("  0) 320x200x16\n");
  printf("  1) 640x200x16\n");
  printf("  2) 640x350x16\n");
  printf("  3) 640x480x256\n");
  printf("  4) 800x600x16\n");
  printf("  5) 1024x768x16\n\n>");
  scanf("%d",&Vid);
  return Vid;
}*/

void main()
{
  int Gd = DETECT, Gm;
  //int Drv;

  clrscr();
  /*printf("Which driver would you like to use?\n");
  printf("  0) Svga256\n");
  printf("  1) Svga16\n");
  printf(">");
  scanf("%d",&Drv);
  if(Drv)
  installuserdriver("SVGA16",DetectVGA16);
  else*/
  installuserdriver("SVGA256",DetectVGA256);

  initgraph(&Gd,&Gm,"d:\\bc\\ilan");
  setcolor(15);
  do
    {
     for(i=0;i<100;i++)
	{
	 setcolor(i);
	 circle(160,100,i);
	}
     for(i=100;i>0;i--)
	{
	 setcolor(i+100);
	 circle(160,100,i);
	}
    }while (!kbhit());
  cleardevice();
  for(i=1;i<=16;i++)
      for(j=1;j<=16;j++)
	 {
	  setfillstyle(1,(i-1)*16+j-1);
	  bar((i-1)*20,(j-1)*10,i*20-2,j*10-2);
	 }
  getch();getch();
  closegraph();
}

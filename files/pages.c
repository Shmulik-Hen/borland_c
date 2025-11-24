#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

int main(void)
{
  int gdriver = VGA, gmode = VGALO, errorcode;
  int x, y, ht;

  initgraph(&gdriver, &gmode, "c:\\bc\\bgi");

  x = getmaxx() / 2;
  y = getmaxy() / 2;
  ht = textheight("W");

  setactivepage(0);
  setvisualpage(0);
  line(0, 0, getmaxx(), getmaxy());
  line(0, getmaxy(), getmaxx(), 0);
  settextjustify(CENTER_TEXT, CENTER_TEXT);
  outtextxy(x, y, "This is page #0:");
  outtextxy(x, y+ht, "Press any key to halt:");
  getch();

  setactivepage(1);
  setvisualpage(1);
  rectangle(0, 0, getmaxx(), getmaxy());
  outtextxy(x, y, "This is page #1.");
  outtextxy(x, y+ht, "Press any key to view page #1:");
  getch();

  closegraph();
  return 0;
}


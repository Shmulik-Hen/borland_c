#include "element.h"
#include "polyelem.h"
#include "graphics.h"
#include <conio.h>

extern matrix UNIT_MAT;
vector view(0,0,-1000000);
vector n_light(0,724,-724);
element *root=NULL;
int quit=0;

void main()
{
 polyelem *pe;
 init();

 while(!quit)
   {
    while(!kbhit())
      {
       keep_moving();
       update_tree(root,UNIT_MAT,UNIT_MAT);
       pe=merge_sort();

       clearviewport();
       while(pe)
	 {
	  pe->show();
	  pe=pe->next;
	 }
       flip_page();
       pe_free();
      }
    do_change();
   }
 closegraph();
}

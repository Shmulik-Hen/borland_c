#include "vector.h"
#include <conio.h>

void main()
{
 vector a,b,c,d,e;

 while(1){
 clrscr();
 a.read();
 b.read();
 c.read();
 d=find_normal(a,b,c);
 e=normalize(d);
 e.show();
 getch();}
}
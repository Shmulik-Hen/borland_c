#include <wind.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <graphini.h>

void main()
{
 start_graph();

 char *str[]={"AAAA","BBBB"};
 int i;
 my_window w1(50,50,1),w2(50,50,1);

 w1.show(0,0);
 w1.put_str(5,5,str[0]);
 w1.save();
 w1.hide();

 w2.show(0,0);
 w2.put_str(5,5,str[1]);
 w2.save();
 w2.hide();

 cleardevice();
 delay(1000);
 w2.show(150,150);
 for(i=0;i<300;i++)
    {
     w1.show(i,i);
     delay(7);
     w1.hide();
    }
 w2.hide();
 closegraph();
}
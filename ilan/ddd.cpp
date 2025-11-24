#include "stdio.h"
#include "graphics.h"
#include "dos.h"
#include "stdlib.h"
#include "time.h"

main()
{

	_stklen = 0x8000;


	randomize();
	if (InitMouse())
	{
		registerbgidriver(EGAVGA_driver);
		registerbgidriver(HERC_driver);
		if (InitGraphics())
		{
			MouseOn();
			ClearScreen();
			InitWindowManager();
			goForIt(0);
			MouseOff();
			deinitGraphics();
		}
		else
			puts("cannot open graphics");
	}
	else
		puts("Cannot locate Mouse Driver");
}

void goForIt(int n)
{
	RECT r;
	WINDOW w;
	int left,top,width,depth;

	delay(50);
	left=random(getmaxx()-100)+10;
	width=random((getmaxx()-left)-50)+40;
	top=random(getmaxy()-100)+10;
	depth=random((getmaxy()-top)-50)+40;

	SetRect(&r,left,top,left+width,top+depth);

	if (n<MAXWINDOW && OpenWindow(&w,&r))
		goForIt(n+1);
	delay(50);
	CloseWindow(&w);
}


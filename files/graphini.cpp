#include <graphics.h>
#include <iostream.h>
#include <process.h>
#include <graphini.h>

void start_graph()
{
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "");
	if (graphresult() != grOk) {
		cout << "error initialising graphics mode";
		exit(1);
	}
	cleardevice();
}

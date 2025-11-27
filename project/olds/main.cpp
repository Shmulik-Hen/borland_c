#include "element.h"
#include "polyelem.h"
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>

extern list<polygon> poly_list;
extern queue<polyelem> poly_elem_q;
extern matrix UNIT_MAT;
vector view(0, 0, -102400);
vector light(1024, 1024, -1024);
vector n_view(0, 0, -1024);
vector n_light(591, 591, -591);

void main()
{
	char filename[] = "box.dat";
	ifstream f;
	LINE line;
	polygon *poly;
	element *root = NULL, *elem1, *elem2;
	polyelem *pe;
	attrib a(1, 0, 0, 0, 0, 0, 1024);
	int gdriver = 1, gmode = 1, errorcode;

	f.open(filename, ios::in | ios::nocreate);
	if (!f)
		error("file not found:", filename);
	f.unsetf(ios::skipws);
	while (!f.eof()) {
		while ((!read_word(f, line)) && (!f.eof()))
			;
		switch (line[1]) {
		case '#':
			read_remark(f);
		case 'p':
			poly = new polygon;
			poly->read(f);
			poly_list.insert(poly);
			break;
		case 'e':
			elem1 = new element;
			elem1->read(f);
			if (!root)
				root = elem1;
			else {
				elem2 = root->find_elem(elem1->parrent);
				if (elem2)
					elem1->addnode(elem2);
				else
					error("element not found in tree::addnode()", elem1->parrent);
			}
			break;
		}
	}
	f.close();

	initgraph(&gdriver, &gmode, "d:\\bc\\bgi");
	errorcode = graphresult();
	if (errorcode != grOk) {
		getch();
		exit(1);
	}
	setfillstyle(1, 0);

	elem1 = root->find_elem("box");
	if (!elem1)
		error("element not found:", "\"box\"");

	while (!kbhit()) {
		elem1->update(a);
		update_tree(root, UNIT_MAT, UNIT_MAT, poly_elem_q);
		pe = merge_sort(poly_elem_q);
		while (pe) {
			pe->show();
			pe = pe->next;
		}
		freemem();
		// delay(100);
		// cleardevice();
	}
	getch();
	closegraph();
}

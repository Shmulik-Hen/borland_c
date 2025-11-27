#include "element.h"
#include "polyelem.h"
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>

extern list<polygon> poly_list;
extern matrix UNIT_MAT;
vector view(0, 0, -1000000);
vector n_light(0, 0, -1024);

void main()
{
	char filename[] = "plane1.dat";
	ifstream f;
	LINE line;
	polygon *poly;
	element *root = NULL, *elem1, *elem2;
	polyelem *pe;

	f.open(filename, ios::in | ios::nocreate);
	if (!f)
		error("file not found:", filename);
	f.unsetf(ios::skipws);
	while (!f.eof()) {
		while ((!read_word(f, line)) && (!f.eof()))
			;
		switch (line[1]) {
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

	int Gd = DETECT, Gm;
	initgraph(&Gd, &Gm, "");

	elem1 = root->find_elem("world");
	elem2 = root->find_elem("plane");
	elem1->update(attrib(0, 0, 0, 0, 0, 0, 3072));
	elem2->update(attrib(128, 0, 256, 0, 0, 0, 1024));

	char c;
	// while(!kbhit())
	while ((c = getch()) != 27) {
		elem2->update(attrib(4, 0, 0, 0, 0, 0, 1024));
		update_tree(root, UNIT_MAT, UNIT_MAT);
		pe = merge_sort();
		clearviewport();
		while (pe) {
			pe->show();
			pe = pe->next;
		}
		pe_free();
	}
	closegraph();
}

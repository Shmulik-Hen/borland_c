#include "element.h"
#include "polyelem.h"
#include <conio.h>

extern list<polygon> poly_list;
extern queue<polyelem> poly_elem_q;

void main()
{
	char filename[] = "elem.dat";
	ifstream f;
	LINE line;
	polygon *poly;
	element *root = NULL, *elem1, *elem2;
	polyelem *pe;
	long z = 0;

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
			pe = new polyelem;
			pe->poly = poly;
			pe->depth = unit(z++);
			poly_elem_q.push(pe);
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
	clrscr();
	pe = merge_sort(poly_elem_q);
	while (pe) {
		pe->print();
		pe = pe->next;
	}
	/*
	for(poly=poly_list.first();poly;poly=poly_list.next())
	   poly->print();
	printall(root);*/
	f.close();
}

#include "element.h"
#include <conio.h>

list<polygon> poly_list;

void main()
{
	char filename[] = "elem.dat";
	ifstream f;
	LINE line;
	polygon *poly;
	element *root = NULL, *elem1, *elem2;

	f.open(filename, ios::in | ios::nocreate);
	f.unsetf(ios::skipws);
	if (!f)
		error("file not found:", filename);
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
	clrscr();
	for (poly = poly_list.first(); poly; poly = poly_list.next())
		poly->print();
	printall(root);
	f.close();
}

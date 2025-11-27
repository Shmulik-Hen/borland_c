#include "utils.h"
#include "polygon.h"
#include "list.cpp"
#include <fstream.h>
#include <conio.h>

void main()
{
	char filename[] = "poly.dat";
	ifstream f;
	LINE line;
	polygon *p;
	list<polygon> lp;

	clrscr();
	f.open(filename, ios::in | ios::nocreate);
	f.unsetf(ios::skipws);
	if (!f)
		error("file not found:", filename);
	while (!f.eof()) {
		while ((!read_word(f, line)) && (!f.eof()))
			;
		if (line[1] == 'p') {
			p = new polygon;
			p->read(f);
			lp.insert(p);
		}
	}
	for (p = lp.first(); p; p = lp.next())
		p->print();
	f.close();
}

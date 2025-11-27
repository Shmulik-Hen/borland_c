#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream.h>

class linklist
{
private:

	linklist *next;
	linklist *prev;

public:

	linklist();
	void append(linklist *h);
	void insert(linklist *h);
	void remove();
	linklist *r_next();
	linklist *r_prev();
};

linklist::linklist()
{
	this->next = NULL;
}

void linklist::insert(linklist *h)
{
	linklist *ptr;

	ptr = h->next;
	h->next = this;
	this->prev = h;
	this->next = ptr;
	ptr->prev = this;
}

void linklist::append(linklist *h)
{
	h->next = this;
	this->prev = h;
	this->next = NULL;
}
void linklist::remove()
{
	linklist *prv, *nxt;

	prv = this->prev;
	nxt = this->r_next();
	prv->next = nxt;
	nxt->prev = prev;
}

linklist *linklist::r_next()
{
	return (next);
}

linklist *linklist::r_prev()
{
	return (prev);
}

class comp : public linklist
{
private:

	char *location[5];
	char *description[50];
	char *crd[5];
	int catno;
	int repl1;
	int repl2;
	int repl3;
	int no;

public:

	void read();
	void print();
	void fileread(fstream &f);
};

void comp::read()
{
}

void comp::print()
{
}

void comp::fileread(fstream &f)
{
	char *c;

	while (!f.eof()) {
		f >> c;
	}
}

linklist head;
comp *my;

void main()
{
	comp *last;
	char *filename;

	last = (comp *)&head;
	cout << "enter file name\n";
	cin >> filename;
	fstream f1(filename, ios::app | ios::nocreate);
	while (!f1.eof()) {
		my = new comp;
		my->fileread(f1);
		my->append(last);
		last = my;
	}
}

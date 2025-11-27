#include <iostream.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

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

class worker : public linklist
{
public:

	char name[20];
	int id;

public:

	friend istream &operator>>(istream &in, worker &w);
	/*friend ostream& operator<<(ostream &out, worker &w);*/
	void read();
	void print();
};

void worker::print()
{
	cout << "WORKER:" << name << endl;
	cout << "ID:" << id << endl;
}

void worker::read()
{
	cin >> *this;
}

istream &operator>>(istream &in, worker &w)
{
	cout << "Enter worker's name:";
	in >> w.name;
	cout << "Enter worker's id No.:";
	in >> w.id;
	return (in);
}

linklist head;
worker *my;

void main()
{
	worker *last;
	char c, *str;
	int found;

	last = (worker *)&head;
	do {
		clrscr();
		cout << "1)append" << endl;
		cout << "2)delete" << endl;
		cout << "3)search" << endl;
		cout << "4)print" << endl;
		c = getch();
		switch (c) {
		case '1':
			my = new worker;
			my->read();
			my->append(last);
			last = my;
			break;
		case '2':
			break;
		case '3':
			found = 0;
			my = (worker *)&head;
			cout << "enter worker's name:";
			cin >> str;
			while (my->r_next() != NULL) {
				my = (worker *)my->r_next();
				if (!strcmp(my->name, str)) {
					my->print();
					found = 1;
				}
			}
			if (!found)
				cout << "no such worker here!" << endl;
			cout << "press any key" << endl;
			getch();
			break;

		case '4':
			my = (worker *)&head;
			while (my->r_next() != NULL) {
				my = (worker *)my->r_next();
				my->print();
			}
			cout << endl << "press any key";
			getch();
			break;
		}
	} while (c != 27);
}

#include <string.h>
#include <iostream.h>
class tree
{
public:

	static int her;
	int id;
	int count;
	tree *t[50];

public:

	tree(int near (*m_cond)(void near *, void near *));
	int (*cond)(void *t1, void *t2);
	void addtree(tree *m_t);
	tree *search(tree *m_t);
};

tree::tree(int near (*m_cond)(void near *, void near *))
{
	id = 0;
	count = 0;
	cond = m_cond;
}

void tree::addtree(tree *m_t)
{
	m_t->t[m_t->count] = this;
	m_t->count++;
}

tree *tree::search(tree *m_t)
{
	int i;
	tree *found;
	if (cond(this, m_t) == 0) {
		cout << "**** found ***" << endl;
		return (m_t);
	}
	if (cond(this, m_t) != 0) {
		for (i = 0; i < m_t->count; i++) {
			found = search(m_t->t[i]);
			if (found != NULL)
				return (found);
		}
	}
	return (NULL);
}

class names : public tree
{
public:

	char name[80];

public:

	names(const char *m_name);
	friend int condition(void *n1, void *n2);
	friend void print(names *h);
	void read();
};
names::names(const char *m_name) : tree(condition)
{
	strcpy(name, m_name);
}

void names::read()
{
	cout << "Enter name" << endl;
	cin >> name;
}
int condition(void *n1, void *n2)
{
	names *l_n1, *l_n2;
	l_n1 = (names *)n1;
	l_n2 = (names *)n2;
	return (strcmp(l_n1->name, l_n2->name));
}

void print(names *h)
{
	int i;

	cout << h->name << endl;
	for (i = 0; i < h->count; i++)
		print((names *)h->t[i]);
}

names h("ROOT"), *p, *s;

void main()
{
	int id = 0;

	s = &h;
	p = new names("");
	p->read();
	while (strcmp(p->name, "quit")) {
		p->addtree(s);
		p = new names("Stam");
		p->read();
		s = new names("Stam");
		cout << "Search what?" << endl;
		s->read();
		s = (names *)s->search(&h);
	}
	print(&h);
}

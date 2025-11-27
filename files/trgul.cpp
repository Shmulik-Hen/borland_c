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

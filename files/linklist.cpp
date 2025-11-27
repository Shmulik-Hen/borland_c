#include <fstream.h>

class linklist
{
private:

	linklist *next;
	linklist *prev;

public:

	linklist();
	~linklist();
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

linklist::~linklist()
{
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

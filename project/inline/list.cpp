#ifndef _LIST_CPP
#define _LIST_CPP
#include "list.h"
#include "utils.h"
#include <stddef.h>

template <class T> list<T>::~list()
{
	link *temp;
	while (head) {
		temp = head;
		head = head->next;
		if (temp->item)
			delete temp->item;
		delete temp;
	}
}

template <class T> inline void list<T>::insert(T *newitem)
{
	link *temp = new link;
	if (!temp)
		error("not enough memory in list::insert()");
	temp->item = newitem;
	temp->next = NULL;
	if (!head)
		head = temp;
	else {
		temp->next = head;
		head = temp;
	}
}

template <class T> inline T *list<T>::first()
{
	current = head;
	if (current)
		return current->item;
	else
		return NULL;
}

template <class T> inline T *list<T>::next()
{
	current = current->next;
	if (current)
		return current->item;
	else
		return NULL;
}

template <class T> T *list<T>::search(int (*comp)(const void *))
{
	link *temp = head;
	while (temp) {
		if (comp(temp->item))
			return temp->item;
		temp = temp->next;
	}
	return NULL;
}
#endif

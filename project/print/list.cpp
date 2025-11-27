/**************************************************************************
 * SUBJECT:    FLIGHT SIMULATOR.                                           *
 *                                                                         *
 * TITLE:      GRADUATION PROJECT.                                         *
 *                                                                         *
 * FILE NAME:  list.cpp                                                    *
 *                                                                         *
 * PURPOSE:    function definitions for template class LIST.               *
 **************************************************************************/

#ifndef _LIST_CPP
#define _LIST_CPP
#include "list.h"
#include "utils.h"
#include <stddef.h>

/* constructor */

template <class T> list<T>::list()
{
	current = head = NULL;
}

/* destructor */

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

/* function for adding a new item to head of list */

template <class T> void list<T>::insert(T *newitem)
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

/* function for returning the first item on the list */

template <class T> T *list<T>::first()
{
	current = head;
	if (current)
		return current->item;
	else
		return NULL;
}

/* function for returning the current item */

template <class T> T *list<T>::next()
{
	current = current->next;
	if (current)
		return current->item;
	else
		return NULL;
}

/* function for finding an item in the list */

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

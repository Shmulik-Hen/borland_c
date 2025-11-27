#include <btree.h>
#include <stdio.h>
#include <math.h>

char btree::LR = ' ';

btree::btree()
{
	count = 0;
	dir = ' ';
	this->right = NULL;
	this->left = NULL;
}

btree *btree::add(btree *bt)
{
	if (bt == NULL) {
		bt = this;
		bt->dir = LR;
	}
	else if (cond(this, bt) == 0)
		bt->count++;
	else if (cond(this, bt) < 0) {
		LR = 'L';
		bt->left = add(bt->left);
	}
	else if (cond(this, bt) > 0) {
		LR = 'R';
		bt->right = add(bt->right);
	}
	return (bt);
}

void btree::pre_order()
{
	if (this != NULL) {
		print();
		left->pre_order();
		right->pre_order();
	}
}

void btree::in_order()
{
	if (this != NULL) {
		left->in_order();
		print();
		right->in_order();
	}
}

void btree::post_order()
{
	if (this != NULL) {
		left->post_order();
		right->post_order();
		print();
	}
}

int btree::deep()
{
	if (this == NULL)
		return 0;
	else if (left->deep() > right->deep())
		return (1 + left->deep());
	else
		return (1 + right->deep());
}

btree *btree::search(btree *bt)
{
	if (this != NULL) {
		if (cond(this, bt) == 0)
			return bt;
		else if (cond(this, bt) < 0)
			return (right->search(bt));
		else if (cond(this, bt) > 0)
			return (left->search(bt));
	}
	return this;
}

#include <string.h>
#include <mylib.h>

extern record *ptr[NUM];
extern int maxnum;

void rec_qsort(void *v[], int left, int right, int (*comp)(void *, void *))
{
	int i, last;

	if (left >= right)
		return;
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	rec_qsort(v, left, last - 1, comp);
	rec_qsort(v, last + 1, right, comp);
}

int sort_cmp1(record *p1, record *p2)
{
	return (strcmp(p1->name, p2->name));
}

int sort_cmp2(record *p1, record *p2)
{
	return (strcmp(p1->lastname, p2->lastname));
}

int sort_cmp3(record *p1, record *p2)
{
	return (numcmp(p1->age, p2->age));
}

int sort_cmp4(record *p1, record *p2)
{
	return (numcmp(p1->id, p2->id));
}

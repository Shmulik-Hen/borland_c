#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#define MAXRECS 5

typedef struct std
{
	char name[20];
	long id;
	int age;
	std *next_name;
	std *next_id;
	std *next_age;
} student;

student *sort_by_name();
student *sort_by_id();
student *sort_by_age();
void print_by_name();
void print_by_id();
void print_by_age();
void fill();

student *head_name, *head_id, *head_age;

void main()
{
	clrscr();
	fill();
	head_name = sort_by_name();
	head_id = sort_by_id();
	head_age = sort_by_age();
	print_by_name();
	print_by_id();
	print_by_age();
}

void fill()
{
	int i;
	student *t, *s;
	s = head_name = head_id = head_age = NULL;

	for (i = 0; i < MAXRECS; i++) {
		if ((t = (student *)malloc(sizeof(student))) == NULL) {
			cout << "no memory\n";
			exit(1);
		}
		cin >> t->name;
		cin >> t->id;
		cin >> t->age;
		t->next_name = NULL;
		t->next_id = NULL;
		t->next_age = NULL;
		if (s == NULL)
			s = head_name = head_id = head_age = t;
		else {
			s->next_name = t;
			s->next_age = t;
			s->next_id = t;
			s = s->next_name;
		}
	}
}

void print_by_name()
{
	student *t;
	t = head_name;

	while (t != NULL) {
		cout << "name: " << t->name << " id: " << t->id << " age: " << t->age << endl;
		t = t->next_name;
	}
	cout << endl;
}

void print_by_id()
{
	student *t;
	t = head_id;

	while (t != NULL) {
		cout << "name: " << t->name << " id: " << t->id << " age: " << t->age << endl;
		t = t->next_id;
	}
	cout << endl;
}

void print_by_age()
{
	student *t;
	t = head_age;

	while (t != NULL) {
		cout << "name: " << t->name << " id: " << t->id << " age: " << t->age << endl;
		t = t->next_age;
	}
	cout << endl;
}

student *sort_by_name()
{
	student *temp, *smallest, *one_back, *newlist, *last;
	newlist = NULL;
	last = newlist;

	while (head_name->next_name != NULL) {
		temp = smallest = one_back = head_name;
		while (temp->next_name != NULL) {
			temp = temp->next_name;
			if (strcmp(temp->name, smallest->name) < 0)
				smallest = temp;
		}

		if (smallest == head_name)
			head_name = head_name->next_name;
		else {
			while (one_back->next_name != smallest)
				one_back = one_back->next_name;
			one_back->next_name = smallest->next_name;
		}

		smallest->next_name = NULL;
		if (newlist == NULL)
			last = newlist = smallest;
		else {
			last->next_name = smallest;
			last = last->next_name;
		}
	}
	last->next_name = head_name;
	return newlist;
}

student *sort_by_id()
{
	student *temp, *smallest, *one_back, *newlist, *last;
	newlist = NULL;
	last = newlist;

	while (head_id->next_id != NULL) {
		temp = smallest = one_back = head_id;
		while (temp->next_id != NULL) {
			temp = temp->next_id;
			if (temp->id < smallest->id)
				smallest = temp;
		}

		if (smallest == head_id)
			head_id = head_id->next_id;
		else {
			while (one_back->next_id != smallest)
				one_back = one_back->next_id;
			one_back->next_id = smallest->next_id;
		}

		smallest->next_id = NULL;
		if (newlist == NULL)
			last = newlist = smallest;
		else {
			last->next_id = smallest;
			last = last->next_id;
		}
	}
	last->next_id = head_id;
	return newlist;
}

student *sort_by_age()
{
	student *temp, *smallest, *one_back, *newlist, *last;
	newlist = NULL;
	last = newlist;

	while (head_age->next_age != NULL) {
		temp = smallest = one_back = head_age;
		while (temp->next_age != NULL) {
			temp = temp->next_age;
			if (temp->age < smallest->age)
				smallest = temp;
		}

		if (smallest == head_age)
			head_age = head_age->next_age;
		else {
			while (one_back->next_age != smallest)
				one_back = one_back->next_age;
			one_back->next_age = smallest->next_age;
		}

		smallest->next_age = NULL;
		if (newlist == NULL)
			last = newlist = smallest;
		else {
			last->next_age = smallest;
			last = last->next_age;
		}
	}
	last->next_age = head_age;
	return newlist;
}

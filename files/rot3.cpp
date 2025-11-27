#include <iostream.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#define MAXRECS 5

typedef struct std
{
	char name[20];
	long id;
	int age;
	int index;
	std *next_name;
	std *next_id;
	std *next_age;
} student;

void sort_by_name();
void sort_by_id();
void sort_by_age();
void print();
void make_file();
student *read_file();

FILE *fp, *f_name, *f_id, *f_age;
student *head_name, *head_id, *head_age;
char filename[] = {"rot3.dat"};

void main()
{
	clrscr();
	make_file();
	read_file();
	sort_by_name();
	sort_by_id();
	sort_by_age();
	print();
}

void make_file()
{
	int i;
	student s;

	if ((fp = fopen(filename, "wb")) == NULL) {
		cout << filename << ": file error";
		exit(1);
	}

	for (i = 0; i < MAXRECS; i++) {
		cin >> s.name;
		cin >> s.id;
		cin >> s.age;
		s.index = i;
		s.next_name = NULL;
		s.next_id = NULL;
		s.next_age = NULL;
		fwrite(&s, sizeof(student), 1, fp);
	}

	fclose(fp);
}

student *read_file()
{
	int i;
	student *t, *s, temp;
	s = head_name = head_id = head_age = NULL;

	if ((fp = fopen(filename, "rb")) == NULL) {
		cout << filename << ": file not found\n";
		exit(1);
	}

	while (fread(&temp, sizeof(student), 1, fp)) {
		if ((t = (student *)malloc(sizeof(student))) == NULL) {
			cout << "no memory\n";
			exit(1);
		}

		strcpy(t->name, temp.name);
		t->id = temp.id;
		t->age = temp.age;
		t->index = temp.index;
		t->next_name = temp.next_name;
		t->next_id = temp.next_id;
		t->next_age = temp.next_age;
		if (s == NULL)
			s = head_name = head_id = head_age = t;
		else {
			s->next_name = t;
			s->next_age = t;
			s->next_id = t;
			s = s->next_name;
		}
	}
	fclose(fp);
	return head_id;
}

void print()
{
	int i, step;
	student *t, *h;
	h = read_file();

	if ((fp = fopen("sid.dat", "rb")) == NULL) {
		cout << "file not found";
		exit(1);
	}

	step = sizeof(int) * -1;
	fseek(fp, 0, SEEK_END);

	while (ftell(fp) > 0) {
		fseek(fp, step, SEEK_CUR);
		fread(&i, sizeof(i), 1, fp);
		fseek(fp, step, SEEK_CUR);
		t = h;
		while ((t->index != i) && (t != NULL))
			t = t->next_id;
		cout << "name: " << t->name << " id: " << t->id << " age: " << t->age << endl;
	}
	cout << endl;
	fclose(fp);
}

void sort_by_name()
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

	if ((f_name = fopen("sname.dat", "wb")) == NULL) {
		cout << "file error";
		exit(1);
	}
	temp = newlist;
	while (temp != NULL) {
		fwrite(&temp->index, sizeof(temp->index), 1, f_name);
		temp = temp->next_name;
	}
	fclose(f_name);
}

void sort_by_id()
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

	if ((f_id = fopen("sid.dat", "wb")) == NULL) {
		cout << "file error";
		exit(1);
	}
	temp = newlist;
	while (temp != NULL) {
		fwrite(&temp->index, sizeof(temp->index), 1, f_name);
		temp = temp->next_id;
	}
	fclose(f_id);
}

void sort_by_age()
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

	if ((f_age = fopen("sage.dat", "wb")) == NULL) {
		cout << "file error";
		exit(1);
	}
	temp = newlist;
	while (temp != NULL) {
		fwrite(&temp->index, sizeof(temp->index), 1, f_name);
		temp = temp->next_age;
	}
	fclose(f_age);
}

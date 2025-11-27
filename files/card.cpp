#include <string.h>
#include "c:\bc\prj\linklist.cpp"

class card : public linklist
{
public:

	char *prj;
	char *crd;
	char *name;
	char *month;
	char *shift;
	char *day;
	char *serno;
	char *stage;
	char *test;
	char *failure;
	char *cause;
	char *location;
	char *description;
	char *mandt;
	char *catno;
	char *rem;

public:

	card();
	~card();
	void read();
	void print();
	friend fstream &operator>>(fstream &fin, card &c);
	friend fstream &operator<<(fstream &fout, card &c);
	friend char *strip(char *s);
};

card::card()
{
}

card::~card()
{
	delete prj;
	delete crd;
	delete name;
	delete month;
	delete shift;
	delete day;
	delete serno;
	delete stage;
	delete test;
	delete failure;
	delete cause;
	delete location;
	delete description;
	delete mandt;
	delete catno;
	delete rem;
	this->remove();
}

void card::read()
{
}

void card::print()
{
}

fstream &operator>>(fstream &fin, card &c)
{
	char *str;
	int i = 0;

	str = new char[200];
	do {
		fin.read(&str[i], 1);
	} while (str[i++] != '\n');
	str[i - 1] = NULL;

	c.prj = strip(str);
	c.crd = strip(NULL);
	c.name = strip(NULL);
	c.month = strip(NULL);
	c.shift = strip(NULL);
	c.day = strip(NULL);
	c.serno = strip(NULL);
	c.stage = strip(NULL);
	c.test = strip(NULL);
	c.failure = strip(NULL);
	c.cause = strip(NULL);
	c.location = strip(NULL);
	c.description = strip(NULL);
	c.mandt = strip(NULL);
	c.catno = strip(NULL);
	c.rem = strip(NULL);

	delete str;
	return (fin);
}

fstream &operator<<(fstream &fout, card &c)
{
	fout << '\"' << c.prj << "\",\"" << c.crd << "\",\"" << c.name << "\",\"" << c.month << "\",\"" << c.shift << "\",\""
	     << c.day << "\",\"" << c.serno << "\",\"" << c.stage << "\",\"" << c.test << "\",\"" << c.failure << "\",\"" << c.cause
	     << "\",\"" << c.location << "\",\"" << c.description << "\",\"" << c.mandt << "\",\"" << c.catno << "\",\"" << c.rem
	     << "\"" << endl;
	return (fout);
}

char *strip(char *s)
{
	char *tmp, *p;

	tmp = strtok(s, ",");
	p = tmp;
	while (*p) {
		if (*p == '\"')
			strcpy(p, p + 1);
		else
			p++;
	}

	p = tmp;
	while (*p == ' ')
		strcpy(p, p + 1);

	p = new char[1 + strlen(tmp)];
	strcpy(p, tmp);
	return p;
}

linklist head;
card *my;

void main()
{
	char file1[50] = "c:\\report\\sumall.dat";
	char file2[50] = "c:\\report\\sumall.da";
	char *str;
	fstream f1, f2;
	card *last;
	int found;

	f1.open(file1, ios::in | ios::out | ios::nocreate);
	if (!f1)
		cout << "could not open file";
	last = (card *)&head;
	while (!f1.eof()) {
		my = new card;
		f1 >> *my;
		my->append(last);
		last = my;
	}
	f1.close();
	delete last;

	f2.open(file2, ios::out);
	if (!f2)
		cout << "could not open file";
	my = (card *)&head;
	while (my->r_next() != NULL) {
		my = (card *)my->r_next();
		f2 << *my;
	}
	f2.close();

	/*
	 //DELETE
	my=(card*)&head;
	while(my->r_next() != NULL)
	     {
	      my=(card*)&head;
	      my=(card*)my->r_next();
	      delete my;
	     }

	cout<<"enter location:";
	cin>>str;

	found=0;
	my=(card*)&head;
	while(my->r_next() != NULL)
	     {
	      my=(card*)my->r_next();
	      if(!strcmp(my->location,str))
		{
		 my->print();
		 found=1;
		}
	     }
	if(!found)
	   cout << "no such component" << endl;

	my=(card*)&head;
	while(my->r_next() != NULL)
	     {
	      my=(card*)my->r_next();
	      my->print();
	      getchar();
	     }
	*/
}

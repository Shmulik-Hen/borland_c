#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <mylib.h>

extern record *ptr[NUM];
extern FILE *fp;
extern char *filename;
extern int maxnum;

void get_dtls(void)
{
	int i = 0;
	char *str;

	clear();
	clrscr();
	while (1) {
		ptr[i] = (record *)malloc(sizeof(record));
		gets(str);
		if (sscanf(str, "%s %s %s %s", ptr[i]->name, ptr[i]->lastname, ptr[i]->age, ptr[i]->id) == -1) {
			ptr[i] = NULL;
			i--;
			break;
		}
		i++;
	}
	maxnum = i;
}

void dspl_rcd(void)
{
	int i;

	clrscr();
	for (i = 0; i <= maxnum; i++)
		printf("%s\t\t%s\t\t%3s\t%10s\n", ptr[i]->name, ptr[i]->lastname, ptr[i]->age, ptr[i]->id);
}

void save_rcd(void)
{
	int i;

	clrscr();
	puts("input file name:");
	gotoxy(17, 1);
	gets(filename);
	fp = fopen(filename, "w");
	for (i = 0; i <= maxnum; i++)
		fprintf(fp, "%s %s %s %s\n", ptr[i]->name, ptr[i]->lastname, ptr[i]->age, ptr[i]->id);
	fclose(fp);
}

void rd_file(void)
{
	int i = 0;

	clrscr();
	puts("input file name:");
	gotoxy(17, 1);
	gets(filename);
	fp = fopen(filename, "r");
	clear();
	while (1) {
		ptr[i] = (record *)malloc(sizeof(record));
		if (fscanf(fp, "%s %s %s %s", ptr[i]->name, ptr[i]->lastname, ptr[i]->age, ptr[i]->id) == EOF) {
			ptr[i] = NULL;
			i--;
			break;
		}
		i++;
	}
	maxnum = i;
	fclose(fp);
}

void prnt_rcd(void)
{
	int i;

	for (i = 0; i <= maxnum; i++)
		fprintf(stdprn, "%s %s %s %s\n", ptr[i]->name, ptr[i]->lastname, ptr[i]->age, ptr[i]->id);
}

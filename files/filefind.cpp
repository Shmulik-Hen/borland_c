#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <dir.h>
#include <dos.h>
#include <string.h>
#define MAX 512

void main()
{
	struct ffblk ffblk;
	char match[] = "*.h";
	char *str[MAX];
	int count = 0, i;
	long size = 0;

	clrscr();
	printf("Directory listing of %s\n", match);
	if (findfirst(match, &ffblk, FA_NORMAL)) {
		printf("No matches found: %s\n", match);
		exit(1);
	}
	do {
		// printf("%s\n", ffblk.ff_name);
		if (count > MAX) {
			printf("too many files");
			exit(1);
		}
		if ((str[count] = (char *)malloc(strlen(ffblk.ff_name) + 1)) == NULL) {
			printf("not enough memory");
			exit(1);
		}
		strcpy(str[count++], ffblk.ff_name);
		size += ffblk.ff_fsize;
	} while (!findnext(&ffblk));
	for (i = 0; i < count; i++) {
		printf("%s\n", str[i]);
		free(str[i]);
	}
	printf("      %d file(s)     %ld bytes\n", count, size);
}

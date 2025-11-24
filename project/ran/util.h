/****************************************************************************
*                                                                           *
* SUBJECT:	Computer Graphics .                                         *
* --------                                                                  *
*                                                                           *
* TITLE:        General Utilities. (header)                                 *
* ------                                                                    *
*                                                                           *
* FILE:		util.h                                                      *
* -----                                                                     *
*                                                                           *
* WRITTEN BY:	Iron Ran	023914260	"iron"                      *
* -----------	Sholkis Moshe   059764993	"shool"                     *
*                                                                           *
****************************************************************************/


char upcase(char c);

#define UPCASE 1
#define NORMAL 0

int read_word(char *word,int max_len,FILE *f,int up);
int str_to_int(char *word);

#define pop(x)		asm pop x
#define push(x)		asm push x
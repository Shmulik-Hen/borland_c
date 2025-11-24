/****************************************************************************
*                                                                           *
* SUBJECT:	Computer Graphics .                                         *
* --------                                                                  *
*                                                                           *
* TITLE:        General Utilities.                                          *
* ------                                                                    *
*                                                                           *
* FILE:		util.c                                                      *
* -----                                                                     *
*                                                                           *
* WRITTEN BY:	Iron Ran	023914260	"iron"                      *
* -----------	Sholkis Moshe   059764993	"shool"                     *
*                                                                           *
* UPDATES:	First Writing	26/11/94                                    *
* --------      Modify #1	26/12/94                                    *
*                                                                           *
*****************************************************************************
*                                                                           *
* DESCRIPTION:	This file containes general utilities.                      *
* ------------	- memory allocation.                                        *
*		- charcter manipulation.                                    *
*                                       	                            *
****************************************************************************/

#include <stdio.h>
#include "types.def"
#include "util.h"

/****************************************************************************
*                                                                           *
* Procedure: 	upcase.                                                     *
* ----------                                                                *
* Inputs:	c      - character to upcase.                               *
* -------                                                                   *
* Outputs:	return - upper case character version of c.                 *
* --------                                                                  *
* Description:	convert charcters 'a..z' to 'A..Z'.                         *
* ------------                                                              *
****************************************************************************/


char upcase(char c)
{
 if ((c<='z') && (c>='a')) return(c & 0xdf);
 return(c);
}


/****************************************************************************
*                                                                           *
* Procedure:	read word.                                                  *
* ----------                                                                *
* Inputs:       word	- pointer to string array.                          *
* -------	max_len - maximum length of word.                           *
*		f	- file pointer.                                     *
*               up      - 0 for normal reading else convert to uppercase    *
*                                                                           *
* Outputs:	word	- points to a word.                                 *
* --------	return	- length of word.                                   *
*                                                                           *
* Description:	read word from file - until delimiter is reached.           *
* ------------                                                              *
****************************************************************************/

int read_word(char *word,int max_len,FILE *f,int up)
{
int finish=0;
int length=0;
char c;

 while((!finish) && (!feof(f)) && (length<max_len))
 {
  c=fgetc(f);
  if (up) c=upcase(c);
  if ((c<=32)||(c==',')||(c=='(')||(c==')')||(c=='{')||(c=='}'))
					/* delimiter list */
   finish=length;
  else
   word[length++]=(c=='~' ? ' ' : c);	/* convert '~' to space */
 }
 word[length]='\0';
 return(length);
}

/****************************************************************************
*                                                                           *
* Procedure:	str_to_int.
* ----------                                                                *
* Inputs:       word	- string.
* -------
*                                                                           *
* Outputs:	return	- integer.
* --------
* Description:	convert string to integer.
* ------------                                                              *
****************************************************************************/

int str_to_int(char *word)
{
int temp=0;
int sign=1;
int radix=10;
int index=0;

 switch(upcase(word[index]))
  {
   case '-':	sign=-1;
   case '+':	index++;
		break;
  }

 switch(upcase(word[index]))
  {
   case 'B':	radix=2;
		index++;
		break;

   case 'X':
   case 'H':	radix=16;
		index++;
		break;
  }


 while(word[index])
 {
  if (word[index]<='9')
    temp=temp*radix+sign*(int)(word[index]-'0');
  else
    temp=temp*radix+sign*(int)(upcase(word[index])-'A'+10);
  index++;
 }
 return(temp);

}


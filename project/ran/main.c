/****************************************************************************
*                                                                           *
* SUBJECT:	Computer Graphics .                                         *
* --------                                                                  *
*                                                                           *
* TITLE:        Main Program.                                               *
* ------                                                                    *
*                                                                           *
* FILE:		main.c                                                      *
* -----                                                                     *
*                                                                           *
* WRITTEN BY:	Iron Ran	023914260	"iron"                      *
* -----------	Sholkis Moshe   059764993	"shool"                     *
*                                                                           *
* UPDATES:	First Writing	18/11/94                                    *
* --------      Modify #1	27/12/94                                    *
*                                                                           *
*****************************************************************************
*                                                                           *
* DESCRIPTION: This the main procedure, the main gets an input file from    *
* ------------ the command line arguments & execute the film interpreter.   *
*                                                                           *
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>
#include <math.h>
#include "types.def"
#include "intrprt2.h"
#include "3d_util.h"

void main(argc,argv)
int argc;
char *argv[];
{
FILE *f;

/*	-- use in command line arguments -- */

 if (argc<2)
  {
   printf("no input file");
   exit;
  }

 if((f=fopen(argv[1],"rb"))==NULL) printf("no such file\n");
 else

/*
 if((f=fopen("road.dat","rb"))==NULL) printf("no input file\n");
 else*/

  {
   opengraph();
   read_file(f);
   fclose(f);

   run_film();

//   closegraph();
  }
}
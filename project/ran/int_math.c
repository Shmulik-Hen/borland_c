/****************************************************************************
*                                                                           *
* SUBJECT:	Computer Graphics .                                         *
* --------                                                                  *
*                                                                           *
* TITLE:        Integer-Math Utility.                                       *
* ------                                                                    *
*                                                                           *
* FILE:		int_math.c                                                  *
* -----                                                                     *
*                                                                           *
* WRITTEN BY:	Iron Ran	023914260	"iron"                      *
* -----------	Sholkis Moshe   059764993	"shool"                     *
*                                                                           *
* UPDATES:	First Writing	18/11/94                                    *
* --------	Modify #1	14/12/94	addtion of "ATTRIB"         *
*               Modify #2	26/12/94        new "mul" macro.            *
*		Modify #3	20/01/95	addition of "fruc_sqrt"	    *
*	                                                             	    *
*****************************************************************************
*                                                                           *
* DESCRIPTION:  The integer math utility uses numbers modulo 1024 to        *
* ------------	simulate fructions. (i.e. 0 - 1 eqv 0 - 1024).              *
*		1024 was chosen for faster modulo with "shifts" insted of   *
*		regular division.                                           *
*                                                                           *
*		Insted of regular F.P. trigonometric function, we used      *
*		constant array of 512 steps (512 "degrees").                *
*		expiriance showed us it's about 4 times faster than F.P.    *
*		computitions.                                               *
*                                                                           *
*		The lose of accuracy due to integer computition is minimal. *
*                                                                           *
****************************************************************************/


#include <stdio.h>
#include "types.def"
#include "int_math.h"

MATRIX IDENT_MATRIX={	{IDENT	,0	,0	,0	},
			{0	,IDENT	,0	,0	},
			{0	,0	,IDENT	,0	},
			{0	,0	,0	,IDENT	}	};


/****************************************************************************
*                                                                           *
* sine & cosine constants (modulo 1024). 				    *
* this values where computed from float function on 512 values & where	    *
* multiplyed by 1024 to create modulo 1024 values.                          *
* sin & cos uses the same array with 128 "degree" offset (eqv. 90 degrees). *
*                                                                           *
****************************************************************************/


FRUC SIN[]={     0,   12,   25,   37,   50,   62,   75,   87,
	       100,  112,  125,  137,  150,  162,  175,  187,
	       199,  212,  224,  236,  248,  260,  273,  285,
	       297,  309,  321,  333,  344,  356,  368,  380,
	       391,  403,  414,  426,  437,  449,  460,  471,
	       482,  493,  504,  515,  526,  537,  547,  558,
	       568,  579,  589,  599,  609,  620,  629,  639,
	       649,  659,  668,  678,  687,  696,  706,  715,
	       724,  732,  741,  750,  758,  767,  775,  783,
	       791,  799,  807,  814,  822,  829,  837,  844,
	       851,  858,  865,  871,  878,  884,  890,  897,
	       903,  908,  914,  920,  925,  930,  936,  941,
	       946,  950,  955,  959,  964,  968,  972,  976,
	       979,  983,  986,  990,  993,  996,  999, 1001,
	      1004, 1006, 1008, 1010, 1012, 1014, 1016, 1017,
	      1019, 1020, 1021, 1022, 1022, 1023, 1023, 1023,
	      1024, 1023, 1023, 1023, 1022, 1022, 1021, 1020,
	      1019, 1017, 1016, 1014, 1012, 1010, 1008, 1006,
	      1004, 1001,  999,  996,  993,  990,  986,  983,
	       979,  976,  972,  968,  964,  959,  955,  950,
	       946,  941,  936,  930,  925,  920,  914,  908,
	       903,  897,  890,  884,  878,  871,  865,  858,
	       851,  844,  837,  829,  822,  814,  807,  799,
	       791,  783,  775,  767,  758,  750,  741,  732,
	       724,  715,  706,  696,  687,  678,  668,  659,
	       649,  639,  630,  620,  610,  599,  589,  579,
	       568,  558,  547,  537,  526,  515,  504,  493,
	       482,  471,  460,  449,  437,  426,  414,  403,
	       391,  380,  368,  356,  344,  333,  321,  309,
	       297,  285,  273,  260,  248,  236,  224,  212,
	       199,  187,  175,  162,  150,  137,  125,  112,
	       100,   87,   75,   62,   50,   37,   25,   12,
		 0,  -12,  -25,  -37,  -50,  -62,  -75,  -87,
	      -100, -112, -125, -137, -150, -162, -175, -187,
	      -199, -212, -224, -236, -248, -260, -273, -285,
	      -297, -309, -321, -333, -344, -356, -368, -380,
	      -391, -403, -414, -426, -437, -449, -460, -471,
	      -482, -493, -504, -515, -526, -537, -547, -558,
	      -568, -579, -589, -599, -609, -620, -629, -639,
	      -649, -659, -668, -678, -687, -696, -706, -715,
	      -724, -732, -741, -750, -758, -767, -775, -783,
	      -791, -799, -807, -814, -822, -829, -837, -844,
	      -851, -858, -865, -871, -878, -884, -890, -897,
	      -903, -908, -914, -920, -925, -930, -936, -941,
	      -946, -950, -955, -959, -964, -968, -972, -976,
	      -979, -983, -986, -990, -993, -996, -999,-1001,
	     -1004,-1006,-1008,-1010,-1012,-1014,-1016,-1017,
	     -1019,-1020,-1021,-1022,-1022,-1023,-1023,-1023,
	     -1024,-1023,-1023,-1023,-1022,-1022,-1021,-1020,
	     -1019,-1017,-1016,-1014,-1012,-1010,-1008,-1006,
	     -1004,-1001, -999, -996, -993, -990, -986, -983,
	      -979, -976, -972, -968, -964, -959, -955, -950,
	      -946, -941, -936, -930, -925, -920, -914, -908,
	      -903, -897, -890, -884, -878, -871, -865, -858,
	      -851, -844, -837, -829, -822, -814, -807, -799,
	      -791, -783, -775, -767, -758, -750, -741, -732,
	      -724, -715, -706, -696, -687, -678, -668, -659,
	      -649, -639, -630, -620, -610, -599, -589, -579,
	      -568, -558, -547, -537, -526, -515, -504, -493,
	      -482, -471, -460, -449, -437, -426, -414, -403,
	      -391, -380, -368, -356, -344, -333, -321, -309,
	      -297, -285, -273, -261, -248, -236, -224, -212,
	      -199, -187, -175, -162, -150, -137, -125, -112,
	      -100,  -87,  -75,  -62,  -50,  -37,  -25,  -12,
		 0,   12,   25,   37,   50,   62,   75,   87,
	       100,  112,  125,  137,  150,  162,  175,  187,
	       199,  212,  224,  236,  248,  260,  273,  285,
	       297,  309,  321,  333,  344,  356,  368,  380,
	       391,  403,  414,  426,  437,  449,  460,  471,
	       482,  493,  504,  515,  526,  537,  547,  558,
	       568,  579,  589,  599,  609,  620,  629,  639,
	       649,  659,  668,  678,  687,  696,  706,  715,
	       724,  732,  741,  750,  758,  767,  775,  783,
	       791,  799,  807,  814,  822,  829,  837,  844,
	       851,  858,  865,  871,  878,  884,  890,  897,
	       903,  908,  914,  920,  925,  930,  936,  941,
	       946,  950,  955,  959,  964,  968,  972,  976,
	       979,  983,  986,  990,  993,  996,  999, 1001,
	      1004, 1006, 1008, 1010, 1012, 1014, 1016, 1017,
	      1019, 1020, 1021, 1022, 1022, 1023, 1023, 1023};

FRUC *COS=&SIN[128];		/* cos(x) = sin(x+"90")	*/

/****************************************************************************
*                                                                           *
* multiply matrix (a) by matrix (b) and get new matrix (c).                 *
* (function version).                                                       *
****************************************************************************/

void f_mul_matrix_matrix(MATRIX a,MATRIX b,MATRIX c)
{
 mul_matrix_matrix(a,b,c);
}



/****************************************************************************
*                                                                           *
* multiply vector "x" by matrix "m". (function version)                     *
*                                                                           *
****************************************************************************/

void f_mul_matrix_vector(MATRIX m,VECTOR x,VECTOR y)
{
 mul_matrix_vector(m,x,y);
}

/****************************************************************************
*
* product attrib (a) with attrib (b) and get attrib (c).
* (function version).
****************************************************************************/

void f_product_attrib_attrib(ATTRIB a,ATTRIB b,ATTRIB c)
{
 product_attrib_attrib(a,b,c);
}

/****************************************************************************
*                                                                           *
* create general operator matrix i.e: add offset & rotation angle & zoom.   *
* convert general attribute to matrix.                                      *
*                                                                           *
****************************************************************************/

void general_matrix(MATRIX m,ATTRIB a)
{
 m[0][0]=fruc_mul(a.zoom,fruc_mul(cos_(a.deg_z),cos_(a.deg_y)));
 m[0][1]=-fruc_mul(a.zoom,fruc_mul(cos_(a.deg_y),sin_(a.deg_z)));
 m[0][2]=fruc_mul(a.zoom,-sin_(a.deg_y));
 m[0][3]=a.off_x;


 m[1][0]=fruc_mul(a.zoom,fruc_mul(cos_(a.deg_x),sin_(a.deg_z))-
		    fruc_mul(sin_(a.deg_x),fruc_mul(cos_(a.deg_z),sin_(a.deg_y))));
 m[1][1]=fruc_mul(a.zoom,fruc_mul(cos_(a.deg_x),cos_(a.deg_z))+
		    fruc_mul(sin_(a.deg_x),fruc_mul(sin_(a.deg_z),sin_(a.deg_y))));
 m[1][2]=fruc_mul(a.zoom,-fruc_mul(sin_(a.deg_x),cos_(a.deg_y)));
 m[1][3]=a.off_y;

 m[2][0]=fruc_mul(a.zoom,fruc_mul(sin_(a.deg_x),sin_(a.deg_z))+
		    fruc_mul(cos_(a.deg_x),fruc_mul(cos_(a.deg_z),sin_(a.deg_y))));
 m[2][1]=fruc_mul(a.zoom,fruc_mul(sin_(a.deg_x),cos_(a.deg_z))-
		    fruc_mul(sin_(a.deg_z),fruc_mul(cos_(a.deg_x),sin_(a.deg_y))));
 m[2][2]=fruc_mul(a.zoom,fruc_mul(cos_(a.deg_x),cos_(a.deg_y)));
 m[2][3]=a.off_z;

 m[3][0]=0;
 m[3][1]=0;
 m[3][2]=0;
 m[3][3]=IDENT;
}

/****************************************************************************
*                                                                           *
* create rotate operator matrix i.e: only rotation angle    		    *
*                                                                           *
****************************************************************************/

void rotate_matrix(MATRIX m,ATTRIB a)
{
 m[0][0]=fruc_mul(cos_(a.deg_z),cos_(a.deg_y));
 m[0][1]=-fruc_mul(cos_(a.deg_y),sin_(a.deg_z));
 m[0][2]=-sin_(a.deg_y);
 m[0][3]=0;


 m[1][0]=fruc_mul(cos_(a.deg_x),sin_(a.deg_z))-
	 fruc_mul(sin_(a.deg_x),fruc_mul(cos_(a.deg_z),sin_(a.deg_y)));
 m[1][1]=fruc_mul(cos_(a.deg_x),cos_(a.deg_z))+
	 fruc_mul(sin_(a.deg_x),fruc_mul(sin_(a.deg_z),sin_(a.deg_y)));
 m[1][2]=-fruc_mul(sin_(a.deg_x),cos_(a.deg_y));
 m[1][3]=0;

 m[2][0]=fruc_mul(sin_(a.deg_x),sin_(a.deg_z))+
	 fruc_mul(cos_(a.deg_x),fruc_mul(cos_(a.deg_z),sin_(a.deg_y)));
 m[2][1]=fruc_mul(sin_(a.deg_x),cos_(a.deg_z))-
	 fruc_mul(sin_(a.deg_z),fruc_mul(cos_(a.deg_x),sin_(a.deg_y)));
 m[2][2]=fruc_mul(cos_(a.deg_x),cos_(a.deg_y));
 m[2][3]=0;

 m[3][0]=0;
 m[3][1]=0;
 m[3][2]=0;
 m[3][3]=IDENT;
}


/****************************************************************************
*                                                                           *
* Procedure:	str_to_fruc.                                                *
* ----------                                                                *
* Inputs:   	w	- string to convert.                                *
* -------                                                                   *
* Outputs:	return	- fruction number of w.                             *
* --------                                                                  *
* Description:	convert string to fruction. (string can be rational).       *
* ------------                                                              *
****************************************************************************/

FRUC str_to_fruc(char *w)
{
FRUC temp=0;
FRUC sign=1;
int index=0;
FRUC fruc=0;

 while(w[index])
 {
  switch(w[index])
  {
   case '-':	sign=-1;
   case '+':	break;

   case	'.':	fruc=1;
		break;

   default:	temp=temp*10+(FRUC)(w[index]-'0');
		fruc=fruc*10;
		break;
  }
  index++;
 }
 if(!fruc) fruc=1;
 return(inv_adj(sign*temp)/fruc);
}


/****************************************************************************
*                                                                           *
* Procedure:	fruc_sqrt.                                                  *
* ----------                                                                *
* Inputs:   	x	- positive fruction.                                *
* -------                                                                   *
* Outputs:	return	- square root (in FRUCtions) of x.                  *
* --------                                                                  *
* Description:	find the square root of a number using intger calculations  *
* ------------	only. the function is uses a guess of half of the bits of   *
*		the number x (the high half). then using iterative function *
*		(with only 4 iterations) computes root=((x/root)+root)/2    *
*                                                                           *
****************************************************************************/


FRUC fruc_sqrt(FRUC x)
{
FRUC y=0xfffff800;	/* bit mask */
FRUC temp,root;
int iter=5;		/* number of iterations */

 if (x==0) return 0;

 temp=x+x>>1;
 root=x;
 while (temp & y)
  {
   root=root>>1;
   temp=temp>>1;
   y=y<<1;
  }

 for (;iter;iter--) root=fruc_div((x>>1),root)+(root>>1);

 return(root);
}



/****************************************************************************
*                                                                           *
* Procedure:	normal_vector.                                              *
* ----------                                                                *
* Inputs:   	x	- vector to normalize.                              *
* -------                                                                   *
* Outputs:	y	- normalized vector.                                *
* --------                                                                  *
* Description:	find the norm of the vector x & divide by it.               *
* ------------                                                              *
****************************************************************************/

void normal_vector(VECTOR x,VECTOR y)
{
FRUC norm;

 norm=fruc_sqrt(mul_vector_vector(x,x));
 y[X_]=fruc_div(x[X_],norm);
 y[Y_]=fruc_div(x[Y_],norm);
 y[Z_]=fruc_div(x[Z_],norm);
}
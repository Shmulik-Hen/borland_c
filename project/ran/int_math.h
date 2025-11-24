/****************************************************************************
*                                                                           *
* SUBJECT:	Computer Graphics .                                         *
* --------                                                                  *
*                                                                           *
* TITLE:        Integer-Math Utility (header).                              *
* ------                                                                    *
*                                                                           *
* FILE:		int_math.h                                                  *
* -----                                                                     *
*                                                                           *
* WRITTEN BY:	Iron Ran	023914260	"iron"                      *
* -----------	Sholkis Moshe   059764993	"shool"                     *
*                                                                           *
****************************************************************************/

#ifndef	__INT_MATH_H
#define	__INT_MATH_H

extern FRUC SIN[];
extern FRUC *COS;

/****************************************************************************
*                                                                           *
* modulo 512 degrees .                                                      *
*                                                                           *
* MASK_511	- the number 511                                            *
* mask(x)	- x modulo 512                                              *
*                                                                           *
****************************************************************************/


#define		MASK_511	0x01ff
#define		mask(x)		((x) & MASK_511)
#define	cos_(x)	COS[mask(x)]	/* 0-511 degrees */
#define	sin_(x)	SIN[mask(x)]	/* 0-511 degrees */


/****************************************************************************
*                                                                           *
* modulo 1024 compensation.                                                 *
*                                                                           *
* IDENT		- "1" in fruction notation 	i.e: 1*1024                 *
* HALF		- "1/2" in fruction notation 	i.e: (1/2)*1024             *
* adj(x) 	- convert fruction to integer 	i.e: x/1024                 *
* semi_adj(x)	- devide fruction by 32 	i.e: x/û1024                *
* pre_adj(x)	- devide fruction by 2 		i.e: x/2                    *
* post_adj(x)	- devide fruction by 256 	i.e: x/256                  *
* inv_adj(x)	- convert integer to fruction 	i.e: x*1024                 *
* fruc_mul(x,y)	- multiply two fruction & get new normalized fruction       *
* fruc_div(x,y)	- divide two fruction & get new normalized fruction         *
*                                                                           *
****************************************************************************/

#define		IDENT		1024
#define		HALF		512

#define		adj(x)		((x)>>10)
#define 	semi_adj(x)	((x)>>5)
#define 	pre_adj(x)	((x)>>1)
#define 	post_adj(x)	((x)>>8)
#define		inv_adj(x)	((x)<<10)
#define		fruc_mul(x,y)	(post_adj(pre_adj(x)*pre_adj(y)))
#define		fruc_div(x,y)	(inv_adj(x)/y)
#define 	sign(x)		(!(x) ? 0 : (((x)>0) ? 1 : -1))
#define		max(x,y)	(((x)>(y)) ? (x) : (y) )
#define		min(x,y)	(((x)<(y)) ? (x) : (y) )



//#define	fruc_mul(x,y)	adj(x*y)
//#define	fruc_mul(x,y)	(semi_adj(x)*semi_adj(y))



/****************************************************************************
*                                                                           *
* multiply 2 vectors (x),(y) - scalar multiplication.                       *
*                                                                           *
****************************************************************************/

#define	mul_vector_vector(x,y)	(x[X_]*y[X_]+x[Y_]*y[Y_]+x[Z_]*y[Z_])
//#define	mul_vector_vector(x,y)	(fruc_mul(x[X_],y[X_])+fruc_mul(x[Y_],y[Y_])+fruc_mul(x[Z_],y[Z_]))

/****************************************************************************
*                                                                           *
* add 2 vectors (x),(y)
*                                                                           *
****************************************************************************/

#define	add_vector_vector(x,y,z)	z[X_]=x[X_]+y[X_];\
					z[Y_]=x[Y_]+y[Y_];\
					z[Z_]=x[Z_]+y[Z_]


/****************************************************************************
*                                                                           *
* sub 2 vectors (x),(y)
*                                                                           *
****************************************************************************/

#define	sub_vector_vector(x,y,z)	z[X_]=x[X_]-y[X_];\
					z[Y_]=x[Y_]-y[Y_];\
					z[Z_]=x[Z_]-y[Z_]


/****************************************************************************
*                                                                           *
* operate matrix (m) on vector (x) and get new vector (y).                  *
*                                                                           *
****************************************************************************/

#define	mul_matrix_vector(m,x,y) y[X_]=adj(mul_vector_vector(m[0],x)+m[0][O_]);	\
				 y[Y_]=adj(mul_vector_vector(m[1],x)+m[1][O_]);	\
				 y[Z_]=adj(mul_vector_vector(m[2],x)+m[2][O_])


/****************************************************************************
*                                                                           *
* multiply matrix (a) by matrix (b) and get new matrix (c).                 *
*                                                                           *
****************************************************************************/

#define mul_matrix_matrix(a,b,c) c[0][0]=fruc_mul(a[0][0],b[0][0])+fruc_mul(a[0][1],b[1][0])+fruc_mul(a[0][2],b[2][0])+fruc_mul(a[0][3],b[3][0]);\
				 c[0][1]=fruc_mul(a[0][0],b[0][1])+fruc_mul(a[0][1],b[1][1])+fruc_mul(a[0][2],b[2][1])+fruc_mul(a[0][3],b[3][1]);\
				 c[0][2]=fruc_mul(a[0][0],b[0][2])+fruc_mul(a[0][1],b[1][2])+fruc_mul(a[0][2],b[2][2])+fruc_mul(a[0][3],b[3][2]);\
				 c[0][3]=fruc_mul(a[0][0],b[0][3])+fruc_mul(a[0][1],b[1][3])+fruc_mul(a[0][2],b[2][3])+fruc_mul(a[0][3],b[3][3]);\
				 c[1][0]=fruc_mul(a[1][0],b[0][0])+fruc_mul(a[1][1],b[1][0])+fruc_mul(a[1][2],b[2][0])+fruc_mul(a[1][3],b[3][0]);\
				 c[1][1]=fruc_mul(a[1][0],b[0][1])+fruc_mul(a[1][1],b[1][1])+fruc_mul(a[1][2],b[2][1])+fruc_mul(a[1][3],b[3][1]);\
				 c[1][2]=fruc_mul(a[1][0],b[0][2])+fruc_mul(a[1][1],b[1][2])+fruc_mul(a[1][2],b[2][2])+fruc_mul(a[1][3],b[3][2]);\
				 c[1][3]=fruc_mul(a[1][0],b[0][3])+fruc_mul(a[1][1],b[1][3])+fruc_mul(a[1][2],b[2][3])+fruc_mul(a[1][3],b[3][3]);\
				 c[2][0]=fruc_mul(a[2][0],b[0][0])+fruc_mul(a[2][1],b[1][0])+fruc_mul(a[2][2],b[2][0])+fruc_mul(a[2][3],b[3][0]);\
				 c[2][1]=fruc_mul(a[2][0],b[0][1])+fruc_mul(a[2][1],b[1][1])+fruc_mul(a[2][2],b[2][1])+fruc_mul(a[2][3],b[3][1]);\
				 c[2][2]=fruc_mul(a[2][0],b[0][2])+fruc_mul(a[2][1],b[1][2])+fruc_mul(a[2][2],b[2][2])+fruc_mul(a[2][3],b[3][2]);\
				 c[2][3]=fruc_mul(a[2][0],b[0][3])+fruc_mul(a[2][1],b[1][3])+fruc_mul(a[2][2],b[2][3])+fruc_mul(a[2][3],b[3][3]);\
				 c[3][0]=fruc_mul(a[3][0],b[0][0])+fruc_mul(a[3][1],b[1][0])+fruc_mul(a[3][2],b[2][0])+fruc_mul(a[3][3],b[3][0]);\
				 c[3][1]=fruc_mul(a[3][0],b[0][1])+fruc_mul(a[3][1],b[1][1])+fruc_mul(a[3][2],b[2][1])+fruc_mul(a[3][3],b[3][1]);\
				 c[3][2]=fruc_mul(a[3][0],b[0][2])+fruc_mul(a[3][1],b[1][2])+fruc_mul(a[3][2],b[2][2])+fruc_mul(a[3][3],b[3][2]);\
				 c[3][3]=fruc_mul(a[3][0],b[0][3])+fruc_mul(a[3][1],b[1][3])+fruc_mul(a[3][2],b[2][3])+fruc_mul(a[3][3],b[3][3])



/****************************************************************************
*
* product attrib (a) on attrib (b) and get attrib (c).
*
****************************************************************************/

#define	product_attrib_attrib(a,b,c)	c.deg_x=mask(a.deg_x+b.deg_x);\
					c.deg_y=mask(a.deg_y+b.deg_y);\
					c.deg_z=mask(a.deg_z+b.deg_z);\
					c.off_x=a.off_x+b.off_x;\
					c.off_y=a.off_y+b.off_y;\
					c.off_z=a.off_z+b.off_z;\
					c.zoom =fruc_mul(a.zoom,b.zoom)




void f_mul_matrix_matrix(MATRIX a,MATRIX b,MATRIX c);
void f_mul_matrix_vector(MATRIX m,VECTOR x,VECTOR y);
void f_product_attrib_attrib(ATTRIB a,ATTRIB b,ATTRIB c);
void general_matrix(MATRIX m,ATTRIB a);
void rotate_matrix(MATRIX m,ATTRIB a);
FRUC str_to_fruc(char *w);
FRUC fruc_sqrt(FRUC x);
void normal_vector(VECTOR x,VECTOR y);

#endif
/****************************************************************************
*                                                                           *
* SUBJECT:	Computer Graphics .                                         *
* --------                                                                  *
*                                                                           *
* TITLE:        3D Graphic Utility (Header).                                *       *
* ------                                                                    *
*                                                                           *
* FILE:		3d_util.h                                                   *
* -----                                                                     *
*                                                                           *
* WRITTEN BY:	Iron Ran	023914260	"iron"                      *
* -----------	Sholkis Moshe   059764993	"shool"                     *
*                                                                           *
****************************************************************************/

int opengraph();
int draw_polygon(POLYGON *p,MATRIX m,VECTOR v,int color);
int draw_sons(ELEMENT *p,MATRIX m);
int draw_z_sort(ELEMENT *element);
int draw_z_sort_elem(ELEMENT *element);
int flip_page();
int push_q(POLY_ELEM **queue,POLY_ELEM **element);
int pop_q(POLY_ELEM **queue,POLY_ELEM **element);
int update_tree(ELEMENT *p,MATRIX m,MATRIX rm,POLY_ELEM **queue);
int update_elem(ELEMENT *p,MATRIX m,MATRIX rm,POLY_ELEM **queue);
int my_setviewport(int left,int top,int right,int bottom);
int my_clearviewport();
void my_bar(int x1,int y1,int x2,int y2);
void my_setcolor(int color);
void my_line(int left,int top,int right,int bottom);
void my_outtextxy(int x,int y,char str[]);
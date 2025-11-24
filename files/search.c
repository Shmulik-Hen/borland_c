#include<string.h>
#include<math.h>
#include<mylib.h>

extern record *ptr[NUM];
extern int maxnum;


int rec_bsrch(void *v[],int bottom,int top,char *item
	     ,int (*comp)(void*,void*))
{
int cell;

cell=floor((top+bottom)/2);
if( (top-1 == bottom ) && ( (*comp)(v[cell],item) != 0 ) )
   return -1;
if( (*comp)(v[cell],item) == 0 )
  return cell;
if( (*comp)(v[cell],item) > 0 )
   return(rec_bsrch(v,bottom,cell,item,comp));
if( (*comp)(v[cell],item) < 0 )
   return(rec_bsrch(v,cell,top,item,comp));
}


int srch_cmp1( record *p , char *str)
{
 return(strcmp(p->name,str));
}


int srch_cmp2( record *p , char *str)
{
 return(strcmp(p->lastname,str));
}


int srch_cmp3( record *p , char *str)
{
 return(numcmp(p->age,str));
}


int srch_cmp4( record *p , char *str)
{
 return(numcmp(p->id,str));
}
#include <conio.h>
#include "vector.h"
#include "matrix.h"
#include "attrib.h"

void main()
{
 clrscr();
 matrix m1=UNIT_MAT,m2;
 vector v1(1,0,0),v2;
 attrib a1(0,0,128,0,0,0,1),a2(0,0,0,0,0,0,1);
 cout<<v1<<endl;
 for(int i=0;i<4;i++)
    {
     a2+=a1;
     prep_gen_mat(m2,a2);
     m2*=m1;
     v2=v1*m2;
     cout<<v2<<endl;
    }
 getch();
}

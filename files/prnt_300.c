#include<stdio.h>
void main()
{
	 int i;
	 for (i=1;i<=300;i++){
		  printf("%3d ",i);
		  if ((i % 10) == 0)
			printf("\n");
	 }
}

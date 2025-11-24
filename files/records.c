#include<stdio.h>
#include<conio.h>
#include<mylib.h>

record *ptr[NUM];
FILE *fp;
char *filename;
int maxnum=0;


main()
{
 char key,*str;
 int i;

 clrscr();
 do{
    initial();
    switch(key=getch())
	  {
	   case 'f':find_scr();
		    switch(key=getch())
			  {
			   case 'a':printf("\rEnter Age: ");
				    gets(str);	
				    rec_qsort((void **)ptr , 0 , maxnum
					      ,(int(*)(void*, void*))(sort_cmp3));
				    i=rec_bsrch((void **) ptr, 0, maxnum+1, str
					      ,(int (*)(void*,void*))(srch_cmp3));
				    break;
			   case 'i':printf("\rEnter Id No. : ");
				    gets(str);
				    rec_qsort((void **) ptr , 0 , maxnum
					      ,(int(*)(void*, void*))(sort_cmp4));
				    i=rec_bsrch((void **) ptr, 0, maxnum+1, str
					      ,(int (*)(void*,void*))(srch_cmp4));
				    
				    break;
			   case 'l':printf("\rEnter Lastname: ");
				    gets(str);
				    rec_qsort((void **) ptr , 0 , maxnum
					      ,(int(*)(void*, void*))(sort_cmp2));
				    i=rec_bsrch((void **) ptr, 0, maxnum+1, str
					      ,(int (*)(void*,void*))(srch_cmp2));
				    
				    break;
			   case 'n':printf("\rEnter Name: ");
				    gets(str);
				    rec_qsort((void **) ptr , 0 , maxnum
					      ,(int(*)(void*, void*))(sort_cmp1));
				    i=rec_bsrch((void **) ptr, 0, maxnum+1, str
					      ,(int (*)(void*,void*))(srch_cmp1));
				    
				    break;
			  }
		    if(i == -1)
		       puts("could not find this record !");
		    else
		       printf("record No.%d: %s %s %s %s\n"
					     ,i+1
		                             ,ptr[i]->name
					     ,ptr[i]->lastname
					     ,ptr[i]->age
					     ,ptr[i]->id);
		    getch();
		    break;
	   case 'g':get_dtls();
		    break;
	   case 'p':prnt_rcd();
		    break;
	   case 'r':rd_file();
		    break;
	   case 's':save_rcd();
		    break;
	   case 'c':clear();
	   defualt:break;
	  }
    dspl_rcd();
   }
 while(key != 'q');
}
#include <iostream.h>
#include <mytree.h>
#include <stdlib.h>

main()
{
 mydata *tmp,*root,*t;
 int i;
 int x[15]={50,25,75,12,37,62,87,6,18,31,43,56,68,81,93};
 //int x[15]={6,12,18,25,31,37,43,50,56,62,68,75,81,87,93};
 //int x[15]={93,87,81,75,68,62,56,50,43,37,31,25,18,12,6};

 root=NULL;

 for(i=0; i<15; i++)
    {
     tmp=new mydata(x[i]);
     if (tmp==NULL)
	exit(0);
     //cin>>*tmp;
     tmp->add(root);
     if(root==NULL)
       root=tmp;
    }

 root->pre_order();
 cout<<"\n";
 /*
 root->in_order();
 cout<<"\n";
 root->post_order();
 cout<<"\n";
 i=root->deep();
 cout<<i<<"\n\n";
 t=new mydata(12);
 tmp=(mydata*)root->search(t);
 if(tmp!=NULL)
    cout<<*tmp;
 else cout<<"not found";
 */
 return 0;
}

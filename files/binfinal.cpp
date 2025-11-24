#include <iostream.h>

class btree
{
 protected:
   int count;
   btree *right;
   btree *left;
 public:
   btree();
   int (*cond)(void *bt1,void *bt2);
   btree *addtree(btree *bt);
};

btree::btree()
{
 count=0;
 this->right=NULL;
 this->left=NULL;
}

btree *btree::addtree(btree *bt)
{
 if (bt==NULL)
    {
     this->count=1;
     bt=this;
    }
    else if (cond(this,bt)==0)
	     bt->count++;
    else if (cond(this,bt)<0)
	     bt->left=addtree(bt->left);
    else if (cond(this,bt)>0)
	     bt->right=addtree(bt->right);
 return(bt);
}

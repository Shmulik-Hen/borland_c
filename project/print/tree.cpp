/**************************************************************************
* SUBJECT:    FLIGHT SIMULATOR.                                           *
*                                                                         *
* TITLE:      GRADUATION PROJECT.                                         *
*                                                                         *
* FILE NAME:  tree.cpp                                                    *
*                                                                         *
* PURPOSE:    function definitions for class TREE.                        *
**************************************************************************/

#include "tree.h"

/* function for adding a link at specific point */

void treenode::addnode(treenode* parrent)
{
 if(!parrent)
   parrent=this;
 else
   {
    this->next=parrent->son;
    parrent->son=this;
   }
}

/* function for finding an item in the tree */

treenode* treenode::search(treenode* root, int (*comp)(const void*))
{
 treenode *p;

 if(!root)
   return NULL;
 if(comp(root))
    return root;
 p=search(root->son,comp);
 if(p)
   return p;
 else
   return(search(root->next,comp));
}

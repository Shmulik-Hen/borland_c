#ifndef _BTREE.H
#define _BTREE.H
class btree
{
 private:
  btree *right;
  btree *left;
 public:
  char dir;
  static char LR;
  int count;
  btree();
  btree *add(btree *bt);
  int (*cond)(void *bt1,void *bt2);
  virtual void print()=0;
  void pre_order();
  void in_order();
  void post_order();
  int deep();
  btree *search(btree *bt);
  friend void del(btree* bt);
};
#endif
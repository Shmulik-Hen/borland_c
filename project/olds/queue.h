#ifndef _QUEUE_H
#define _QUEUE_H

template<class T>
class queue
      {
	typedef struct tag_item
		       {
			T* data;
			tag_item* next;
		       }item;
	item* head;
	item* tail;
       public:
	queue();
	~queue();
	void push(T*);
	T* pop();
	int empty();
      };
#endif

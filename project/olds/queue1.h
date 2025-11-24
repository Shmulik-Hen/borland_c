#ifndef _QUEUE_H
#define _QUEUE_H

template<class T>
class queue
      {
	T* head;
	T* tail;
       public:
	queue();
	~queue();
	void push(T*);
	T* pop();
      };
#endif

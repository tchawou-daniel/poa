#ifndef DEF_MYCHAINEDSTACK
#define DEF_MYCHAINEDSTACK
#include "mystack.h"

class Mychainedstack : public Mystack{
	struct List {
		int elt ;
		List *next;
	};

	public:
	List *ptr=nullptr;
	void push(int number);
	int pop(void);
	int operator%(int mod) const;
	void clear();
	Mychainedstack();
	~Mychainedstack();
    void print();
	int size() const;
};

#endif
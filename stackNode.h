#ifndef __STACKNODE_H__
#define __STACKNODE_H__

#include "SExp.h"


class stackNode{
public:
	int type;
	char token;
	SExp* s;
	stackNode();
	stackNode(char b);
	stackNode(SExp* b);
	stackNode(const stackNode& a);
	stackNode& operator=(const stackNode& a);
	void show();
};


#endif
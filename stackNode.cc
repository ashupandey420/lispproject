/*AUTHOR: ASHUTOSH PANDEY
  EMAIL: pandey.99@osu.edu
  COURSE: CSE 6341
  FILE: stackNode.cc*/

#include "stackNode.h"
#include <iostream>



stackNode::stackNode():s(NULL){}


stackNode::stackNode(char b):type(1),token(b),s(NULL){}


stackNode::stackNode(SExp* b):type(2),s(b){}


stackNode::stackNode(const stackNode& a){
		type=a.type;
		token=a.token;
		s=new SExp;
		*s=*(a.s);
}


stackNode& stackNode::operator=(const stackNode& a){
	if(this!=&a){
		type=a.type;
		token=a.token;
		*s=*(a.s);
	}
	return *this;
}


void stackNode::show(){
		if(type==1){std::cout<<token;}
		else {s->show();}
	}

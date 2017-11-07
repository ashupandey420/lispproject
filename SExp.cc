/*AUTHOR: ASHUTOSH PANDEY
  EMAIL: pandey.99@osu.edu
  COURSE: CSE 6341
  FILE: SExp.cc*/
#include "SExp.h"
//#include "globalVars.h"

std::list <SExp*> SExp::idPointers=std::list <SExp*> ();
SExp::SExp(){}

SExp::SExp(int64_t v):type(1),value(v),left(NULL),right(NULL),isFun(0),funDef(NULL){ idPointers.push_front(this);}

SExp::SExp(std::string n):type(2),name(n),left(NULL),right(NULL),isFun(0),funDef(NULL){idPointers.push_front(this);}

SExp::SExp(SExp* l, SExp* r):type(3),left(l),right(r),isFun(0),funDef(NULL){}

void SExp::changeToFun(SExp* def){
	this->funDef=def;
	this->isFun=1;
}
void SExp::show() {
	if(type==1){
		std::cout<<this->value;
	}
	else if (type==2){
		std::cout<<this->name;
	}
	else{
		std::cout<<"(";
		this->left->show();
		std::cout<<" . ";
		this->right->show();
		std::cout<<")";
	}
}

void SExp::showIdList(){
	//std::list<SExp*> idPointers;
	std::list<SExp*>::iterator it;
	for(it=this->idPointers.begin();it!=this->idPointers.end();++it){
		(*it)->show();
		std::cout<<"\n";		
	}
}



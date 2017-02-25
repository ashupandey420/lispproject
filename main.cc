#include <iostream>
#include<string.h>
//#include<stdint.h>
using namespace std;
#define INT64 int64_t
class SExp{
public:
	int type;
	INT64 value;
	string name;
	SExp* left;
	SExp* right;
	SExp(){left=NULL;right=NULL;}
	SExp(int t, INT64 v):type(t),value(v){}
	SExp(int t, string n):type(t),name(n){}
	SExp(SExp* l, SExp* r):type(3),left(l),right(r){}
	void show();
};
void SExp::show(){
	std::cout<<type<<"\n";
	std::cout<<value<<"\n";
	std::cout<<name<<"\n";
}

SExp T(2,"T");
SExp NIL(2,"NIL");

SExp* ATOM(SExp* s);

SExp* CAR(SExp* s);

SExp* EQ(SExp* s);

SExp* CDR(SExp* s);
int main() {
	SExp s1(1,2);
	s1.show();
	SExp s2(2,"Ashu");
	s2.show();
	SExp s3(&s1,&s2);
	s3.show();
	SExp* s4=ATOM(&s3);
	s4->show();
	SExp* s5=CAR(s4);
	s5->show();

	SExp* s6=CDR(s4);
	s6->show();
   	return 0;
}

SExp* ATOM(SExp* s){
	if(s->type==1 or s->type==2){
		return &T;
	}
	else{
		return &NIL;
	}
}

SExp* EQ(SExp* s1,SExp* s2){
	if(ATOM(s1)==&T && ATOM(s2)==&T){
		if(s1->type==1 && s2->type==1){
			if(s1->value==s2->value){
				return &T;
			}
			else{
				return &NIL;
			}
		}
		else{
			if(&s1==&s2){
				return &T;
			}
			else{
				return &NIL;
			}
		}
	}
	else{
		cout<<"one of the arguments for Eq is non atomic";
		exit(1);
	}
}

SExp* CAR(SExp* s){
	if(ATOM(s)==&T){
		throw "CAR";
		exit(1);
	}
	else{
		return s->left;
	}
}

SExp* CDR(SExp* s){
	if(ATOM(s)==&T){
		throw 20;
		exit(1);
	}
	else{
		return s->right;
	}
}
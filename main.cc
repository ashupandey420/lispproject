#include <iostream>
#include <fstream>
#include <string>
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
	SExp(INT64 v):type(1),value(v){}
	SExp(string n):type(2),name(n){}
	SExp(SExp* l, SExp* r):type(3),left(l),right(r){}
	void show();
};
void SExp::show(){
	std::cout<<type<<"\n";
	std::cout<<value<<"\n";
	std::cout<<name<<"\n";
}
void printSExp(SExp* s);
SExp T("T");
SExp NIL("NIL");

SExp* ATOM(SExp* s);

SExp* CAR(SExp* s);

SExp* EQ(SExp* s);

SExp* CDR(SExp* s);
int main() {
	string a;
	a="123";
	cout<<a[4]<<'\n';
	/*string line;
	string input;
	while (getline(cin, line))
	{
	    
	    if(line == "$"){
	    	cout<<"Ashutosh"<<"\n";
	    	//line="";
	    	//input="";
	    }
	    
	    cout<<line<<"\n\n";
	    if (line == "$$"){
	    	break;
	    }
	}
	input="((A.3).(4.ABC))";
	//is.get(input,"$");
	SExp s1(1);
	//s1.show();
	SExp s2("Ashu");
	//s2.show();
	SExp s3(3);
	//s3.show();
	SExp s4("Pandey");
	SExp s5(5);

	SExp s6(6);
	//s1.show();
	SExp s7(7);
	//s2.show();
	SExp s8(8);
	//s3.show();
	SExp s9(&s1,&s2);
	SExp s10(&s3,&s4);
	SExp s11(&s5,&s6);
	SExp s12(&s7,&s8);
	SExp s13(&s9,&s10);
	SExp s14(&s11,&s12);
	SExp s15(&s13,&s14);
	//s4->show();
	/*printSExp(&s15);
	cout<<"\n";
	printSExp(CAR(&s15));
	cout<<"\n";
	printSExp(CDR(&s15));
	cout<<"\n";
	printSExp(CAR(CAR(&s15)));
	cout<<"\n";
	printSExp(CDR(CAR(&s15)));
	cout<<"\n";
	printSExp(CAR(CDR(&s15)));
	cout<<"\n";
	printSExp(CDR(CDR(&s15)));
	cout<<"\n";
	printSExp(CAR(CAR(CAR(&s15))));
	cout<<"\n";
	printSExp(CDR(CAR(CAR(&s15))));
	cout<<"\n";
	printSExp(CAR(CDR(CAR(&s15))));
	cout<<"\n";
	printSExp(CDR(CDR(CAR(&s15))));
	cout<<"\n";
	printSExp(CAR(CAR(CDR(&s15))));
	cout<<"\n";
	printSExp(CDR(CAR(CDR(&s15))));
	cout<<"\n";
	printSExp(CAR(CDR(CDR(&s15))));
	cout<<"\n";
	printSExp(CDR(CDR(CDR(&s15))));*/
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
		cout<<"error CAR expects non atomic arguments";
		exit(1);
	}
	else{
		return s->left;
	}
}

SExp* CDR(SExp* s){
	if(ATOM(s)==&T){
		cout<<"error CDR expects non atomic arguments";
		exit(1);
	}
	else{
		return s->right;
	}
}

void printSExp(SExp* s){
	if(ATOM(s)==&T){
		if(s->type==1){
			cout<<s->value;
		}
		else{
			cout<<s->name;
		}
	}
	else{
		cout<<"(";
		printSExp(s->left);
		cout<<" . ";
		printSExp(s->right);
		cout<<")";
	}
}
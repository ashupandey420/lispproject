#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <algorithm>
#include <list>
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
	static std::list <SExp*> idPointers;
	SExp(){left=NULL;right=NULL;}
	SExp(INT64 v):type(1),value(v),left(NULL),right(NULL){idPointers.push_front(this);}
	SExp(string n):type(2),name(n),left(NULL),right(NULL){idPointers.push_front(this);}
	SExp(SExp* l, SExp* r):type(3),left(l),right(r){}
	void show();
	void showIdList();
};

std::list <SExp*> SExp::idPointers;
std::string error="Error: Invalid SExpression\n\n\n\n";
void printSExp(SExp* s);
SExp T("T");
SExp NIL("NIL");
SExp* ATOM(SExp* s);

SExp* CAR(SExp* s);

SExp* EQ(SExp* s);

SExp* CDR(SExp* s);

SExp* CONS(SExp* l,SExp* r);
void SExp::show(){
	printSExp(this);
}

void SExp::showIdList(){
	std::list<SExp*>::iterator it;
	for(it=idPointers.begin();it!=idPointers.end();++it){
		printSExp(*it);
	}
}
class stackNode{
public:
	int type;
	char token;
	SExp* s;
	stackNode(){}
	stackNode(char b):type(1),token(b),s(NULL){}
	stackNode(SExp* b):type(2),s(b){}
	stackNode(const stackNode& a){
		type=a.type;
		token=a.token;
		s=new SExp;
		*s=*(a.s);
	}
	stackNode& operator=(const stackNode& a){
		if(this!=&a){
			type=a.type;
			token=a.token;
			*s=*(a.s);
		}
		return *this;

	}
	void show(){
		if(type==1){cout<<token;}
		else {printSExp(s);}
	}

};
std::pair<bool,SExp*> doesExist(string tempStr);
void parseInput(string input);
bool isvalidID(string a);
bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }
inline bool isInteger(const std::string & s);
int main(){

	stack<stackNode*> myStack;
	string line;
	string input;
	
	//myStack.push(&n1);


	while (getline(cin, line))
	{
	    
	    if((line == "$") || (line=="$$")){
	    	//cout<<input<<"\n\n\n";
	    	
	    	
			string::iterator new_end = unique(input.begin(), input.end(), BothAreSpaces);
			input.erase(new_end, input.end()); 
	    	input.erase(remove(input.begin(), input.end(), '\n'),input.end());
			input.erase(remove(input.begin(), input.end(), '\t'),input.end());
	    	parseInput(input);
	    	
	    	if (line == "$$"){
	    		break;
	    	}
	    	line="";
	    	input="";
	    }
	    input+=line;
	    //cout<<line<<"\n\n";
	    
	}
}

void parseInput(string input){
	cout<<"input received: "<<input<<"\n\n";
	stack<stackNode*> myStack;
	
	string tempStr;
	//stackNode tempNode;
	int tempInt;
	std::string::iterator it=input.begin();
	while(1){
		if(it==input.end()){break;}
		else if(*it==' '){++it;}
		else if(*it=='(' || *it=='.'){
			//cout<<"neha\n";
			stackNode* tempNode= new stackNode(*it);
			myStack.push(tempNode);
			++it;
			
		}
		else if(*it!='(' && *it!=')'&& *it!='.'){
			tempStr="";

			while((*it>=48 && *it<=57)||(*it>=65 && *it<=90)){
				tempStr+=*it;
				++it;
			}
			if(*it!='('&& *it!=')' && *it!='.' && *it!=' '&& it!=input.end()){
				cout<<"Error: Illegal character "<<*it<<" in string.\n\n\n\n";
				return;
			}
			if(!isvalidID(tempStr)){
				cout<<"Error: Illegal identifeir "<<tempStr<<" in string.\n\n\n\n";
				return;
			}
			if(isInteger(tempStr)){
				tempInt=std::stoi(tempStr);
				SExp* s =new SExp(tempInt);
				stackNode* tempNode= new stackNode(s);
				myStack.push(tempNode);
			}
			else{
				std::pair<bool,SExp*> p;
				p=doesExist(tempStr              );
				if(!p.first){
					SExp* s =new SExp(tempStr);
					stackNode* tempNode = new stackNode(s);
					myStack.push(tempNode);
				}
				else{
					stackNode* tempNode = new stackNode(p.second);
					myStack.push(tempNode);
				}
				
				
			}
			
			
		}

		else if(*it==')'){
			//cout<<"inside )\n";
			if(myStack.empty()){
				cout<<error;
				return;
			}
			stackNode* s1=myStack.top();
			
			if(s1->type==1){
				if(s1->token=='('){
					//cout<<"shivam\n";
					myStack.pop();
					stackNode* tempNode= new stackNode (&NIL);
					myStack.push(tempNode);

				}
				else{
					cout<<error;
					return;
				}
			}
			else if(s1->type==2){
				myStack.pop();
				if(myStack.empty()){
					cout<<error;
					return;
				}
				stackNode *s2=myStack.top();
				if(s2->type==1 and s2->token==')'){
					cout<<error;
					return;
				}
				else if(s2->type==1 and s2->token=='('){
					myStack.pop();
					SExp* temp=new SExp(s1->s,&NIL);
					stackNode* t=new stackNode(temp);
					myStack.push(t);
				}
				else if(s2->type==1 and s2->token=='.'){
					myStack.pop();
					if(myStack.empty()){
						cout<<error;
						return;
					}
					stackNode* s3=myStack.top();
					if(myStack.top()->type==1){
						cout<<error;
						return;
					}
					else{
						myStack.pop();
						if(myStack.empty()){
							cout<<error;
							return;
						}
						if(!(myStack.top()->type==1 and myStack.top()->token=='(')){
							cout<<error;
							return;
						}
						else{

							myStack.pop();
							SExp* temp=new SExp(s3->s,s1->s);
							stackNode* t=new stackNode(temp);
							myStack.push(t);
						}
					}
				}
				else if(s2->type==2){
					SExp* r=s1->s;
					r=new SExp(r,&NIL);
					while(!(myStack.empty()) and !(myStack.top()->type==1)){
						r=new SExp(myStack.top()->s,r);
						myStack.pop();
					}
					if(myStack.empty()){
						cout<<error;
						return;
					}
					else if(myStack.top()->token=='.' or myStack.top()->token==')'){
						cout<<error;
						return;
					}
					else{
						myStack.pop();
						stackNode* t=new stackNode(r);
						myStack.push(t);
					}
				}
			}
			++it;
			//cout<<"out of it\n";
		}

	}
	if(myStack.empty()){
		cout<<error;
	}
	else{
		stackNode *s1=myStack.top();
		if(s1->type!=2){
			cout<<error;
			return;
		}
		myStack.pop();
		if(!myStack.empty()){
			cout<<error;
			return;
		}
		s1->show();
		cout<<"\n\n\n\n";
	}
	/*while(!myStack.empty()){
		myStack.top()->show();
		cout<<"   "<<"\n";
		myStack.pop();
	}
	cout<<"printting idPointers\n";
	std::list<SExp*>::iterator it1;
	for(it1=SExp::idPointers.begin();it1!=SExp::idPointers.end();++it1){
		(*it1)->show();
		cout<<"   "<<"\n";
	}*/
	return;
}			
	


inline bool isInteger(const std::string & s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
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
SExp* CONS(SExp* l,SExp* r){
	SExp *s=new SExp[1];
	s->left=l;
	s->right=r;
	s->type=3;
	return s;
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

bool isvalidID(string a){
	if(a[0]>=65 && a[1]<=90){
		return true;
	}
	else{
		std::string::iterator it;
		for(it=a.begin();it!=a.end();++it){
			if(!(*it>=48 && *it<=57)){
				return false;
			}
		}
		return true;
	}
}

std::pair<bool,SExp*> doesExist(string tempStr){
	std::list<SExp*>::iterator it;
	std::pair<bool,SExp*> p;
	for(it=SExp::idPointers.begin();it!=SExp::idPointers.end();++it){
		if((*it)->type==2 and (*it)->name==tempStr){
			p.first=true;
			p.second=*it;
			return p;
		}
	}
	p.first=false;
	p.second=NULL;
	return p;
}


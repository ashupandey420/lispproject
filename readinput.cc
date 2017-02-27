#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <algorithm>
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
class stackNode{
public:
	int type;
	char token;
	string id;
	int value;
	SExp* s;
	stackNode(){}
	stackNode(char b):type(1),token(b){}
	stackNode(string b):type(3),id(b){}
	stackNode(int b):type(2),value(b){}
	stackNode(SExp* b):type(4),s(b){}
	stackNode(const stackNode& a){
		type=a.type;
		token=a.token;
		id=a.id;
		value=a.value;
		s=new SExp;
		*s=*(a.s);
	}
	stackNode& operator=(const stackNode& a){
		if(this!=&a){
			type=a.type;
			token=a.token;
			id=a.id;
			value=a.value;
			s=new SExp;
			*s=*(a.s);
		}
		return *this;

	}
	void show(){
		if(type==1){cout<<token<<'\n';}
		else if(type==2){cout<<value<<"\n";}
		else if(type==3){cout<<id<<"\n";}
		else {printSExp(s);}
	}

};
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
	cout<<"inside parse Input"<<"\n";
	cout<<"input received: "<<input<<"\n\n\n";
	stack<stackNode*> myStack;
	
	string tempStr;
	//stackNode tempNode;
	int tempInt;
	std::string::iterator it=input.begin();
	while(1){
		
		cout<<*it<<"\n";
		if(it==input.end()){break;}
		else if(*it==' '){++it;}
		else if(*it=='(' || *it=='.'){
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
			if(*it!='('&&*it!=')' && *it!='.' && *it!=' '){
				cout<<"error: illegal character "<<*it<<" in string.\n";
				exit(1);
			}
			if(!isvalidID(tempStr)){
				cout<<"error: Illegal identifeir "<<tempStr<<" in string.\n";
				exit(1);
			}
			cout<<"Identifier is: "<<tempStr<<"\n";
			if(isInteger(tempStr)){
				cout<<tempStr<<"  is  integer";
				tempInt=std::stoi(tempStr);
				cout<<tempInt<<"\n";
				stackNode* tempNode= new stackNode(tempInt);
				myStack.push(tempNode);
			}
			else{
				cout<<tempStr<<"  is  not integer";
				stackNode* tempNode = new stackNode(tempStr);
				myStack.push(tempNode);
			}
			
			
		}
		


		else if(*it==')'){
			if(myStack.empty()){
				cout<<"error: Invalid S expression\n";
				exit(1);
			}

			cout<<"inside )"<<"\n";

			stackNode* s1=myStack.top();

			myStack.top()->show();
			
			if(s1->type==1){
				
				if(s1->token=='('){
					myStack.pop();
					stackNode* temp= new stackNode(&NIL);
					myStack.push(temp);
				}
				else{
					cout<<"error: Invalid Sexpression\n";
					exit(1);
				}
			}

			else if(s1->type==2){
				myStack.pop();
				cout<<"bhako";
				myStack.top()->show();
				if(myStack.empty()){
					cout<<"error: Invalid S expression\n";
					exit(1);
				}
				stackNode* s2=myStack.top();
				cout<<"bhak";
				myStack.top()->show();
				if (s2->type==2 or s2->type==3){
					SExp* r=&NIL;
					while(!(myStack.top()->type==1) and !myStack.empty()){
						stackNode* temp=myStack.top();
						SExp *l;
						if(temp->type==2){
							SExp* l1= new SExp(temp->value);
							l=l1;
						}
						else if(temp->type==3){
							SExp* l1 = new SExp(temp->id);
							l=l1;
						}
						else if(temp->type==4){
							SExp* l1 = new SExp(*(temp->s));
							l=l1;
						}
						r=CONS(l,r);
						myStack.pop();
					}
					if(myStack.empty()){
						cout<<"error: Invalid S expression\n";
						exit(1);
					}
					if(myStack.top()->token!='('){
						cout<<"error: Invalid S expression\n";
						exit(1);
					}
					myStack.pop();
					stackNode* t= new stackNode(r);
					myStack.push(t);
				}


			}
			
			++it;
			
		}


	}
	while(!myStack.empty()){
		cout<<"shivam"<<"\n";
			myStack.top()->show();
			myStack.pop();
		}
		exit(1);
}

	
		
			/*else if(s1->type==2){	
				
				if(myStack.top()->type==1){

					if(myStack.top()->token=='('){
						cout<<"kuttu\n";
						myStack.pop();
						SExp temp(s1->value);
						myStack temp1(CONS(&temp,&NIL));
						myStack.push(&temp1);
						myStack.top()->show();
					}
					else if(myStack.top()->token=='.'){
						cout<<"shivam"<<"\n";
						myStack.pop();
						if(myStack.top()->type==2){	
							stackNode* n1=myStack.top();
							myStack.pop();
							if(myStack.top()->type==1){
								if(myStack.top()->token=='('){
									myStack.pop();

									SExp templ(n1->value);
									SExp tempr(s1->value);
									stackNode temp(CONS(&templ,&tempr));
									myStack.push(&temp);
									cout<<"neha"<<"\n";
									myStack.top()->show();
									
								}
								else{
									cout<<"error: Invalid Sexpression\n";
									exit(1);
								}
							}
							else{
								cout<<"error: Invalid Sexpression\n";
								exit(1);
							}

						}
						else if(myStack.top()->type==3){
							stackNode* n1=myStack.top();
							myStack.pop();
							if(myStack.top()->type==1){
								if(myStack.top()->token=='('){
									myStack.pop();

									SExp templ(n1->id);
									SExp tempr(s1->value);
									stackNode temp(CONS(&templ,&tempr));
									myStack.push(&temp);
									cout<<"neha"<<"\n";
									myStack.top()->show();
									
									
								}
								else{
									cout<<"error: Invalid Sexpression\n";
								}
							}
							else{
								cout<<"error: Invalid Sexpression\n";
								exit(1);
							}
						}
						else if(myStack.top()->type==4){
							cout<<"inside 4";
							
							stackNode* n1=myStack.top();
							
							n1->show();
							exit(1);
							//n1.show();
							
							myStack.pop();
							if(myStack.top()->type==1){
								myStack.top()->show();
								cout<<"bakchodi"<<"\n";
								
								cout<<myStack.top()->token<<"\n";

								if(myStack.top()->token=='('){

									cout<<"kuttu"<<"\n";
									myStack.pop();
									SExp temp(s1->value);
									temp.show();
									n1->s->show();
									SExp* t=CONS(n1->s,&temp);
									t->show();
									exit(1);
									myStack temp1(CONS(n1->s,&temp));
									myStack.push(&temp1);
									myStack.top()->show();
									
									
									
								}
								else{
									cout<<"error: Invalid Sexpression\n";
									exit(1);
								}
							}
							else{
								cout<<"error: Invalid Sexpression\n";
								exit(1);
							}
						}
					}
					

				}

				/*else if(myStack.top().type==2||myStack.top().type==3){
					SExp r(s.value);
					SExp* r1=CONS(&r,&NIL);
					while(!(myStack.top().type==1 && myStack.top().token=='(')&& !myStack.empty()){
						stackNode n1=myStack.top();
						
						if(n1.type==2){
							SExp l(n1.value);
							r1=CONS(&l,r1);
						}
						else if(n1.type==3){
							SExp l(n1.id);
							r1=CONS(&l,r1);
						}
						else if(n1.type==4){
							r1=CONS(n1.s,r1);
						}
						else{
							cout<<"error: Invalid Sexpression\n";
							exit(1);
						}
						myStack.pop();
					}
					if(myStack.empty()){
						cout<<"error: Invalid Sexpression\n";
					}
					else{
						myStack.pop();
						stackNode t(r1);
						myStack.push(t);
						++it;
					}
				}
			}
		//else if(*it)*/
			/*cout<<"end ) \n";
			++it;
		
			}
		}*/
		

	
	/*if(input[0]=='('){
		cout<<'('<<"\n";
	}*/


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


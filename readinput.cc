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
		if(type==1){cout<<token<<'\n';}
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
			cout<<"jai na ho"<<"\n";
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
			if(*it!='('&& *it!=')' && *it!='.' && *it!=' '){
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
				SExp* s =new SExp(tempInt);
				stackNode* tempNode= new stackNode(s);
				myStack.push(tempNode);
			}
			else{
				cout<<tempStr<<"  is  not integer";
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
		
		/*else if(*it==')'){
			while(!myStack.empty()){
				cout<<"shivam"<<"\n";
				myStack.top()->show();
				myStack.pop();
			}
			std::list<SExp*>::iterator it;
			for(it=SExp::idPointers.begin();it!=SExp::idPointers.end();++it){
				(*it)->show();
			}
			exit(1);
		}*/

		else if(*it==')'){
			if(myStack.empty()){
				cout<<"error: Invalid S expression\n";
				exit(1);
			}

			cout<<"inside )"<<"\n";

			stackNode* s1=myStack.top();

			s1->show();
			
			if(s1->type==1){
				
				if(s1->token=='('){
					cout<<"jai ho"<<"\n";
					myStack.pop();
					myStack.top()->show();
					stackNode* tempNode= new stackNode (&NIL);
					myStack.push(tempNode);

				}
				else{
					cout<<"error: Invalid Sexpression\n";
					exit(1);
				}
			}
			else if(s1->type==2){
				myStack.pop();
				stackNode *s2=myStack.top();
				if(s2->type==1 and s2->token==')'){
					cout<<"error: Invalid Sexpression";
					exit(1);
				}
				else if(s2->type==1 and s2->token=='('){
					myStack.pop();
					myStack.top()->show();
					SExp* temp=new SExp(s1->s,&NIL);
					stackNode* t=new stackNode(temp);
					myStack.push(t);
				}
				else if(s2->type==1 and s2->token=='.'){
					myStack.pop();
					stackNode* s3=myStack.top();
					if(myStack.top()->type==1){
						cout<<"error: Invalid Sexpression\n";
						exit(1);
					}
					else{
						myStack.pop();
						if(!(myStack.top()->type==1 and myStack.top()->token=='(')){
							cout<<"error: Invalid Sexpression\n";
							exit(1);
						}
						else{
							myStack.top()->show();
							SExp* temp=new SExp(s3->s,s1->s);
							stackNode* t=new stackNode(temp);
							myStack.push(t);
						}
					}
				}
				
			++it;
		}
	}
	myStack.top()->show();
}			/*else if(s1->type==2){
	}			myStack.pop();
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


			}*/
			
			
			
		

	
	/*while(!myStack.empty()){
		cout<<"shivam"<<"\n";
			myStack.top()->show();
			myStack.pop();
		}
		exit(1);*/


	
		
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


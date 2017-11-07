/*AUTHOR: ASHUTOSH PANDEY
  EMAIL: pandey.99@osu.edu
  COURSE: CSE 6341
  FILE: globalFuncs.cc*/

#include "globalFuncs.h"

std::string error="Error: Invalid SExpression";


std::pair<bool,SExp*> doesExist(std::string tempStr){
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


SExp* parseInput(std::string input, SExp* NIL){
	//cout<<"input received: "<<input<<"\n\n";
	std::stack<stackNode*> myStack;
	
	std::string tempStr;
	//stackNode tempNode;
	int64_t tempInt;
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
			if(*it=='+' || *it=='-'){
				tempStr+=*it;
				++it;
			}
				
			
			while((*it>=48 && *it<=57)||(*it>=65 && *it<=90)){
				tempStr+=*it;
				++it;
			}
			if(*it!='('&& *it!=')' && *it!='.' && *it!=' '&& it!=input.end()){
				std::string err_string="Error: Illegal character ";
				err_string+=*it;
				err_string=err_string +" in string";
				throw err_string;
				//return;
			}
			if(!isvalidID(tempStr)){
				std::string err_string="Error: Illegal identifeir ";
				err_string=err_string+tempStr+" in string";
				throw err_string;
			}
			if(isInteger(tempStr)){
				tempInt=std::stoll(tempStr,NULL,10);
				SExp* s =new SExp(tempInt);
				stackNode* tempNode= new stackNode(s);
				myStack.push(tempNode);
			}
			else{
				std::pair<bool,SExp*> p;
				p=doesExist(tempStr);
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
				throw error;
			}
			stackNode* s1=myStack.top();
			
			if(s1->type==1){
				if(s1->token=='('){
					//cout<<"shivam\n";
					myStack.pop();
					stackNode* tempNode= new stackNode (NIL);
					myStack.push(tempNode);

				}
				else{
					throw error;
				}
			}
			else if(s1->type==2){
				myStack.pop();
				if(myStack.empty()){
					throw error;
				}
				stackNode *s2=myStack.top();
				if(s2->type==1 and s2->token==')'){
					throw error;
				}
				else if(s2->type==1 and s2->token=='('){
					myStack.pop();
					SExp* temp=new SExp(s1->s,NIL);
					stackNode* t=new stackNode(temp);
					myStack.push(t);
				}
				else if(s2->type==1 and s2->token=='.'){
					myStack.pop();
					if(myStack.empty()){
						throw error;
					}
					stackNode* s3=myStack.top();
					if(myStack.top()->type==1){
						throw error;
					}
					else{
						myStack.pop();
						if(myStack.empty()){
							throw error;
						}
						if(!(myStack.top()->type==1 and myStack.top()->token=='(')){
							throw error;
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
					//SExp* r=s1->s;
					SExp* r=new SExp(s1->s,NIL);
					while(!(myStack.empty()) and !(myStack.top()->type==1)){
						r=new SExp(myStack.top()->s,r);
						myStack.pop();
					}
					if(myStack.empty()){
						throw error;
	
					}
					else if(myStack.top()->token=='.' or myStack.top()->token==')'){
						throw error;
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
		std::cout<<error;
	}
	else{
		stackNode *s1=myStack.top();
		if(s1->type!=2){
			throw error;
		}
		myStack.pop();
		if(!myStack.empty()){
			throw error;
		}
		return s1->s;
		//s1->show();
		//std::cout<<"\n";
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
	return NULL;
}			



bool isvalidID(std::string a){
	if(a[0]>=65 && a[1]<=90){
		return true;
	}
	else{
		std::string::iterator it;
		it=a.begin();
		if(*it=='+' || *it=='-'){
			it=it+1;
			if(it==a.end()){return false;}
			else{
				for(it=a.begin()+1;it!=a.end();++it){
					if(!(*it>=48 && *it<=57)){
						return false;
					}
				}
				return true;
			}
		}
		else{
			for(it=a.begin();it!=a.end();++it){
				if(!(*it>=48 && *it<=57)){
					return false;
				}
			}
		}
		return true;
	}
}


bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }


inline bool isInteger(const std::string & s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
}

std::string tab2Space(std::string input){
	for(int i=0;i<input.length();i++){
		if(input[i]=='\t'){
			input[i]=' ';
		}

	}
	return input;
}

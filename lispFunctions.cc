/*AUTHOR: ASHUTOSH PANDEY
  EMAIL: pandey.99@osu.edu
  COURSE: CSE 6341
  FILE: lispFunctions.cc*/

#include "lispFunctions.h"


SExp* car(SExp* s){
	if(s->type==1 or s->type==2){
		std::string err="Error: Passed argument to CAR is atomic.";
		throw err;
	}
	return s->left;
}

SExp* cdr(SExp* s){
	if(s->type==1 or s->type==2){
		std::string err="Error: Passed argument to CDR is atomic.";
		throw err;
	}
	return s->right;
}

SExp* cons(SExp* left, SExp* right){
	SExp* ans=new SExp(left,right);
	return ans;
}

SExp* atom(SExp* in){
	if(in->type==1 or in->type==2){
		return T;
	}
	else{
		return NIL;
	}
}

SExp* eq(SExp* a, SExp* b){
	if (a->type==3 or b->type==3){
		std::string err="Error: Non atomic arguments to EQ.";
		throw err;
	}
	else if(a->type==1 and b->type==1){
		if(a->value==b->value){
			return T;
		}
		else{
			return NIL;
		}
	}
	else{
		if(a==b){
			return T;
		}
		else{
			return NIL;
		}
	}
}


SExp* null(SExp* a){
	if(a==NIL){
		return T;
	}
	else{
		return NIL;
	}
}


SExp* int1(SExp* a){
	if(a->type==1){
		return T;
	}
	else{
		return NIL;
	}
}


SExp* plus(SExp* a, SExp* b){
	if(a->type==1 and b->type==1){

		SExp* ans=new SExp(a->value+b->value);
		return ans;
	}
	else{
		std::string err="Error: Non integer arguments to PLUS.";
		throw err;
	}
}

SExp* minus(SExp* a, SExp* b){
	if(a->type==1 and b->type==1){

		SExp* ans=new SExp(a->value-b->value);
		return ans;
	}
	else{
		std::string err="Error: Non integer arguments to MINUS.";
		throw err;
	}
}

SExp* times(SExp* a, SExp* b){
	if(a->type==1 and b->type==1){

		SExp* ans=new SExp(a->value*b->value);
		return ans;
	}
	else{
		std::string err="Error: Non integer arguments to TIMES.";
		throw err;
	}
}

SExp* quotient(SExp* a, SExp* b){
	if(a->type==1 and b->type==1){
		if(b->value==0){
			std::string err ="Error: Arithmetic error: Division by zero.";
			throw err;
		}

		SExp* ans=new SExp(a->value/b->value);
		return ans;
	}
	else{
		std::string err="Error: Non integer arguments to QUOTIENT.";
		throw err;
	}
}

SExp* remainder(SExp* a, SExp* b){
	if(a->type==1 and b->type==1){

		SExp* ans=new SExp(a->value%b->value);
		return ans;
	}
	else{
		std::string err="Error: Non integer arguments to REMAINDER.";
		throw err;
	}
}

SExp* less(SExp* a, SExp* b){
	if(a->type==1 and b->type==1){
		if(a->value<b->value){
			return T;
		}
		else{
			return NIL;
		}
	}
	else{
		std::string err="Error: Non integer arguments to LESS.";
		throw err;
	}
}

SExp* greater(SExp* a, SExp* b){
	if(a->type==1 and b->type==1){
		if(a->value>b->value){
			return T;
		}
		else{
			return NIL;
		}
	}
	else{
		std::string err="Error: Non integer arguments to GREATER.";
		throw err;
	}
}

SExp* equal(SExp* x, SExp* y){
	if(atom(x)==T){
		if(atom(y)==T){
			return eq(x,y);
		}
		else{
			return NIL;
		}
	}
	else if(atom(y)==T){
		return NIL;
	}
	else {
		if(equal(car(x),car(y))==T){
			return equal(cdr(x),cdr(y));
		}
		else{
			return NIL;
		}
	}
}

SExp* in(SExp* x, SExp* aList){
	if(null(aList)==T){
		return NIL;
	}
	else if(equal(car(car(aList)),x)==T){
		return T;
	}
	else{
		return in(x,cdr(aList));
	}

}

SExp* getVal(SExp* x, SExp* aList){
	if(equal(car(car(aList)),x)==T){
		return cdr(car(aList));
	}
	else{
		return getVal(x,cdr(aList));
	}
}


SExp* isList(SExp* a){
	if(atom(a)==T){
		if(a==NIL){
			return T;
		}
		else{
			return NIL;
		}
	}
	else{
		return isList(cdr(a));
	}
}
SExp* eval(SExp* exp,SExp* aList){
	if(atom(exp)==T){
		if(int1(exp)==T){
			return exp;
		}
		else if(eq(exp,T)==T){
			return T;
		}
		else if(eq(exp,NIL)==T){
			return NIL;
		}
		else if(in(exp,aList)==T){
			return getVal(exp,aList);
		}
		else{
			std::string err="Error: Unbound variable ";
			err+= exp->name;
			err+='.';
			throw err;
		}
	}
	else if(atom(car(exp))==T){
		if(isList(exp)==NIL){
			std::string err="Error: Invalid lisp expression. Non atomic expressions have to be in list form.";
			throw err;
		}
		else if(eq(car(exp),QUOTE)==T){
			if(cdr(exp)==NIL){
				std::string err="Error: Too few argument to QUOTE.";
				throw err;
			}
			else if(cdr(cdr(exp))!=NIL){
				std::string err="Error: Too much arguments to QUOTE.";
				throw err;
			}
			else{
				return car(cdr(exp));
			}
		}

		else if(eq(car(exp),COND)==T){
			if(cdr(exp)==NIL){
				std::string err="Error: Too few arguments to COND.";
				throw err;
			}
			else{
				return evcon(cdr(exp),aList);
			}
		}
		else if(eq(car(exp),DEFUN)==T){
			if(cdr(exp)==NIL){
				std::string err="Error: Too few arguments to DEFUN.";
				throw err;
			}
			else if(atom(car(cdr(exp)))==NIL){
				std::string err="Error: Function name must be atomic.";
				throw err;
			}
			else if(int1(car(cdr(exp)))==T){
				std::string err="Error: Function name can not be integer.";
				throw err;
			}
			else if(isConstants(car(cdr(exp)),lispConstants)==T){
				SExp* F=car(cdr(exp));
				std::string err="Error: Function name can not be ";
				err+=F->name;
				err+=". It is one of the built-in constants.";
				throw err;
			}
			else if(cdr(cdr(exp))==NIL){
				std::string err="Error: Invalid lisp expression. Too few arguments to DEFUN.";
				throw err;
			}
			else{
				SExp* params=car(cdr(cdr(exp)));
				if(isList(params)==NIL){
					std::string err="Error: Invalid lisp expression. Function parameters must be in the list format.";
					throw err;
				}
				else if(isValidParams(params)==NIL){
					std::string err="Error: Invalid lisp expression. Function parameters names must be atomic, non integer and non lisp constants.";
					throw err;
				}
				else if(cdr(cdr(cdr(exp)))==NIL){
					std::string err="Error: Invalid lisp expression. Too few arguments to DEFUN.";
					throw err;
				}
				else{
					SExp* body=car(cdr(cdr(cdr(exp))));
					SExp* def=new SExp(params,body);
					SExp* F=car(cdr(exp));
					F->changeToFun(def);
					//F->funDef->show();
					if(cdr(cdr(cdr(cdr(exp))))!=NIL){
						std::string err="Error: Invalid lisp expression. Too much arguments to DEFUN.";
						throw err;
					}
					return F;
				}
			}
		}
		else{
				return apply(car(exp),evlis(cdr(exp),aList),aList);
		}
	}
	else{
		std::string err="Invalid Lisp Expression.";
		throw err;
	}
}

SExp* evcon(SExp* be, SExp* aList){

	if(null(be)==T){
		std::string err="Error: Non of the conditions in COND are satisfied.";
		throw err;
	}
	else if(atom(car(be))==T){
		std::string err="Error: Atomic argument to COND. Each argument to COND has to be non atomic list.";
		throw err;
	}
	else if(isList(car(be))==NIL){
		std::string err="Error: Non list argument to COND. Each argument to COND has to be non atomic list.";
		throw err;
	}
	else if(cdr(car(be))==NIL){
		std::string err="Eroor: Invalid argument to COND. Each list must have two elements.";
		throw err;
	}
	else if(cdr(cdr(car(be)))!=NIL){
		std::string err="Eroor: Invalid argument to COND. Each list must have two elements.";
		throw err;
	}
	else if(eval(car(car(be)),aList)!=NIL){

		return eval(car(cdr(car(be))),aList);
	}
	else{
		return evcon(cdr(be),aList);
	}
}

SExp* isValidParams(SExp* params){
	if(params==NIL){
		return T;
	}
	else if((atom(car(params))==T) and (int1(car(params))==NIL) and isConstants(car(params),lispConstants)==NIL){
		return isValidParams(cdr(params));
	}
	else{
		return NIL;
	}
}

SExp* isConstants(SExp* a, SExp* list){
	
	if(list==NIL){
		return NIL;
	}
	else if(a==car(list)){
		return T;
	}
	else{
		return isConstants(a,cdr(list));
	}
}


SExp* evlis(SExp* inList, SExp* aList){
	if(null(inList)==T){
		return NIL;
	}
	else {
		if(atom(car(inList))==NIL){
			if(car(car(inList))==DEFUN){
				std::string err="Error: Argument to a function can not be a DEFUN statement";
				throw err;
			}
		}
		return cons(eval(car(inList),aList),evlis(cdr(inList),aList));
	}
}

SExp* apply(SExp* F, SExp* X, SExp* aList){
	if(atom(F)==T){
		if(eq(F,CAR)==T){
			if(X==NIL){
				std::string err="Error: Too few arguments to CAR.";
				throw err;
			}
			else if(cdr(X)!=NIL){
				std::string err="Error: Too much arguments to CAR.";
				throw err;
			}
			return car(car(X));
		}

		else if(eq(F,CDR)==T){
			if(X==NIL){
				std::string err="Error: Too few arguments to CDR.";
				throw err;
			}
			else if(cdr(X)!=NIL){
				std::string err="Error: Too much arguments to CDR.";
				throw err;
			}
			return cdr(car(X));
		}

		else if(eq(F,CONS)==T){
			if(X==NIL){
				std::string err="Error: Too few arguments to CONS.";
				throw err;
			}
			else if(cdr(X)==NIL){
				std::string err="Error: Too few arguments to CONS.";
				throw err;
			}
			else if(cdr(cdr(X))!=NIL){
				std::string err="Error: Too much arguments to CONS.";
				throw err;
			}
			return cons(car(X),car(cdr(X)));
		}
		else if(eq(F,ATOM)==T){
			if(X==NIL){
				std::string err="Error: Too few arguments to ATOM.";
				throw err;
			}
			else if(cdr(X)!=NIL){
				std::string err="Error: Too much arguments to ATOM.";
				throw err;
			}
			return atom(car(X));
		}
		else if(eq(F,NULL1)==T){
			if(X==NIL){
				std::string err="Error: Too few arguments to NULL.";
				throw err;
			}
			else if(cdr(X)!=NIL){
				std::string err="Error: Too much arguments to NULL.";
				throw err;
			}
			return null(car(X));
		}

		else if(eq(F,EQ)==T){
			if(X==NIL){
				std::string err="Error: Too few arguments to EQ.";
				throw err;
			}
			else if(cdr(X)==NIL){
				std::string err="Error: Too few arguments to EQ.";
				throw err;
			}
			else if(cdr(cdr(X))!=NIL){
				std::string err="Error: Too much arguments to EQ.";
				throw err;
			}
			return eq(car(X),car(cdr(X)));
		}

		else if(eq(F,INT)==T){
			if(X==NIL){
				std::string err="Error: Too few arguments to INT.";
				throw err;
			}
			else if(cdr(X)!=NIL){
				std::string err="Error: Too much arguments to INT.";
				throw err;
			}
			return int1(car(X));
		}

		else if(eq(F,PLUS)==T){
			if(X==NIL){
				std::string err="Error: Too few arguments to PLUS.";
				throw err;
			}
			else if(cdr(X)==NIL){
				std::string err="Error: Too few arguments to PLUS.";
				throw err;
			}
			else if(cdr(cdr(X))!=NIL){
				std::string err="Error: Too much arguments to PLUS.";
				throw err;
			}
			return plus(car(X),car(cdr(X)));
		}

		else if(eq(F,MINUS)==T){
			if(X==NIL){
				std::string err="Error: Too few arguments to MINUS.";
				throw err;
			}
			else if(cdr(X)==NIL){
				std::string err="Error: Too few arguments to MINUS.";
				throw err;
			}
			else if(cdr(cdr(X))!=NIL){
				std::string err="Error: Too much arguments to MINUS.";
				throw err;
			}
			return minus(car(X),car(cdr(X)));
		}

		else if(eq(F,TIMES)==T){
			if(X==NIL){
				std::string err="Error: Too few arguments to TIMES.";
				throw err;
			}
			else if(cdr(X)==NIL){
				std::string err="Error: Too few arguments to TIMES.";
				throw err;
			}
			else if(cdr(cdr(X))!=NIL){
				std::string err="Error: Too much arguments to TIMES.";
				throw err;
			}
			return times(car(X),car(cdr(X)));
		}

		else if(eq(F,QUOTIENT)==T){
			if(X==NIL){
				std::string err="Error: Too few arguments to QUOTIENT.";
				throw err;
			}
			else if(cdr(X)==NIL){
				std::string err="Error: Too few arguments to QUOTIENT.";
				throw err;
			}
			else if(cdr(cdr(X))!=NIL){
				std::string err="Error: Too much arguments to QUOTIENT.";
				throw err;
			}
			return quotient(car(X),car(cdr(X)));
		}

		else if(eq(F,REMAINDER)==T){
			if(X==NIL){
				std::string err="Error: Too few arguments to REMAINDER.";
				throw err;
			}
			else if(cdr(X)==NIL){
				std::string err="Error: Too few arguments to REMAINDER.";
				throw err;
			}
			else if(cdr(cdr(X))!=NIL){
				std::string err="Error: Too much arguments to REMAINDER.";
				throw err;
			}
			return remainder(car(X),car(cdr(X)));
		}

		else if(eq(F,LESS)==T){
			if(X==NIL){
				std::string err="Error: Too few arguments to LESS.";
				throw err;
			}
			else if(cdr(X)==NIL){
				std::string err="Error: Too few arguments to LESS.";
				throw err;
			}
			else if(cdr(cdr(X))!=NIL){
				std::string err="Error: Too much arguments to LESS.";
				throw err;
			}
			return less(car(X),car(cdr(X)));
		}

		else if(eq(F,GREATER)==T){
			if(X==NIL){
				std::string err="Error: Too few arguments to GREATER.";
				throw err;
			}
			else if(cdr(X)==NIL){
				std::string err="Error: Too few arguments to GREATER.";
				throw err;
			}
			else if(cdr(cdr(X))!=NIL){
				std::string err="Error: Too much arguments to GREATER.";
				throw err;
			}
			return greater(car(X),car(cdr(X)));
		}
		else{
			
			if(F->isFun==0){
				std::string err="Error: Undefined function ";
				if(int1(F)==T){
					err+=std::to_string((long long int)F->value);
					err+='.';
				}
				else{
					err=err+F->name+".";
				}
				throw err;
			}
			else{
				SExp* temp=F->funDef;
				try{
					SExp* tempList=addpairs(car(temp),X,aList);
					return eval(cdr(temp),tempList);
				}
				catch(std::string err){
					err=err+F->name+".";
					throw err;
				}

			}
		}

	}
	else{
		std::string err="Error: Unexpexted error.";
		throw err;
	}
}

SExp* addpairs(SExp* params, SExp* args,SExp* aList){
	if(params==NIL and args == NIL){
		return aList;
	}
	else if(params == NIL and args != NIL){
		std::string err="Error: Too much arguments to ";
		throw err;
	}
	else if(params !=NIL and args==NIL){
		std::string err="Error: Too few arguments to ";
		throw err;
	}
	else{
		return cons(cons(car(params),car(args)),addpairs(cdr(params),cdr(args),aList));
	}
}

SExp* printListForm(SExp* a){
	if(atom(a)==T){
		if(int1(a)==T){
			std::cout<<a->value;
		}
		else{
			std::cout<<a->name;
		}
	}
	else{
		std::cout<<"(";
		while(cdr(a)!=NIL){
			SExp* temp=car(a);
			if(isList(temp)==NIL){
				temp->show();
			}
			else{
				printListForm(temp);
			}
			std::cout<<" ";
			a=cdr(a);
		}
		if(isList(car(a))==NIL){
				car(a)->show();
			}
		else{
			printListForm(car(a));

		}
		std::cout<<")";	
	}
}

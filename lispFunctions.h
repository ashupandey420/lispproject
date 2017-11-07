#ifndef __LISPFUNCTIONS_INCLUDED__
#define __LISPFUNCTIONS_INCLUDED__
#include "SExp.h"

extern SExp* T;
extern SExp* NIL;
extern SExp* QUOTE;
extern SExp* COND;
extern SExp* DEFUN;
extern SExp* CAR;
extern SExp* CDR;
extern SExp* CONS;
extern SExp* ATOM;
extern SExp* NULL1;
extern SExp* lispConstants;
extern SExp* EQ;
extern SExp* INT;
extern SExp* PLUS;
extern SExp* MINUS;
extern SExp* TIMES;
extern SExp* QUOTIENT;
extern SExp* REMAINDER;
extern SExp* LESS;
extern SExp* GREATER;

SExp* car(SExp* );
SExp* cdr(SExp* );
SExp* cons(SExp* , SExp* );
SExp* atom(SExp* );
SExp* eq(SExp*, SExp*);
SExp* null(SExp* );
SExp* int1(SExp*);
SExp* plus(SExp*, SExp* );
SExp* minus(SExp*, SExp* );
SExp* times(SExp*, SExp* );
SExp* quotient(SExp*, SExp* );
SExp* remainder(SExp*, SExp* );
SExp* less(SExp*, SExp* );
SExp* greater(SExp*, SExp*);
SExp* equal(SExp*, SExp*);
SExp* in(SExp*, SExp*);
SExp* getVal(SExp*, SExp* );
SExp* eval(SExp*,SExp*);
SExp* isList(SExp* );
SExp* evcon(SExp*, SExp* );
SExp* isValidParams(SExp*);
SExp* isConstants(SExp*, SExp* );
SExp* evlis(SExp*, SExp* );
SExp* apply(SExp*, SExp*, SExp*);
SExp* addpairs(SExp*, SExp*,SExp*);
SExp* printListForm(SExp* );


#endif
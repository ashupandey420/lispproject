//SExp.h
#ifndef __SEXP_H_INCLUDED__
#define __SEXP_H_INCLUDED__
#include <iostream>
#include <stdint.h>
#include <string>
#include <list>
class SExp{
public:
	int type;
	int64_t  value;
	std::string name;
	SExp* left;
	SExp* right;
	bool isFun;
	SExp* funDef;
	static std::list <SExp*> idPointers;
	SExp();
	SExp(int64_t );
	SExp(std::string );
	SExp(SExp* l, SExp* r);
	void show();
	void showIdList();
	void changeToFun(SExp* );
};

//extern std::list <SExp*> SExp::idPointers;
/*extern SExp T("T");
extern SExp NIL("NIL");
extern SExp CAR("CAR");
extern SExp CDR("CDR");
extern SExp EQ("EQ");
extern SExp NULL1("NULL");
extern SExp ATOM("ATOM");
extern SExp COND("COND");
extern SExp DEFUN("DEFUN");
extern SExp CONS("CONS");
extern SExp QUOTE("QUOTE");*/




/*SExp* atom(SExp* s);

SExp* car(SExp* s);

SExp* eq(SExp* s);

SExp* cdr(SExp* s);

SExp* cons(SExp* l,SExp* r);*/
#endif


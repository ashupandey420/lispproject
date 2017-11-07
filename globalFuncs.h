#ifndef __GLOBAL_FUNCS_INCLUDED__
#define __GLOBAL_FUNCS_INCLUDED__
#include "SExp.h"
#include <stack>
#include "stackNode.h"
#include <cstdlib>
#include <list>
#include <string>
#include <stdint.h>

extern std::string error;

std::pair<bool,SExp*> doesExist(std::string tempStr);

SExp* parseInput(std::string input, SExp* NIL);

bool isvalidID(std::string a);

bool BothAreSpaces(char lhs, char rhs);

inline bool isInteger(const std::string & s);

std::string tab2Space(std::string input);

#endif

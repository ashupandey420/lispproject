/*AUTHOR: ASHUTOSH PANDEY
  EMAIL: pandey.99@osu.edu
  COURSE: CSE 6341
  FILE: main.cc*/

#include <iostream>
#include <string>
#include "SExp.h"
#include "globalFuncs.h"
#include "stackNode.h"
#include <algorithm>
#include "lispFunctions.h"
SExp* T;
SExp* NIL;
SExp* CAR;
SExp* CDR;
SExp* ATOM;
SExp* NULL1;
SExp* DEFUN;
SExp* COND;
SExp* QUOTE;
SExp* EQ;
SExp* CONS;
SExp* INT;
SExp* PLUS;
SExp* MINUS;
SExp* TIMES;
SExp* QUOTIENT;
SExp* REMAINDER;
SExp* LESS;
SExp* GREATER;
SExp* lispConstants;
int main(){
	
	T= new SExp("T");
	NIL= new SExp("NIL");
	CAR= new SExp("CAR");
	CDR= new SExp("CDR");
	ATOM= new SExp("ATOM");
	NULL1= new SExp("NULL");
	DEFUN= new SExp("DEFUN");
	COND= new SExp("COND");
	QUOTE= new SExp("QUOTE");
	EQ= new SExp("EQ");
	CONS= new SExp("CONS");
	INT= new SExp("INT");
	PLUS= new SExp("PLUS");
	MINUS= new SExp("MINUS");
	TIMES= new SExp("TIMES");
	QUOTIENT= new SExp("QUOTIENT");
	REMAINDER= new SExp("REMAINDER");
	LESS= new SExp("LESS");
	GREATER= new SExp("GREATER");
	int nConst=19;
	SExp* lispConstants1[]={T, NIL, CAR, CDR, ATOM, NULL1, DEFUN, COND, 
		QUOTE, EQ, CONS, INT, PLUS, MINUS, TIMES, QUOTIENT, REMAINDER, LESS, GREATER};
	lispConstants=NIL;
	for (int i =0;i<nConst;i++){
		SExp* temp =new SExp(lispConstants1[i],lispConstants);
		lispConstants=temp;
	}
	
	std::string line="";
	std::string input=" ";
	while (getline(std::cin, line))
	{
		
	    line=tab2Space(line);
		
	    if((line == "$") || (line=="$$")){
			std::string::iterator new_end = unique(input.begin(), input.end(), BothAreSpaces);
			input.erase(new_end, input.end()); 
		    	input.erase(remove(input.begin(), input.end(), '\n'),input.end());
			//input.erase(remove(input.begin(), input.end(), '\t'),input.end());
			if(input==" "){
				
				if(line=="$$"){
				    break;
				}
				continue;
			}
			
			try{
				//std::cout<<"Input:\n";
				SExp* inputS;
		    	inputS=parseInput(input,NIL);
		 		
		    	/*if(inputS!=NULL){
		    		if(isList(inputS)==T){
		    			printListForm(inputS);
		    		}
		    		else{
		    			inputS->show();
		    		}
		    		std::cout<<"\n\n";
		    	}*/
		    

			    try{
			    	//std::cout<<"Output:\n";
			    	SExp* outputS=eval(inputS,NIL);
			    	if(outputS!=NULL){
			    		if(isList(outputS)==T){
			    			printListForm(outputS);
			    		}
			    		else{
			    			outputS->show();
			    		}
			    		std::cout<<"\n";
			    	}
			    }
			    catch(std::string err_string){
			    	std::cout<<err_string<<"\n";
			    }
			}

			catch(std::string err_string){
			    std::cout<<err_string<<"\n";
			}
		    if (line == "$$"){
		    	break;
		    }
		    line="";
		    input="";
	   }
	  input=input+" "+line;
	    
	}

}

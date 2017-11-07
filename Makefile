main : main.o SExp.o globalFuncs.o stackNode.o lispFunctions.o
	g++ --std=c++0x -g -Wall main.o SExp.o globalFuncs.o stackNode.o lispFunctions.o -o main

main.o : main.cc SExp.h globalFuncs.h
	g++ --std=c++0x -g -c -Wall main.cc

SExp.o : SExp.cc SExp.h 
	g++ --std=c++0x -g -c -Wall SExp.cc

globalFuncs.o : globalFuncs.cc globalFuncs.h stackNode.h SExp.h
	g++ --std=c++0x -g -c -Wall globalFuncs.cc

stackNode.o : stackNode.cc stackNode.h SExp.h
	g++ --std=c++0x -g -c -Wall stackNode.cc

lispFunctions.o : lispFunctions.cc lispFunctions.h SExp.h
	g++ --std=c++0x -g -c -Wall lispFunctions.cc

clean:
	\rm *.o *~ main

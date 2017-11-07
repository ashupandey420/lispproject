# lispproject
* There are 5 source files:
  * globalFunc.cc
  * SExp.cc
  * stackNode.cc
 * main.cc
 * lispFunctions.cc
* 1 Makefile to compile each source file separately or together.  
 * on terminal type make  
 \> make
 * It will compile all source files and link them together to create a final executable file main.

* If you want to compile source files separately then type make sourcefilename.o  
 * \> make SExp.o
 * \> make stackNode.o
 * \> make main.o
 * \> make globalFuncs.o
 * \> make lispFunctions.o

* There is one clean command in Makefile. Type make clean. It will delete all object files and the main executable file.
 * \> make clean

* Use the executable main file to test this code. For example, if testcases are in file input.txt then
 * \>./main <input.txt  
 or  
 * \>cat input.txt | ./main

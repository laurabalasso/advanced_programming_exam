# Advanced programming exam: c++ project

This folder includes a tempate binary search tree implementation in c++ and some tests.

The folder  `src` contains the source code of the project: 
- the class implementation can be found in the file  `bst.h` together with the functions' definitions. 
- another simple struct Node is implemented in the file `node.h` which is included in `bst.h`.
-  in `main.cpp` some tests on binary search tree are implemented and executed. 

A brief report about the structure of the class and tests results is available. 
The performance test's results used to build the report's graphs can be found in the forlder `results_performance_test` . 

Code execution
- 
A Makefile is used to compile automatically the source code with the required flags. 
Just use the command `make` to compile: an executable named `bst` will be produced. 
Use the command `make clean` to remove the the file created.

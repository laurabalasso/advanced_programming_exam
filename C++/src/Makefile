SRC = main.cpp
EXE = bst
CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -Wextra
INC = bst.h node.h

all: $(EXE)


bst: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o bst

main.cpp: bst.h 
bst.h: node.h

format: $(SRC) $(INC)
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"

clean:
	rm -f $(EXE)

.PHONY: clean all format


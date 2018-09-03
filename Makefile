CXX=g++
CXXFLAGS=-std=c++14

all: result

result: AVLTree.o
	$(CXX) AVLTree.o -o result

AVLTree.o: AVLTree.cpp node.h avl.h
	$(CXX) -c AVLTree.cpp 

clean:
	rm -f *.o *.gch

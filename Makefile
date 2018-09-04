CXX=g++
CXXFLAGS=-std=c++1y

all: result

result: AVLTree.o
	$(CXX) AVLTree.o -o result

AVLTree.o: AVLTree.cpp node.h avl.h
	$(CXX) -c AVLTree.cpp $(CXXFLAGS)

clean:
	rm -f *.o *.gch

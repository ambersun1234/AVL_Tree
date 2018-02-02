all: result

result: AVLTree.o
	g++ AVLTree.o -o result

AVLTree.o: AVLTree.cpp node.h avl.h
	g++ -c AVLTree.cpp -std=c++14

clean::
	rm -f *.o *.gch

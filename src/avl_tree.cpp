#include <iostream>
#include <string>

#ifndef node_h
	#define node_h
	#include "node.h"
#endif

#ifndef avl_h
	#define avl_h
	#include "avl.h"
#endif

using namespace std;

void display( node< int > &record ) {
	cout << "   " << record.getData() << ',' << record.getHeight();
}

void menu() {
	cout << "a for add , r for remove , t for traversal , s for search" << endl << "c for clear tree , n for numberOfNodes , f for findPredecessor" << endl << "x for exit" << endl;
}

int main( int argc , const char *argv[] ) {
	AVLTree< int > myAVLTree;
	string command;
	int input;

	while ( true ) {
		menu();
		cout << "> ";
		cin >> command;

		if ( command == "a" || command == "A" ) { // done
			cout << "please enter the number for add: ";
			cin >> input;
			if ( myAVLTree.insertHelper( input ) ) cout << "add successfully" << endl;
			else cout << "add failed" << endl;
		}
		else if ( command == "c" || command == "C" ) {
			myAVLTree.clearTreeHelper();
			cout << "clear tree done" << endl;
		}
		else if ( command == "r" || command == "R" ) {
			cout << "please enter the number to remove: ";
			cin >> input;
			if ( myAVLTree.removeHelper( input ) ) cout << "removed successfully" << endl;
			else cout << "removed failed" << endl;
		}
		else if ( command == "f" || command == "F" ) {
			cout << "please enter the number to find: ";
			cin >> input;
			cout << "the predecessor is " << myAVLTree.findPredecessorHelper( input ) << endl;
		}
		else if ( command == "t" || command == "T" ) { // done
			cout << "inorder traversal:";
			myAVLTree.inorderTraversalHelper( display );
			cout << endl;
			cout << "preorder traversal:";
			myAVLTree.preorderTraversalHelper( display );
			cout << endl;
			cout << "postorder traversal:";
			myAVLTree.postorderTraversalHelper( display );
			cout << endl;
			cout << "levelorder traversal:";
			myAVLTree.levelorderTraversalHelper( display );
			cout << endl;
		}
		else if ( command == "n" || command == "N" ) { // done
			cout << "the AVL Tree contain " << myAVLTree.getNumberOfNodesHelper() << " nodes" << endl;
		}
		else if ( command == "s" || command == "S" ) { // done
			cout << "please enter the number to search: ";
			cin >> input;
			if ( myAVLTree.searchHelper( input ) ) cout << "target found" << endl;
			else cout << "failed to find target in the AVL Tree" << endl;
		}
		else if ( command == "x" || command == "X" ) {
			cout << "see you~~ bye~~" << endl;
			break;
		}
		else {
			cout << "input error , please enter the command again." << endl;
		}
		cout << endl;
	}
	return 0;
}

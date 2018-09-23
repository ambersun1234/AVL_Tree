#define avl_h

#include <queue>
#include <iostream>
#include <algorithm>
#include <climits>

#ifndef node_h
	#define node_h
	#include "node.h"
#endif

#include "gtest/gtest_prod.h"

using namespace std;

template< typename itemType >
class AVLTree {
	private:
		node< itemType > *root;
		node< itemType >* leftRotation( node< itemType > *up , node< itemType > *middle );
		node< itemType >* rightRotation( node< itemType > *up , node< itemType > *middle );
		FRIEND_TEST( avlTest , privateContent ); // must be in the same namespace

	protected:
		node< itemType >* findSmallestNode( node< itemType > *root , itemType &returnValue );
		node< itemType >* findSmallestNodeHelper( node< itemType > *root , itemType &returnValue );
		node< itemType >* insert( node< itemType > *root , node< itemType > *newNode );
		node< itemType >* remove( node< itemType > *root , itemType target );
		void clearTree( node< itemType > *root );
		void doRotation( node< itemType > *&root ); // move function
		bool search( node< itemType > *root , itemType target );
		int getNumberOfNodes( node< itemType > *root );
		itemType findPredecessor( node< itemType > *root , itemType target ) const;

		void inorderTraversal( node< itemType > *root , void visit( node< itemType > &record ) );
		void preorderTraversal( node< itemType > *root , void visit( node< itemType > &record ) );
		void postorderTraversal( node< itemType > *root , void visit( node< itemType > &record ) );
		void levelorderTraversal( node< itemType > *root , void visit( node< itemType > &record ) );
		int consanguinity( node< itemType > *root , int target1 , int target2 );

	public:
		AVLTree();
		~AVLTree();

		bool insertHelper( itemType newItem );
		bool removeHelper( itemType target );
		bool searchHelper( itemType target );
		void clearTreeHelper();
		int getNumberOfNodesHelper();
		itemType findPredecessorHelper( itemType target );
		int consanguinityHelper( int target1 , int target2 );

		void inorderTraversalHelper( void visit( node< itemType > &record ) );
		void preorderTraversalHelper( void visit( node< itemType > &record ) );
		void postorderTraversalHelper( void visit( node< itemType > &record ) );
		void levelorderTraversalHelper( void visit( node< itemType > &record ) );
};

template< typename itemType >
AVLTree< itemType >::AVLTree() {
	this->root = nullptr;
}

template< typename itemType >
AVLTree< itemType >::~AVLTree() {
	this->clearTree( this->root );
}

template< typename itemType >
node< itemType >* AVLTree< itemType >::leftRotation( node< itemType > *up , node< itemType > *middle ) {
	node< itemType > *temp = middle->getLeftChild();

	up->setRightChild( temp );
	middle->setLeftChild( up );

	up->setHeight( up->getMaxHeight() );
	middle->setHeight( middle->getMaxHeight() );

	return middle;
}

template< typename itemType >
node< itemType >* AVLTree< itemType >::rightRotation( node< itemType > *up , node< itemType > *middle ) {
	node< itemType > *temp = middle->getRightChild();

	up->setLeftChild( temp );
	middle->setRightChild( up );

	up->setHeight( up->getMaxHeight() );
	middle->setHeight( middle->getMaxHeight() );

	return middle;
}

template< typename itemType >
void AVLTree< itemType >::doRotation( node< itemType > *&root ) {
	int direction[ 2 ] = { 0 };
	node< itemType > *up = root , *middle , *down;
	// check for nullptr
	if ( up->getLeftChildHeight() > up->getRightChildHeight() ) {
		middle = up->getLeftChild();
		direction[ 0 ] = -1;
	}
	else {
		middle = up->getRightChild();
		direction[ 0 ] = 1;
	}

	if ( middle->getLeftChildHeight() > middle->getRightChildHeight() ) {
		down = middle->getLeftChild();
		direction[ 1 ] = -1;
	}
	else {
		down = middle->getRightChild();
		direction[ 1 ] = 1;
	}
	if ( direction[ 1 ] == 1 && direction[ 0 ] == 1 ) { // LL rotation
		root = this->leftRotation( up , middle );
	}
	else if ( direction[ 1 ] == -1 && direction[ 0 ] == -1 ) { // RR rotation
		root = this->rightRotation( up , middle );
	}
	else if ( direction[ 1 ] == 1 && direction[ 0 ] == -1 ) { // RL rotation
		middle = this->leftRotation( middle , down );
		up->setLeftChild( middle );

		root = this->rightRotation( up , middle );
	}
	else { // LR rotation
		middle = this->rightRotation( middle , down );
		up->setRightChild( middle );

		root = this->leftRotation( up , middle );
	}
}

template< typename itemType >
node< itemType >* AVLTree< itemType >::findSmallestNode( node< itemType > *root , itemType &returnValue ) {
	if ( root == nullptr ) return nullptr;

	if ( root->getRightChild() == nullptr ) {
		returnValue = root->getData();
		node< itemType > *temp = root->getLeftChild();

		delete root;
		root = nullptr;
		return temp;
	}
	root->setRightChild( this->findSmallestNode( root->getRightChild() , returnValue ) );
	if ( root != nullptr && root->unbalanced() ) this->doRotation( root );
	root->setHeight( root->getMaxHeight() );
	return root;
}

template< typename itemType >
node< itemType >* AVLTree< itemType >::findSmallestNodeHelper( node< itemType > *root , itemType &returnValue ) {
	root = root->getLeftChild();

	if ( root == nullptr ); // no smallest node found;
	else { // smallest node found
		itemType first = root->getData() , second = 0x3f3f3f3f;
		node< itemType > *temp = this->findSmallestNode( root->getRightChild() , second );

		root->setRightChild( temp );

		returnValue = first > second ? first : second;

		if ( root->unbalanced() ) this->doRotation( root );
		root->setHeight( root->getMaxHeight() );
	}
	return root;
}

template< typename itemType >
bool AVLTree< itemType >::searchHelper( itemType target ) {
	return this->search( this->root , target );
}

template< typename itemType >
bool AVLTree< itemType >::search( node< itemType > *root , itemType target ) {
	if ( root == nullptr ) return false;
	if ( root->getData() == target ) return true;

	if ( root->getData() > target ) return this->search( root->getLeftChild() , target );
	if ( root->getData() < target ) return this->search( root->getRightChild() , target );

	return false;
}

template< typename itemType >
itemType AVLTree< itemType >::findPredecessor( node< itemType > *root , itemType target ) const {
	if ( root == nullptr ) return INT_MIN;

	if ( root->getData() > target ) {
		return max( INT_MIN , findPredecessor( root->getLeftChild() , target ) );
	}
	else {
		return max( root->getData() , findPredecessor( root->getRightChild() , target ) );
	}
}

template< typename itemType >
itemType AVLTree< itemType >::findPredecessorHelper( itemType target ) {
	itemType temp = this->findPredecessor( this->root , target );

	return ( temp == INT_MIN ? target : temp );
}

template< typename itemType >
bool AVLTree< itemType >::insertHelper( itemType newItem ) {
	this->root = this->insert( this->root , new node< itemType >( newItem ) );
	return true;
}

template< typename itemType >
int AVLTree< itemType >::consanguinity( node< itemType > *root , int target1 , int target2 ) {
	if ( root == nullptr ) {
		return INT_MAX;
	}
	if ( root->getData() == target1 || root->getData() == target2 ) {
		return 0;
	}

	if ( root->getData() > target1 ) return 1 + this->consanguinity( root->getLeftChild() , target1 , target2 );
	if ( root->getData() < target1 ) return 1 + this->consanguinity( root->getRightChild() , target1 , target2 );

	if ( root->getData() > target2 ) return 1 + this->consanguinity( root->getLeftChild() , target1 , target2 );
	if ( root->getData() < target2 ) return 1 + this->consanguinity( root->getRightChild() , target1 , target2 );

}

template< typename itemType >
int AVLTree< itemType >::consanguinityHelper( int target1 , int target2 ) {
	return this->consanguinity( this->root , target1 , target2 );
}

template< typename itemType >
node< itemType >* AVLTree< itemType >::insert( node< itemType > *root , node< itemType > *newEntry ) {
	if ( root == nullptr ) return newEntry;

	if ( root->getData() > newEntry->getData() ) root->setLeftChild( this->insert( root->getLeftChild() , newEntry ) );
	else if ( root->getData() < newEntry->getData() ) root->setRightChild( this->insert( root->getRightChild() , newEntry ) );

	if ( root->unbalanced() ) {
		this->doRotation( root );
	}
	root->setHeight( root->getMaxHeight() );

	return root;
}

template< typename itemType >
bool AVLTree< itemType >::removeHelper( itemType target ) {
	this->root = this->remove( this->root , target );
	return true;
}

template< typename itemType >
node< itemType >* AVLTree< itemType >::remove( node< itemType > *root , itemType target ) {
	if ( root == nullptr ) return nullptr;

	if ( root->getData() == target ) { // target found
		if ( root->isLeaf() ) { // no children
			delete root;
			root = nullptr;
			return root;
		}
		else {
			itemType returnValue;
			node< itemType > *temp = this->findSmallestNodeHelper( root , returnValue );

			if ( temp == nullptr ) { // no smallest node found , but may have right children
				return root->getRightChild();
			}
			else { // smallest children found
				root->setLeftChild( temp );
				root->setData( returnValue );
				if ( root->unbalanced() ) this->doRotation( root );
				return root;
			}
		}
	}

	else if ( root->getData() > target ) root->setLeftChild( this->remove( root->getLeftChild() , target ) );
	else if ( root->getData() < target ) root->setRightChild( this->remove( root->getRightChild() , target ) );

	if ( root->unbalanced() ) this->doRotation( root );
	root->setHeight( root->getMaxHeight() );
	return root;
}

template< typename itemType >
void AVLTree< itemType >::clearTreeHelper() {
	this->clearTree( this->root );
	this->root = nullptr;
}

template< typename itemType >
void AVLTree< itemType >::clearTree( node< itemType >* root ) {
	if ( root == nullptr ) return;

	this->clearTree( root->getLeftChild() );
	this->clearTree( root->getRightChild() );

	delete root;
	root = nullptr;
}

template< typename itemType >
int AVLTree< itemType >::getNumberOfNodesHelper() {
	return this->getNumberOfNodes( this->root );
}

template< typename itemType >
int AVLTree< itemType >::getNumberOfNodes( node< itemType > *root ) {
	if ( root == nullptr ) return 0;
	return 1 + this->getNumberOfNodes( root->getLeftChild() ) + this->getNumberOfNodes( root->getRightChild() );
}

template< typename itemType >
void AVLTree< itemType >::inorderTraversalHelper( void visit( node< itemType > &record ) ) {
	this->inorderTraversal( this->root , visit );
}

template< typename itemType >
void AVLTree< itemType >::preorderTraversalHelper( void visit( node< itemType > &record ) ) {
	this->preorderTraversal( this->root , visit );
}

template< typename itemType >
void AVLTree< itemType >::postorderTraversalHelper( void visit( node< itemType > &record ) ) {
	this->postorderTraversal( this->root , visit );
}

template< typename itemType >
void AVLTree< itemType >::levelorderTraversalHelper( void visit( node< itemType > &record ) ) {
	this->levelorderTraversal( this->root , visit );
}

template< typename itemType >
void AVLTree< itemType >::inorderTraversal( node< itemType > *root , void visit( node< itemType > &record ) ) {
	if ( root == nullptr ) return;
	this->inorderTraversal( root->getLeftChild() , visit );
	visit( *root );
	this->inorderTraversal( root->getRightChild() , visit );
}

template< typename itemType >
void AVLTree< itemType >::preorderTraversal( node< itemType > *root , void visit( node< itemType > &record ) ) {
	if ( root == nullptr ) return;
	visit( *root );
	this->preorderTraversal( root->getLeftChild() , visit );
	this->preorderTraversal( root->getRightChild() , visit );
}

template< typename itemType >
void AVLTree< itemType >::postorderTraversal( node< itemType > *root , void visit( node< itemType > &record ) ) {
	if ( root == nullptr ) return;
	this->postorderTraversal( root->getLeftChild() , visit );
	this->postorderTraversal( root->getRightChild() , visit );
	visit( *root );
}

template< typename itemType >
void AVLTree< itemType >::levelorderTraversal( node< itemType > *root , void visit( node< itemType > &record ) ) {
	queue< node< itemType >* > myQueue;
	node< itemType > *temp;

	if ( root != nullptr ) myQueue.push( root );

	while ( !myQueue.empty() ) {
		temp = myQueue.front();
		myQueue.pop();

		visit( *temp );

		if ( temp->getLeftChild() != nullptr ) myQueue.push( temp->getLeftChild() );
		if ( temp->getRightChild() != nullptr ) myQueue.push( temp->getRightChild() );
	}
}

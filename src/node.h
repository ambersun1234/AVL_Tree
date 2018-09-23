#define node_h

template< typename itemType >
class node {
	private:
		itemType data;
		node< itemType > *left , *right;
		int height;

	public:
		node( itemType input );

		node< itemType >* getLeftChild();
		node< itemType >* getRightChild();
		itemType getData();
		int getHeight();
		int getLeftChildHeight();
		int getRightChildHeight();

		void setLeftChild( node< itemType > *pointer );
		void setRightChild( node< itemType > *pointer );
		void setData( itemType newItem );
		void setHeight( int h );

		bool isLeaf();
		int getMaxHeight();
		bool unbalanced();
};

template< typename itemType >
node< itemType >::node( itemType input ) {
	this->data = input;
	this->left = nullptr;
	this->right = nullptr;
	this->height = 1;
}

template< typename itemType >
node< itemType >* node< itemType >::getLeftChild() {
	return this->left;
}

template< typename itemType >
node< itemType >* node< itemType >::getRightChild() {
	return this->right;
}

template< typename itemType >
itemType node< itemType >::getData() {
	return this->data;
}

template< typename itemType >
int node< itemType >::getHeight() {
	return this->height;
}

template< typename itemType >
int node< itemType >::getLeftChildHeight() {
	int temp;

	if ( this->left == nullptr ) temp = 0;
	else temp = this->getLeftChild()->getHeight();

	return temp;
}

template< typename itemType >
int node< itemType >::getRightChildHeight() {
	int temp;

	if ( this->right == nullptr ) temp = 0;
	else temp = this->getRightChild()->getHeight();

	return temp;
}

template< typename itemType >
void node< itemType >::setLeftChild( node< itemType > *pointer ) {
	this->left = pointer;
}

template< typename itemType >
void node< itemType >::setRightChild( node< itemType > *pointer ) {
	this->right = pointer;
}

template< typename itemType >
void node< itemType >::setData( itemType newItem ) {
	this->data = newItem;
}

template< typename itemType >
void node< itemType >::setHeight( int h ) {
	this->height = h;
}

template< typename itemType >
bool node< itemType >::isLeaf() {
	return this->left == nullptr && this->right == nullptr;
}

template< typename itemType >
int node< itemType >::getMaxHeight() {
	int leftHeight , rightHeight;

	leftHeight = this->getLeftChildHeight();
	rightHeight = this->getRightChildHeight();

	return ( leftHeight > rightHeight ? leftHeight : rightHeight ) + 1;
}

template< typename itemType >
bool node< itemType >::unbalanced() {
	int ans = this->getLeftChildHeight() - this->getRightChildHeight();

	return abs( ans ) > 1;
}

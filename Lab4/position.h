/*
*File: position.h 

*Author: Kassidi Knight

*Purpose: The Position class declaration.
*/

#ifndef POSITION_H
#define POSITION_H


template<class T> class BinarySearchTree; // declaration for
//friend statement below

template<class T>
class Position {
public:
	Node<T>& operator*() const { return *nodePtr; } 
	
	Position parent() const { return Position<T>( this->nodePtr->parentPtr ); }
	
	Position left() const {
	return Position<T>( nodePtr->leftPtr ); }
	
	Position right() const {
	return Position<T>( nodePtr->rightPtr ); }
	
	// does this iterator point to real root?
	bool isRoot( ) const { return this->nodePtr->parentPtr->parentPtr == NULL; }
	
	bool isSuperRoot() const{
	// does this iterator point to fake superroot?
	return this->nodePtr->parentPtr == NULL; }
	
	bool isExternal() const { return this->nodePtr->leftPtr == NULL && this->nodePtr->rightPtr == NULL; }
	bool isInternal() const { return !(isExternal() ); }
	
	bool operator==( const Position& p ) {
	return this->nodePtr == p.nodePtr; }
	
	bool operator!=( const Position& p ) { return this->nodePtr != p.nodePtr; }
	
	Position& operator++( ); // inorder traversal
	
	T getItem() const { return nodePtr->item; }
	
	friend class BinarySearchTree<T>;
private:
	// only friends like BST can create positions from its nodes
	Position(): nodePtr(NULL) { }
	Position( Node<T>* );
	Node<T>* nodePtr;
	
};

/*
 * 
*/
template <class T>
Position<T>::Position( Node<T>* n ){
	
	nodePtr = n;
}


/* overloaded ++ returns an iterator that points to the next
* node in the tree, in-order traversal.
* Returns Position with NULL nodePtr if get to end of
* the tree in an in-order traversal
* Precondition: class T has overloaded operator<
*/
template<class T>
Position<T>& Position<T>::operator++() {
	
	//Position w = this’ right
	Position w = this->right();

	//2. if w is an internal node // like 80, so not a fake leaf
	if(w.isInternal()){
		do{
			*this = w;
			//move left
			w = w.left();
		//a. do // move left until w gets to a leaf
		//*this = w’s nodePtr
		//ii. w = w’s left
		//b. while w is internal // w is a fake leaf and this->77
		}while(w.isInternal());

		// since this followed w
	
		//else // w is external (a fake leaf), 85’s right fake node
	}else{
		//a. w = this’ parent // w = 80 so this will follow w up the tree
		w = this->parent(); 
		//b. while w’s nodePtr isn’t NULL (didn’t hit the superroot
		//yet which will happen as w goes up from 200, the last
		//node in the tree in-order) and *this is w’s right
		while(w.nodePtr != NULL && *this == w.right()){
			
			//i. *this = w // first loop iteration: this = 80;
			//second iteration this = 75
			*this = w;
			//ii. w = w’s parent // first loop iteration w = 75;
			w = w.parent();
		}
		
		//c. *this = w // this = 100, the next in-order
		*this = w; 
	}
	return *this;
}

#endif

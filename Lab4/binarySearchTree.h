/*
*File: binarySearchTree.h 

*Author: Kassidi Knight

*Purpose: The binary search tree class declaration. 
*/

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <cstdlib> 
#include <iostream> 
#include <algorithm> 
#include <iostream>


using std::max;
using std::cout;


// declaration for friend statement below
//template<class T> class Position;
//template<class T> class Node;

const int PREORDER = 1;
const int INORDER = 2;
const int POSTORDER = 3;

template<class T>
class BinarySearchTree {
public:
	BinarySearchTree();
	
	// returns num nodes in tree
	int size() const { return numNodes; }
	
	// returns true if tree empty of real nodes
	bool empty() const { return numNodes == 0; }
	
	// superroot right pointer always points to real root node
	Position<T> root() const { return Position<T>( superRootPtr->rightPtr ); }
	bool isSuperRoot( Position<T> p ) {return p.nodePtr == superRootPtr; }
	void traverseAndPrint(const Position<T>&, int);
	void preorderTraverseAndPrint(const Position<T>&) const;
	void inorderTraverseAndPrint(const Position<T>&) const;
	void postorderTraverseAndPrint(const Position<T>&) const;
	void preorderTraverseAndWrite(const Position<T>&, ostream&) const;
	
	int depth( const Position<T>& ) const;
	int height( const Position<T>& ) const;
	Position<T> begin() const;
	// returns NULL iterator
	Position<T> end() const { return Position<T>( ); }
	
	Position<T> find( const T& ) const;
	Position<T> insert( const T& );
	
	bool erase( const T& );
	bool erase( const Position<T>& );
	void addParticipant(Position<T>&); 
	
	virtual ~BinarySearchTree() { deleteUtility(superRootPtr); }
	//friend class Position<T>;
	//friend class Node<T>;
	
	BinarySearchTree<T>& operator=(const BinarySearchTree<T>&);
	BinarySearchTree(const BinarySearchTree<T>&);
private:
	Node<T>* superRootPtr;
	// number real nodes in tree, not including fake super
	// root and fake ends nodes
	int numNodes;
	
	// finds item in tree starting at position
	Position<T> findUtility( const T& item, const Position<T>& )
	const;
	// inserts item into tree
	Position<T> insertUtility( const T& item );
	
	// deletes all nodes in the tree
	void deleteUtility( Node<T>* );
	
	// erases just one node from the tree at position p
	Position<T> eraseUtility( const Position<T>& p);
	
	// insert item data at position p
	void expandExternal( const T& item, Position<T>& p);
	
	// remove node above fake leaf node at position p
	Position<T> removeAboveExternal( const Position<T>& p );
	//Is this the same as removeExternal?
	Node<T>* copyTree(Node<T>*, Node<T>*);
	
};

//Copy constructor
template<class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& b){
	numNodes = b.numNodes;
	superRootPtr = new Node<T>();
	if(b == NULL){
		superRootPtr->rightPtr = new Node<T>();
		superRootPtr->rightPtr->parentPtr = superRootPtr;
	}else{
		superRootPtr->rightPtr = copyTree(superRootPtr, b.superRootPtr->rightPtr);
	}
}

//operator=
template<class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& b){
	deleteUtility(this->superRootPtr); 
	numNodes = b.numNodes;
	superRootPtr = new Node<T>();
	if(b == NULL){
		superRootPtr->rightPtr = new Node<T>();
		superRootPtr->rightPtr->parentPtr = superRootPtr;
	}else{
		superRootPtr->rightPtr = copyTree(superRootPtr, b.superRootPtr->rightPtr);
	}
	
	return *this;
}

//Copy tree
template<class T>
Node<T>* BinarySearchTree<T>::copyTree(Node<T>* p, Node<T>* n){
	if(n != NULL){
		Node<T>* newNode = new Node<T>(*n);
		newNode->parentPtr = p;
		newNode->leftPtr = copyTree(newNode, n->leftPtr);
		newNode->rightPtr = copyTree(newNode, n->rightPtr);
		return newNode;
	}else{
		return NULL; 
	}
}


/* default ctor sets up an empty tree with two nodes:
* fake root whose right ptr points to fake end
*/
template<class T>
BinarySearchTree<T>::BinarySearchTree() {
	superRootPtr = new Node<T>();
	superRootPtr->rightPtr = new Node<T>();
	superRootPtr->rightPtr->parentPtr = superRootPtr;
	superRootPtr->leftPtr = NULL;
	numNodes = 0;
}


/* depth returns distance from root to node at parameter
* position
* Parameter:
* p position to compute depth of
* Returns depth or -1 if position p is superroot
*/
template<class T>
int BinarySearchTree<T>::depth( const Position<T>& p ) const {
	if ( p.isSuperRoot()) return -1;
	if ( p.isRoot()) return 0;
	else {
		return 1+depth( p.parent() );
	}
	
}



/* height returns distance from node at parameter position to
* lowest leaf
* Parameter: position to computer height of
*/
template<class T>
int BinarySearchTree<T>::height( const Position<T>& p ) const {
	// if leaf
	
	if ( p.isExternal() ) return 0;
		int h = 0;
	// h = max of 0 and height of left subtree
	h = max( h, height( Position<T>( p.nodePtr->leftPtr )));
	// h = max of height of left subtree and
	// height of right subtree
	h = max( h, height( Position<T>( p.nodePtr->rightPtr )));
	return 1 + h;
}




/* begin: returns position iterator to first node on tree - the
leftmost
*/
template<class T>
Position<T> BinarySearchTree<T>::begin() const {
	if ( numNodes > 0 ) {
		Position<T> p = root();
			while (p.isInternal()) {
				p = p.left();
			}
		return p.parent();
	}
	else return Position<T>( superRootPtr );
}



/* finds a T object in tree
* Parameters: the object to find
* Pre-condition: class T has overloaded operator==
* Returns iterator to object, superroot iterator if tree
* is empty, fake leaf postion if not found
*/
template<class T>
Position<T> BinarySearchTree<T>::find( const T& item ) const {
	if ( numNodes > 0 ) {
		Position<T> v = findUtility( item, root());
		return v;
	}
	else return Position<T>(superRootPtr);
}



/*
* to end nodes
* Parameters
* item to be inserted
* p fake end node where item will be inserted
* Precondition: p is an external node (a fake leaf) and
* class T has overloaded = operator
*/
template<class T>
void BinarySearchTree<T>::expandExternal( const T& item, Position<T>& p){
		
	//1. left = new Node
	Node<T>* leftPtr = new Node<T>();
	
	//2. right = new Node
	Node<T>* rightPtr = new Node<T>();
	
	//3. p.nodePtr’s leftPtr = left
	p.nodePtr->leftPtr = leftPtr;
	
	//4. p.nodePtr’s rightPtr = right
	p.nodePtr->rightPtr = rightPtr;
	
	//5. left’s parent = p.nodePtr
	leftPtr->parentPtr = p.nodePtr; 
	
	//6. right’s parent = p.nodePtr
	rightPtr->parentPtr = p.nodePtr; 
	
	//7. p.nodePtr’s item = item
	p.nodePtr->item = item;
	
	//8. numNodes++
	numNodes++; 
}


/* findUtility: recursive utility find function
* Parameters:
* item to look for
* p position to start looking from
* Pre-condition: class T has overloaded operator== and
* operator<, tree not empty of real nodes
* Returns position iterator where found or NULL iterator
*/
template <class T>
Position<T> BinarySearchTree<T>::findUtility( const T& item, const Position<T>& p ) const{
	
	//Check this function in tutoring 
	
	if(p.isExternal()){  
		return p;
	}else if(item == p.getItem()){
		return p; 
	}else if(item < p.getItem()){
		return findUtility(item, p.left());
	}else{
		return findUtility(item, p.right());
	}
	
/*
1. If the subroot, the current position, p, is external, then
we’ve hit a fake end node without finding the item, we’re
not going to find the item, so return the fake end node – a
base case to end the recursion.
2. If the item we’re looking for is equal to the item in the
subroot/position, p, parameter, then we’ve found the item so
return this position – another base case for recursion.
3. If the item we’re looking for is less than the item at p,
return what the call to findUtility with a position going
left returns
4. Otherwise return what the call to the findUtility with a
position going right returns
*/
	
}




/* insertUtility: inserts at position for new node
* Parameters: new node to insert
* Returns iterator to newly inserted object or to superRoot
* fake node if item already in tree
*/
template <class T>
Position<T> BinarySearchTree<T>::insertUtility( const T& item ){
	
	Position<T> foundPosition;
	
	foundPosition = findUtility( item, root() ); 
	//2. if foundPosition is a fake end node (then item not already in tree)
	if(foundPosition.isExternal()){
		expandExternal(item, foundPosition);
		return foundPosition;
	}else{
		//3. else return superRootPtr Position object because the item is
		//already in the tree
		return Position<T>(superRootPtr);
		//superRootPtr is already of type Position, 
		//why do we need Position<T>
	}
}


/* removeAboveExternal: removes internal node just above fake
leaf node pointed to by p. Decrements number of nodes
in tree.
Parameter
p leaf node of real node to delete
* Returns position iterator to sibling of node removed
*/
template <class T>
Position<T> BinarySearchTree<T>::removeAboveExternal( const Position<T>& p ){
	
	Node<T>* siblingPtr, *grandParentPtr;
	Node<T>* v, *w;
	
	//1. w = p’s nodePtr (so, w is a Node* and points to p’s node)
	w = p.nodePtr; 
	//2. v = p’s parent pointer (v points to the real node to delete)
	v = w->parentPtr; 
	//p is a position and does not have a parent pointer, but we've just put _Bool
	//it into w, which is of type node and does have a parentPtr
	
	//3. if w comes from the left of its parent
	if(w == v->leftPtr){
		//a. siblingPtr = v’s rightPtr (to set sibling of w)
		siblingPtr = v->rightPtr; 
	}else{
		//4. else
		//a. siblingPtr = v’s leftPtr
		siblingPtr = v->leftPtr; 
	}

	//5. if removing actual root (v is the superroot’s rightPtr)
	if(v == superRootPtr->rightPtr){
		
		//a. superroot’s rightPtr = siblingPtr
		//. siblingPtr’s parentPtr = superrootPtr
		superRootPtr->rightPtr = siblingPtr; 
		siblingPtr->parentPtr = superRootPtr; 
	}else{
		
		//6. else // removing a leaf that isn’t the actual root
		//a. grandparentPtr (of w and parent of v) = v’s parent
		grandParentPtr = v->parentPtr; 
		//b. if v, the real node to remove, is to the left of its parent 
		//if grandparentPtr’s leftPtr == v
		if(grandParentPtr->leftPtr == v ){
			grandParentPtr->leftPtr = siblingPtr; 
			//i. grandparent’s leftPtr = siblingPtr (put v’s
			//sibling in place of v)
		}else{ 
			//c. else // v is to the right of its parent
			//i. grandparent’s rightPtr = siblingPtr
			grandParentPtr->rightPtr = siblingPtr; 
			//d. siblingPtr’s parentPtr = grandparentPtr
		}	
		siblingPtr->parentPtr = grandParentPtr;
	}
	//7. delete w (fake end node)
	delete(w);
	//8. delete v (real node to delete)
	delete(v);
	//9. numNodes--
	numNodes--;
	//10. return Position of siblingPtr
	return Position<T>(siblingPtr); 
	
}


template <class T>
void BinarySearchTree<T>::deleteUtility( Node<T>* subroot ){

	//has to delete every node inc superroot and fakes
	//the base case cannot be asking if it's external, we 
	//want fake nodes deleted too
	//base case is if the subroot param is NULL 
	//if pointer is null, which is why we're passing a pointer 
	if(subroot != NULL){
		deleteUtility(subroot->leftPtr);
		deleteUtility(subroot->rightPtr); 
		delete subroot;
	}
	
}



/* inserts object T in the binary tree
  * Parameter: the object to insert
  * Pre-condition: class T has overloaded operator<
  * Returns iterator to newly inserted object or superRootPtr
  *    if item already in tree
  */
template<class T>
Position<T> BinarySearchTree<T>::insert( const T& item ){
    // root() = superroot's right ptr
    Position<T> p = insertUtility( item );
    // return iterator to position where new node inserted
    return p;
 }



/* erase removes a node above Position p
* Precondition position p is a valid position in tree
* Returns true if successful
*/
template<class T>
bool BinarySearchTree<T>::erase( const Position<T>& p ){
// can't remove superroot or fake external node
	if ( !p.isSuperRoot() && !p.isExternal() ) {
		eraseUtility( p );
		return true;
	}else{
		return false;
	}
}



/* erase removes a node above Position p
* Precondition position p is a valid position in tree
* Returns true if successful
*/
template<class T>
bool BinarySearchTree<T>::erase( const T& item ){
// can't remove superroot or fake external node
	Position<T> p = find( item );
	//if superroot, tree is empty, external is fake
	if ( !p.isSuperRoot() && !p.isExternal() ) {
		eraseUtility( p );
		return true;
	}else{
		return false;
	}
}


//MAY OR MAY NOT WORK //HELP
template<class T>
Position<T> BinarySearchTree<T>::eraseUtility(const Position<T>& p){

	Position<T> w, u;

	//1. if p has empty left subtree (points to a fake end node)
	if(p.left().isExternal()){
		//a. w = p’s fake/left node (fake leaf below node to erase)
		w = p.left();
	}

	//2. else if p has empty right subtree (points to a fake end node)
	else if(p.right().isExternal()){
		//a. w = p’s fake/right node
		w = p.right();
	}
	//3. else (case 3 – p has two, non-empty subtrees)
	else{
		w = p.right(); //don't want to change position p
		do{
			w = w.left();
		}while(w.isInternal());
		u = w.parent();
		p.nodePtr->item = u.getItem();
	}
	//call removeAboveExternal and pass it w, the fake leaf node that is below the node to delete
	removeAboveExternal(w);
	return p; 
}


template<class T>
void BinarySearchTree<T>::traverseAndPrint(const Position<T>& p, int type){
	//P IS THE ROOT OF THE SUBTREE
	if(type == PREORDER){
		preorderTraverseAndPrint(p);
	}else if(type == INORDER){
		inorderTraverseAndPrint(p);
	}else if(type == POSTORDER){
		postorderTraverseAndPrint(p);
	}
}



template<class T>
void BinarySearchTree<T>::preorderTraverseAndPrint(const Position<T>& p) const{

	if(p.isInternal()){
		cout << *p << " "; //should this be item?
		preorderTraverseAndPrint(p.left());
		preorderTraverseAndPrint(p.right());
	}	
}

template<class T>
void BinarySearchTree<T>::preorderTraverseAndWrite(const Position<T>& p, ostream& output) const{

	if(p.isInternal()){
		p.getItem().write(output);
		preorderTraverseAndWrite(p.left(), output);
		preorderTraverseAndWrite(p.right(), output);
	}	
}


template<class T>
void BinarySearchTree<T>::inorderTraverseAndPrint(const Position<T>& p) const{

	if(p.isInternal()){
		inorderTraverseAndPrint(p.left());
		cout << *p << " ";
		inorderTraverseAndPrint(p.right());
	}
	
}

template<class T>
void BinarySearchTree<T>::postorderTraverseAndPrint(const Position<T>& p) const{

	if(p.isInternal()){
		//should this be item?
		postorderTraverseAndPrint(p.left());
		postorderTraverseAndPrint(p.right());
		cout << *p << " ";
	}
	
}

#endif




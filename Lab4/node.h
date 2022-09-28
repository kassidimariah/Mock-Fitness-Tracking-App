/*
*File: node.h 

*Author: Kassidi Knight

*Purpose: Node class and some of its respective 
* 	functions.
*/

#ifndef NODE_H
#define NODE_H

#include <fstream>
using std::ostream;



template<class T> class BinarySearchTree; 
template<class T> class Position; 

template<class T>
class Node {
public:
	Node(); // default constuctor
	// constructor that takes node’s dat
	Node( const T& );
	// copy constructor.
	Node( const Node<T>& );
	virtual ~Node<T>() {} // destructor
	void setItem( const T& );
	T getItem() const { return item; }
	Node<T>& operator=( const Node<T>& );
	friend ostream& operator<<(ostream& out,  const Node<T> n) { out << n.item; }
	friend class BinarySearchTree<T>;
	friend class Position<T>; // Position is an iterator class
private:
	Node<T>* leftPtr;
	Node<T>* rightPtr;
	Node<T>* parentPtr;
	T item;
};


//Node default constructor
template<class T>
 Node<T>::Node() : leftPtr( NULL ), rightPtr( NULL ), parentPtr( NULL ) { }
	
	
//Copy constructor
//Parameters: A node
 template<class T>
 Node<T>::Node( const Node<T>& n ) { 
	*this = n;  
	leftPtr = NULL; 
	rightPtr = NULL;
	parentPtr = NULL;
}
	
template<class T>
void Node<T>::setItem( const T& i ) {this->item = i;}

//Operator=
//Parameters: A constant reference to a node
//Returns: this 
template<class T>
Node<T>& Node<T>::operator=( const Node<T>& n ){ 
	leftPtr = NULL; 
	rightPtr = NULL; 
	parentPtr = NULL;
	item = n.item; 
	return *this;
}


#endif
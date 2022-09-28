/*
 * File: Lab 4
 * Purpose: Fitness tracking
 * Author: Kassidi Knight
 * Creation date: 4/20/22
 * Last Lab for Prof. Arnold <3
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "node.h"
#include "position.h"
#include "participant.h"
#include "binarySearchTree.h"
#include "activity.h"

//int calcTotalMiles(Position& p); 

using namespace std;
void printMenu();
void getTrash();
double calcTotalMiles(BinarySearchTree<Participant>&);
void addParticipant(BinarySearchTree<Participant>&);
void removeParticipant(BinarySearchTree<Participant>&);
void removeParticipant(BinarySearchTree<Participant>&);
void addActivity(BinarySearchTree<Participant>&);

int main()
{
	
    ifstream in;
	ofstream out;
	char userChoice;
	BinarySearchTree<Participant> tree;
	Participant p;

    in.open( "tracking.bin", ios::in | ios::binary );

	if( !in.fail() ){ //Open failed, nonexistent file
		in.read( (char* )&p, sizeof( Participant ) );
		while( !in.eof() ) {
			p.setKey();
			p.calcParticipantMiles();
			tree.insert(p);
			in.read( (char* )&p, sizeof( Participant ) );
		}
		in.close();
	}
	cout << "Welcome to the Fitness Tracking System: ";

	do{
		printMenu();
		cin >> userChoice;
		getTrash();
		switch(userChoice){
			case '1': 
				cout << "\nRemove participant\n";
				//remove participant function
				removeParticipant(tree);
				break;

			case '2': 
				//add participant function 
				cout << "Add participant\n";
				addParticipant(tree);
				break;

			case '3': 
				cout << "Add activity\n";
				addActivity(tree);
				break;

			case '4': 
				cout << "Calculate total miles walked\n";
				cout << "Total miles walked by *everyone* = "<< calcTotalMiles(tree) << "!\n";
				break;

			case '5': 
				//pre-order print 
				cout << "Pre-order print\n";
				tree.traverseAndPrint(tree.root(), PREORDER);
				break;
			
			case '6': 
				cout << "Exit and save\n";
				out.open("tracking.bin", ios::out | ios::binary);
				tree.preorderTraverseAndWrite(tree.root(), out);
				out.close();
				break;

			default: 
				printf("Invalid choice, please select again.\n");
				break;
			
		}
		
	}while(userChoice != '6');

}

//Print menu
//No parameters
//Prints the menu
//Returns nothing
void printMenu(){
	cout << "\n 1 Remove participant \n 2 Add participant \n 3 Add activity \n 4 Calculate total miles walked \n 5 Pre-order print \n 6 Exit and save \n Option: ";
}

//getTrash
//Void, no parameters
//Cleans up input
void getTrash(){
	char temp[500];
	cin.getline(temp, 500);
}


//addParticipant 
//Parameters: A BST
//Returns nothing 
void addParticipant(BinarySearchTree<Participant>& tree){
	
	Participant p;
	char temp[500];
	double inches;
	
	cout << "First name: ";
	cin >> temp;
	getTrash();
	p.setFirst(temp);
	cout << "Last name: "; 
	cin >> temp;
	getTrash();
	p.setLast(temp);
	p.setKey();
	p.fixName();
	Position<Participant> pos = tree.find(p);
	
	if(pos.isInternal()){
		p.getFirst(temp);
		cout << temp << " ";
		p.getLast(temp);
		cout << temp << " ";
		cout << "is already a participant.\n";
	}else{
		cout << "Height in inches: " ;
		cin >> inches;
		p.setHeight(inches);
		tree.insert(p);
		p.getFirst(temp);
		cout << temp << " ";
		p.getLast(temp);
		cout << temp << " ";
		cout << "has been added.\n";
 
	}
	
}

//removeParticipant
//Parameter: a BST
//Returns nothing 
void removeParticipant(BinarySearchTree<Participant>& tree){
	
	Participant p;
	char temp[500];
	
	cout << "First name: ";
	cin >> temp;
	getTrash();
	p.setFirst(temp);
	cout << "Last name: "; 
	cin >> temp;
	getTrash();
	p.setLast(temp);
	p.setKey();
	p.fixName();
	Position<Participant> pos = tree.find(p);
	if(pos.isInternal()){
		p = pos.getItem();
		p.getFirst(temp);
		cout << "Participant " << temp << " ";
		p.getLast(temp);
		cout << temp;
		cout << ", " << p.getTotalMiles() << " total miles walked removed.\n"; 
		tree.erase(p);
		
	}else{
		p.getFirst(temp);
		cout << temp << " ";
		p.getLast(temp);
		cout << temp << " is not a participant.\n";
	}
	
}

//calcTotalMiles
//Parameters: A binary search tree
//Returns: A double value for the total miles
double calcTotalMiles(BinarySearchTree<Participant>& b){
	double totalMiles;
	Position<Participant> pos = b.begin();
	for( ; pos != b.end(); ++pos){
		totalMiles += pos.getItem().getTotalMiles();
	}
	return totalMiles;
}

//addActivity
//Parameters: a BST
//Returns nothing
void addActivity(BinarySearchTree<Participant>& tree){
	Participant p;
	Activity a; 
	char temp[500];
	int act, mins;
	
	cout << "First name: ";
	cin >> temp;
	getTrash();
	p.setFirst(temp);
	cout << "Last name: "; 
	cin >> temp;
	getTrash();
	p.setLast(temp);
	p.setKey();
	p.fixName();
	Position<Participant> pos = tree.find(p);
	if(pos.isInternal()){
		p = pos.getItem();
		cout << "Activity: ";
		cin >> act;
		getTrash();
		a.setCode(act);
		p.getActivity(act);
		cout << "Minutes: ";
		cin >> mins;
		getTrash();
		a.setMinutes(mins);
		p.addActivity(a);
		tree.erase(p);
		tree.insert(p);
		cout << "Added ";
		p.getFirst(temp);
		cout << temp;
		p.getLast(temp);
		cout << " " << temp << ", " << ACTIVITY_NAMES[act] << ", " << mins << " minutes = " << a.returnMiles(p.getHeight()) << " miles.\n";
		
	}else{
		p.getFirst(temp);
		cout << temp << " ";
		p.getLast(temp);
		cout << temp << " is not a participant.\n";
	}
	
}

//File: participant.cpp
//Author: Kassidi Knight
//Purpose: The Participant class's functions, 
//declared in participant.h
#include "participant.h"
#include "activity.h"
#include <cstring>

//default constructor 
Participant::Participant() {
	firstName[0] = '\0';
	lastName[0] = '\0';
	height = 0;
	numAct = 0;
	key[0] = '\0';
}

//addActivity
//Parameters: a, the activity to add
//Returns nothing
void Participant::addActivity( const Activity& a ) {
	this->activities[numAct] = a;
	numAct++; 
	totalMiles += a.returnMiles(height);
}

//operator<
//Parameters: a and b, the activites to commpare
//returns their comparison
bool operator<(const Participant& a, const Participant& b){
	//compare concatenated names 
	return( strcmp(a.key, b.key) < 0 );	
}

//operator==
//Parameters: the two participants to be compared
//returns their comparison, true or false
bool operator==( const Participant& a, const Participant& b){
	//compare concatenated names
	return( strcmp(a.key, b.key) == 0 );		
}

//setFirst
//Parameters: n, a char pointer
//sets the participant's first name 
//returns nothing 
void Participant::setFirst( char* n ){
	strcpy(firstName, n);
}

//setLast 
//Parameters: n, a char pointer
//sets the participant's last name 
//returns nothing
void Participant::setLast( char* n ){
	strcpy(lastName, n); 
}

//setHeight 
//Parameters: n, a double
//sets the participant's height
//returns nothing
void Participant::setHeight( double n ){
	this->height = n; 
}

//setNumAct
//Parameters: n, an integer
//sets the participant's number of activities 
//returns nothing
void Participant::setNumAct( int n ){
	this->numAct = n; 
}

//setKey
//sets the key
//returns nothing
void Participant::setKey( ){
	strcpy(key, lastName);
	strcat(key, firstName);
	for(int i = 0; i < strlen(key); i++){
		key[i] = tolower(key[i]);
	}
}

//setTotalMiles 
//sets the total miles 
//returns nothing
void Participant::setTotalMiles(double n){
	this->totalMiles = n;
}

//getFirst
//Parameters: a character array
//gets the participant's first name
//returns nothing 
void Participant::getFirst( char temp[] ) const{
	strcpy( temp, firstName );
}

//getLast
//Parameters: a character array
//gets the participant's last name
//returns nothing 
void Participant::getLast( char temp[] ) const{
	strcpy( temp, lastName ); 
}

//operator<<
//Parameters: the outstream, out, and a Participant, p
//Returns nothing 
ostream& operator<<(ostream& out, const Participant& p){
	out << p.firstName << " " << p.lastName << " " << p.totalMiles << "\n"; 
	
}

//calcParticipantMiles
//No parameters
//Calculates an indiviual participant's miles
void Participant::calcParticipantMiles(){
	
	totalMiles = 0;
	for(int i = 0; i < numAct; i++){
		 totalMiles += activities[i].returnMiles(height);
	}
}

//fixName
//No parameters
//Returns nothing
//Fixes the input name using 
//toupper and tolower
void Participant::fixName(){
	firstName[0] = toupper(firstName[0]);
	for(int i = 1; i < strlen(firstName); i++){
		firstName[i] = tolower(firstName[i]);
	}
	
	lastName[0] = toupper(lastName[0]);
	for(int i = 1; i < strlen(lastName); i++){
		lastName[i] = tolower(lastName[i]);
	}
}

//write
//Parameters: the output streamm
//Returns nothing 
void Participant::write(ostream& output) const{
	output.write( (char* )this, sizeof( Participant ) );
}
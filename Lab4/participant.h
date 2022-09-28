/*
*File: participant.h 

*Author: Kassidi Knight

*Purpose: The Participant class declaration.
*/

#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include "activity.h"

#include <fstream>
using std::ostream;

const int MAX_NAME_LENGTH = 30;
const int MAX_ACTIVITES = 365;

class Participant {
	
public:
	
	Participant();
	//need set and get functions 
	void setFirst( char* );
	void setLast( char* ); 
	void getFirst( char* ) const;
	void getLast( char* ) const;
	
	Activity getActivity( int index ) const { return activities[index]; }
	void addActivity( const Activity& a );
	void setHeight( double );
	void setNumAct( int ); 
	void setTotalMiles( double ); 
	void setKey( );
	void fixName();
	
	
	double getHeight() const { return height; }
	int getNumAct() const { return numAct; } 
	double getTotalMiles() const { return totalMiles; } 
	void calcParticipantMiles();
	void write(ostream&) const;
	
	friend bool operator<( const Participant&, const Participant& );
	friend bool operator==( const Participant&, const Participant& ); 
	friend ostream& operator<<(ostream&, const Participant&);

private: 
	char firstName[MAX_NAME_LENGTH];
	char lastName[MAX_NAME_LENGTH]; 
	double height;
	Activity activities[MAX_ACTIVITES];
	int numAct; 
	double totalMiles = 0;
	char key[MAX_NAME_LENGTH * 2];

}; 

#endif 

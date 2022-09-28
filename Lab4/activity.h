/*
*File: activity.h 

*Author: Kassidi Knight 

*Purpose: The Activity class declaration.
*/

#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <fstream>
#include <string> 
using std::string; 
using std::ostream;

const string ACTIVITY_NAMES[] = { "Assembly line", "Basketball shooting", "Basketball game", "Bicycling 10 mph", 
		"Bicycling", "Cooking", "Dance", "Football", "Hiking", "House Cleaning", "Gardening", "Miniature golf", 
		"Racquetball", "Rowing", "Running 6 mph", "Running 7 mph", "Running 8 mph", "Shopping", "Soccer", 
		"Softball", "Stairs", "Swimming Laps", "Tennis", "Walking 3 mph", "Walking 4 mph", "Weight lifting", 
		"Yoga" };

class Activity {
	
public:
	static const int STEPS[]; 
	
	Activity();
	void setCode( const int );
	int getCode() const { return code; }
	void setMinutes( const int );
	int getMinutes() const { return minutes; }
	double returnMiles( double height ) const;

private: 
	int code;
	int minutes;

}; 

#endif 

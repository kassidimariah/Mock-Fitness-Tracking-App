/*
 * FIle: activity.cpp
 * Author: Kassidi Knight
 * Purpose: Functions for the Activity
 * 	class in activity.h
 */

#include "activity.h"

#include <string> 
using std::string;

	enum activityEnum{ ASSEMBLY_LINE, BASKETBALL_SHOOTING, BASKETBALL_GAME, BICYCLYING_10MPH, BICYCLING, COOKING, DANCE, 
		FOOTBALL, HIKING, HOUSE_CLEANING, GARDENING, MINIATURE_GOLF, RACQUETBALL, ROWING, RUNNING_6MPH, RUNNING_7MPH, 
		RUNNING_8MPH, SHOPPING, SOCCER, SOFTBALL, STAIRS, SWIMMING_LAPS, TENNIS, WALKING_3MPH, WALKING_4MPH, 
		WEIGHT_LIFTING, YOGA };
	
	//27 activities total, array 0-26
	
	const int Activity::STEPS[] = { 85, 136, 242, 121, 242, 61, 167, 242, 182, 91, 99, 91, 212, 212, 303, 348, 409, 70, 212,
	152, 273, 212, 212, 100, 152, 121, 76 };
	
	
//default constructor 
Activity::Activity() {
	code = 0;
	minutes = 0; 
}

//setItem function

//Function that returns the miles equivalent of the activity
double Activity::returnMiles( double height ) const{
	
	double distance, numSteps;
	numSteps = minutes * STEPS[code];
	// f = (0.413 * height in inches ) / 12
	distance = (0.413 * height) / 12; 
	distance *= numSteps;
	distance /= 5280; 
	return distance;
	
}

//setCode
//Parameters: an integer
//sets the code to this
void Activity::setCode(int c ){
	if(c >= ASSEMBLY_LINE && c <= YOGA){
		this->code = c;
	} 
}

//setMinutes
//Parameters: an integer
//sets the minutes to this
void Activity::setMinutes( int m ){
		if(m >= 0){
			this->minutes = m; 
		}
}


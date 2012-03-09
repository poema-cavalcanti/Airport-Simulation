#include <iostream>
#include "Plane.h"

// DEFAULT CONSTRUCTOR
Plane::Plane()
{
	id = 0;
	landing = false;
	priority = 2;
	minutes_waiting = 0;
	landingTime = 0;
	takeOffTime = 0;
}

/******************************************************************
	PLANE ( INT , BOOL , INT )
	Constructor takes in three parameters which are used to set:
	- id
	- landing
	- landingTime (if landing)
	- takeOffTime (if !landing)
	That information is used to determine priority
	1 - if landing
	2 - if !landing
******************************************************************/
Plane::Plane(int ident, bool land, int land_takeOff_time)
{
	id = ident;
	landing = land;
	minutes_waiting = 0;
	if (landing){
		landingTime = land_takeOff_time;
		priority = 1;
	}
	else{
		takeOffTime = land_takeOff_time;
		priority = 2;
	}
}

/********************************************************************
	VOID UPDATE ( )

	increments minutes_waiting.

	if the plane is waiting to take off and is 20 minutes away to
	reaching the 3 hour mark, it's priority is udated to highest
	priority.
********************************************************************/
void Plane::update()
{
	minutes_waiting++;

	if ((priority == 2) && (minutes_waiting >= 160)) {
		priority = 0;
	}

	return;
}

// INT GET_MINUTES_WAITING ( )
int Plane::get_minutes_waiting() const
{
	return minutes_waiting;
}

// INT GET_PRIORITY ( )
int Plane::get_priority() const
{
	return priority;
}

// INT GET_TIME ( )
int Plane::get_time() const
{
	if (landing)
		return landingTime;
	else
		return takeOffTime;
}

// BOOL IS_LANDING ( )
bool Plane::is_landing() const
{
	return landing;
}

// ASSIGNMENT OPERATOR OVERLOAD
const Plane & Plane::operator=(const Plane & rhs)
{
	id = rhs.id;
	landing = rhs.landing;
	priority = rhs.priority;
	minutes_waiting = rhs.minutes_waiting;
	landingTime = rhs.landingTime;
	takeOffTime = rhs.takeOffTime;

	return *this;
}

// OUT STREAM << OPERATOR OVERLOAD
ostream &operator << (ostream &out, const Plane &P) 
{
	out << "Plane " << P.id << " was in queue for " ;
	if (P.landing)
		out << "landing " ;
	else
		out << "take off " ;
	out << "for " << P.minutes_waiting << " minutes" ;

	return out;
}
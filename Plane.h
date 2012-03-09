/********************************************************************************
*	Title: Plane.h																*
*	Abstract: This class creates a Plane object that stores information about	*
*			  the plane and provides functions to alter and access the info.	*
*	Author: Poema Cavalcanti													*
*	Date: 12/11/2011															*
********************************************************************************/

#include <iostream>
using namespace std;

#ifndef PLANE
#define PLANE

class Plane
{
private:
	int id; // identification number
	bool landing; // true if the plane is landing, false otherwise
	int priority; // 0 - highest priority, 1 - second highest priority, 2 - lowest priority
	int minutes_waiting; // number of minutes plane has been waiting for access to the runway
	int landingTime; // number of minutes the plane takes to land
	int takeOffTime; // number of minutes the plane takes to take off
public:
	Plane(); // default constructor
	Plane(int ident, bool land, int land_takeOff_time); 

	void update(); // updates minutes_waiting and if necessary priority
	int get_minutes_waiting() const; // returns value of minutes_waiting
	int get_priority() const; // returns value of private variable priority
	int get_time() const; // returns landingTime if plane is landing, takeOffTime otherwise
	bool is_landing() const; // returns value of landing

	friend ostream &operator << (ostream &out, const Plane &P); 
	const Plane &operator= (const Plane & rhs);
};

#endif
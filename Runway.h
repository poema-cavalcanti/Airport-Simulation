/****************************************************************************
*	Title: Runway.h															*
*	Abstract: This class creates a Runway object that is used to store:		*
*			  - boolean value for runway availability						*
*			  - integer value that counts down to when the runway will		*
*			    be available												*
*			  - the plane currently on the runway							*
*			  - priority table of plane queues that require access to the	*
*			    runway														*
*			  Priority determination:										*
*			  0 - Planes that have been waiting to take off for near to		*
*			      three hours (highest priority)							*				
*			  1 - Planes that need to land (second highest priority)		*	
*			  2 - Planes waiting to take off for less than three hours		*
*			      (lowest priority)											*				
*	Author: Poema Cavalcanti												*
*	Date: 12/12/2011														*
****************************************************************************/

#include <iostream>
using namespace std;

#include "Plane.h"
#include "LLQueue.h"

#ifndef RUNWAY
#define RUNWAY

const int PRIORITIES = 3;

class Runway
{
private:
	bool free; // true if time_until_free = 0, false otherwise
	int time_until_free; // time a plane will use the runway to land or take off
	LLQueue<Plane> planes[PRIORITIES]; // Priority table of Plane queues
	Plane onRunway; // Plane currently on runway
public:
	Runway(); // default constructor
	bool empty(); // returns true if all queues in planes[] are empty
	bool is_free(); // returns value of private variable free
	void insert(int id_num, bool land, int time); // uses parameters to insert a new plane to planes[]
	bool remove(); // true if plane is removed from planes[] and occupies the runway, false otherwise
	bool update(); // false if empty(), updates and returns true otherwise
	int landing_size() const; // returns size of landing queue
	int take_off_size() const; // returns size of take off queues
	int wait() const; // returns time_until_free
	bool landing() const; // returns true if onRunway is landing, false otherwise
	void print(ostream &out) const;
};

#endif
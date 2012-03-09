#include "Runway.h"

// DEFAULT CONSTRUCTOR
Runway::Runway()
{
	free = true;
	time_until_free = 0;
}

// BOOL EMPTY ( )
bool Runway::empty()
{
	for (int i = 0; i < PRIORITIES; i++)
	{
		if (!(planes[i].empty()))
			return false;
	}
	return true;
}

// BOOL IS_FREE ( )
bool Runway::is_free()
{
	return free;
}

// VOID INSERT ( INT , BOOL , INT )
void Runway::insert(int id_num, bool land, int time)
{
	Plane p(id_num,land,time); // creates a Plane object p and assigns a priority.
	planes[p.get_priority()].enqueue(p); // p is inserted in planes[] at the index of its priority
}

// BOOL REMOVE ( )
bool Runway::remove()
{
	if (!free) // if there is already a plane using the runway no planes can be removed from planes[]
		return false;
	if (empty()) // no planes can be removed from planes[]
		return false;

	for (int i = 0; i < PRIORITIES; i++) // starts with highest priority queue
	{
		if (!(planes[i].empty())) // if queue has planes, dequeue plane.
		{
			onRunway = planes[i].front();
			planes[i].dequeue();
			free = false;
			time_until_free = onRunway.get_time();
			return true;
		}
	}

	return false; // if for any reason the code reaches this point returns false
}

/***************************************************** 
	BOOL UPDATE ( )

	This function always checks to update:
	- free (when !free)
	- time_until_free (when !free)

	If planes[] is empty, function returns false.

	Otherwise, all non empty queues are updated.
	If a plane has changed its priority to 0, that
	plane is enqueued in planes[0] and dequeued
	from its current queue.

	Function returns true.
*****************************************************/
bool Runway::update()
{
	if (!free) { 
		time_until_free--; // update time_until_free
		if (time_until_free == 0) {
			free = true; // update free
		}
	}

	if (empty()) // check if empty
		return false;

	for (int i = 0; i < PRIORITIES; i++) {
		if (!(planes[i].empty())) {
			planes[i].updateQueue(); // update queues to reflect time passage
		}
	}
	if (((planes[2].front()).get_priority()) == 0) {
		planes[0].enqueue(planes[2].front()); // update queues based on priority changes
		planes[2].dequeue();
	}
	return true;
}

// INT LANDING_SIZE ( )
int Runway::landing_size() const
{
	return (planes[1].size()); // priority 1 is only given to planes that need to land
}

// INT TAKE_OFF_SIZE ( )
int Runway::take_off_size() const
{
	return ((planes[0].size()) + (planes[2].size())); // priority 0 and 2 are only given to planes needing to take off
}

// INT WAIT ( )
int Runway::wait() const
{
	return (onRunway.get_minutes_waiting());
}

// BOOL LANDING ( )
bool Runway::landing() const
{
	return (onRunway.is_landing());
}
/***********************************************
	VOID PRINT ( OSTREAM & )
	Outputs:
	- Plane on the runway (when !free)
	- Take-off queue information
		- size
		- wait time of first plane in queue
	- Landing queue information
		- size
		- wait time of first plane in queue
***********************************************/
void Runway::print(ostream &out) const
{
	if (!free) {
		out << onRunway << " is now on the runway.\n" ;
		if (onRunway.is_landing()) {
			out << "The runway will be free after the plane lands in " << time_until_free << " minutes.\n" ;
		}
		else {
			out << "The runway will be free after the plane takes off in " << time_until_free << " minutes.\n" ;
		}
	}

	out << "\nTake-off queue:\n"
		<< "There are " << (planes[0].size() + planes[2].size()) << " planes in the take-off queue.\n"
		<< "The first plane in the take-off queue has been waiting for " ;
	if (planes[0].empty()) {
		if (!planes[2].empty())
			out << (planes[2].front()).get_minutes_waiting() << " minutes.\n" ;
		else
			out << "0 minutes.\n" ;
	}
	else {
		out << (planes[0].front()).get_minutes_waiting() << " minutes.\n" ;
	}

	out << "\nLanding queue:\n"
		<< "There are " << (planes[1].size()) << " in the landing queue.\n"
		<< "The first plane in the landing queue has been waiting for " ;
	if (planes[1].empty()) {
		out << "0 minutes.\n" ;
	}
	else {
		out << (planes[1].front()).get_minutes_waiting() << " minutes.\n" ;
	}
}
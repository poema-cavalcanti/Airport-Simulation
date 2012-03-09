/****************************************************************************
*	Title: Report.h															*
*	Abstract: This class stores information from the airport simulation		*
*			  and prints and calculates averages associated with program	*
*			  operations.													*
*	Author: Poema Cavalcanti												*
*	Date: 12/11/2011														*
****************************************************************************/

#include <iostream>
using namespace std;

#ifndef REPORT
#define REPORT

class Report
{
private:
	int take_offs; // stores total number of take offs
	int landings; // stores total number of landings
	int avg_landing_queue_size; // stores the sum of landing queue sizes
	int avg_takeOff_queue_size; // stores the sum of takeOff queue sizes
	int minutes_to_land; // stores the sum of the minutes that planes that have landed waited to use the runway
	int minutes_to_takeOff; // stores the sum of the minutes that planes that have taken off waited to use the runway
	int time; 
public:
	Report(); // default constructor
	void increment_time(); // updates time
	void increase_takeOffs(int wait); // updates take_offs and minutes_to_takeOff
	void increase_landings(int wait); // updates landings and minutes_to_land
	void update_landing_size(int size); // updates avg_landing_queue_size
	void update_takeOff_size(int size); // updates avg_takeOff_queue_size
	void print(ostream &out) const;
	void print_averages(ostream &out) const;
};

#endif

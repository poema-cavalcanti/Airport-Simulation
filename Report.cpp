#include "Report.h"

/*****************************************************
	Default Constructor: initializes all variables
						 to zero.
*****************************************************/
Report::Report()
{
	take_offs = 0;
	landings = 0;
	avg_landing_queue_size = 0;
	avg_takeOff_queue_size = 0;
	minutes_to_land = 0;
	minutes_to_takeOff = 0;
	time = 0;
}

/************************************
	VOID INCREMENT_TIME()
	adds one to the time variable.
************************************/
void Report::increment_time()
{
	time++;
}

/************************************************************
	VOID INCREASE_TAKEOFFS(INT)
	adds one to the take_offs variable and adds the value 
	of the funtion parameter to minutes_to_takeOff. When
	minutes_to_takeOff is divided by take_offs we have the
	average number of minutes a plane waits to take off.
************************************************************/
void Report::increase_takeOffs(int wait)
{
	take_offs++;
	minutes_to_takeOff += wait;
}

/************************************************************
	VOID INCREASE_LANDINGS(INT)
	adds one to the landings variable and adds the value 
	of the funtion parameter to minutes_to_land. When
	minutes_to_land is divided by landings we have the
	average number of minutes a plane waits to land.
************************************************************/
void Report::increase_landings(int wait)
{
	landings++;
	minutes_to_land += wait;
}

/************************************************************
	VOID UPDATE_LANDING_SIZE(INT)
	adds parameter value to avg_landing_queue_size. When
	avg_landing_queue_size is divided by time we have the
	average landing queue size.
************************************************************/
void Report::update_landing_size(int size)
{
	avg_landing_queue_size += size;
}

/************************************************************
	VOID UPDATE_TAKEOFF_SIZE(INT)
	adds parameter value to avg_takeOff_queue_size. When
	avg_takeOff_queue_size is divided by time we have the
	average take off queue size.
************************************************************/
void Report::update_takeOff_size(int size)
{
	avg_takeOff_queue_size += size;
}

/**********************************************************
	VOID PRINT(OSTREAM&)
	displays the total number of planes that have taken
	off and the total number of planes that have landed.
**********************************************************/
void Report::print(ostream &out) const
{
	out << take_offs << " planes have taken off.\n"
		<< landings << " planes have landed." << endl;
}

/**********************************************************
	VOID PRINT_AVERAGES(OSTREAM&)
	displays the total number of planes that have taken
	off and the total number of planes that have landed
	displays the average queue sizes and average waiting
	times for planes taking off and landing
**********************************************************/
void Report::print_averages(ostream &out) const
{
	out << take_offs << " planes have taken off.\n"
		<< landings << " planes have landed.\n"
		<< "Average queue size: " << (avg_takeOff_queue_size + avg_landing_queue_size) / time
		<< "\nAverage landing queue size: " << avg_landing_queue_size / time
		<< "\nAverage take-off queue size: " << avg_takeOff_queue_size / time ;
	if ((landings + take_offs) != 0)
		out << "\nAverage waiting time: " << (minutes_to_land + minutes_to_takeOff) / (landings + take_offs);
	else
		out << "\nAverage waiting time: " << (minutes_to_land + minutes_to_takeOff);
	if (landings != 0)
		out << "\nAverage wait to land: " << minutes_to_land / landings ;
	else
		out << "\nAverage wait to land: " << minutes_to_land ;
	if (take_offs != 0)
		out << "\nAverage wait to take off: " << minutes_to_takeOff / take_offs ;
	else
		out << "\nAverage wait to take off: " << minutes_to_takeOff ;

	out	<< endl;
}
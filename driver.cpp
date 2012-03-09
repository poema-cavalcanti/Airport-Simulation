/****************************************************************************************
*	Title: driver.cpp																	*
*	Abstract: This file contains the main() function that uses the Runway and Report	*
*			  classes to simulate an airport's operation.								*
*																						*
*			  Airport Properties:														*
*			  - Only one runway is in operation											*
*			  - Every hour avgLanding planes land										*
*			  - Every hour avgTakeOff planes take off									*
*			  - Planes that have been waiting to take off for near to three hours		*
*			    have highest priority													*
*			  - Planes that need to land have second highest priority					*
*			  - Planes waiting to take off for less than three hours have lowest		*
*			    priority																*
*																						*
*			  Simulation Basic Flow:													*
*			  (1) User enters run time for the program.									*
*			  (2) User is asked if they would like multiple reports and if yes, at		*
*				  what intervals.														*
*			  (3) Simulation enters loop for user requested run time. Every loop		*
*			      iteration the program updates the runway and the report.				*
*				  (3.1) Planes may be added to either the take off or landing queue.	*
*			      (3.2) If the user requested reports, the program checks that the		*
*				        time interval for printing a report passed.						*
*			  (4) Loop ends. Runway operations summary printed on console.				*
*	Author: Poema Cavalcanti															*
*	Date: 12/11/2011																	*
****************************************************************************************/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

#include "Runway.h"
#include "Report.h"

int main()
{
	// variables used for simulation run time and reporting intervals 
	int runtime;
	char input;
	bool reports;
	int reportTime;
	// Runway variable
	Runway runwayOne;
	// Report variable
	Report summary;

	// Get simulation run time
	cout << "Please enter number of minutes simulation should run: " ;
	cin >> runtime;

	// Get report interval
	cout << "Would you like the simulation to print status reports? (Y/N) " ;
	cin >> input;
	if (input == 'y' || input == 'Y') {
		reports = true;
		cout << "How often would you like a report to be printed? " ;
		cin >> reportTime;
	}
	else
		reports = false;

	int avgTakeOff = 15;	// Every hour avgTakeOff planes take-off
	int takeOff_this_hour = 0;
	int avgLanding = 15;	// Every hour avgLanding planes land
	int landed_this_hour = 0;

	for (int i = 0; i < runtime; i++)
	{
		// Using rand() to generate takeOffRand
		int takeOffRand = rand();
		if (((takeOffRand % 60) < avgTakeOff) && (takeOff_this_hour < avgTakeOff)) {	// Though the Problem description asks that the program check
			runwayOne.insert((rand() % 9000 + 1000), false, (rand() % 10 + 5));			// if takeOffRand < (avgTakeOff/60), when that check is used	
			takeOff_this_hour++;														// no planes get added to the take-off queue.
		}
		// Using rand() to generate landRand
		int landRand = rand();
		if (((landRand % 60) < avgLanding) && (landed_this_hour < avgLanding)) {	// Though the Problem description asks that the program check
			runwayOne.insert((rand() % 9000 + 1000), true, (rand() % 5 + 5));		// if  landRand < (avgLanding/60), when that check is used
			landed_this_hour++;														// no planes get added to the landing queue.
		}
		if (runwayOne.is_free()) {									// Check if the runway is free. Else continue execution.
			if(runwayOne.remove()) {								// Check if a plane can be dequeued from either the landing or take-off queue
				if (runwayOne.landing())							// If the plane that was dequeued is landing
					summary.increase_landings(runwayOne.wait());	//   Update number of landings and add how long the plane waited to land
				else												// Else
					summary.increase_takeOffs(runwayOne.wait());	//   Update number of take-offs and add how long the plane waited to take-off
			}
		}

		// Update runway status and report to reflect time passage
		runwayOne.update();
		summary.increment_time();
		// Report collects the sizes of each queue to calculate averages
		summary.update_landing_size(runwayOne.landing_size());
		summary.update_takeOff_size(runwayOne.take_off_size());

		// If the hour mark has been reached reset planes landed and taken off for the hour
		if ((i % 60) == 0) {
			int takeOff_this_hour = 0;
			int landed_this_hour = 0;
		}

		// If the user chose to see reports and the time interval requested
		// has passed, the program prints a report. Else continues execution.
		if ((reports) && ((i % reportTime) == 0))	{
			cout << "\n-----------------------------------------------------------------------" << endl;
			cout << "\t\t\t\tReport " << i / reportTime << endl;
			summary.print(cout);
			cout << endl;
			runwayOne.print(cout);
			cout << "\n-----------------------------------------------------------------------" << endl;
		}
	}
	// Run time has ended
	// Print final report
	cout << "\nSimulation End Summary" << endl;
	summary.print_averages(cout);

	return 0;
}
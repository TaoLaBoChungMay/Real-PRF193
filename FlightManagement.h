#include <iostream>
#include <vector>
#include "FLight.h"

#ifndef FLIGHTMANAGEMENT_H
#define FLIGHTMANAGEMENT_H

class FlightManagement {
	private :
		vector <Flight> listFlight;
	public :

		void addFlightSchedule ();
		void updateFlightSchedule ();
		void searchByDestination ();
		void revenuePerFlight ();
};

#endif
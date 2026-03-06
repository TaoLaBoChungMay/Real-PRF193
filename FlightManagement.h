#ifndef FLIGHTMANAGEMENT_H
#define FLIGHTMANAGEMENT_H

#include <iostream>
#include <vector>
#include "FLight.h"


class FlightManagement {
	private :
		vector <Flight> listFlight;
	public :
		void addFlightSchedule ();
		void updateFlightSchedule ();
		void searchByDestination ();
		void revenuePerFlight ();

		// Hàm bổ trợ cho việc tìm kiếm Destination và đặt vé
		vector<Flight> findFlightByDestination(string Des);

		// Hàm in header
		void displayHeader ();
};

#endif
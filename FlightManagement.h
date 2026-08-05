#ifndef FLIGHTMANAGEMENT_H
#define FLIGHTMANAGEMENT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Flight.h"
#include "ReservationManagement.h"
class ReservationManagement;

class FlightManagement {
	protected :
		vector <Flight> listFlight;
		int NextFID = 0;
	public :
		void addFlightSchedule ();
		void deleteFlightSchedule ();
		void updateFlightSchedule ();
		void searchByDestination ();
		void revenuePerFlight (ReservationManagement &RMng);
		void sortFlightByPrice();
		void searchByDepartureTime();

		// sub-attribute
		double revenueByFID;

		// sub - method
		vector<Flight> findFlightByDestination(string Des);
		Flight* findFlightByFID (const string& FID);
		vector<Flight>::iterator findItByFID(const string& FID);
		void updateNextIDFromData();
		// Header
		void headerFlight ();

		// Getter
		const vector<Flight>& getListFlight() const;
		double getRevenueByFID() const;
		// Setter
		void setListFlight(vector<Flight>& LF);
		
};

#endif
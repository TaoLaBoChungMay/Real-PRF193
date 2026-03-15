#ifndef FLIGHTMANAGEMENT_H
#define FLIGHTMANAGEMENT_H

#include <iostream>
#include <vector>
#include "Flight.h"
#include "ReservationManagement.h"
#include "FileHelper.h"
class ReservationManagement;

class FlightManagement {
	protected :
		vector <Flight> listFlight;
	public :
		void addFlightSchedule ();
		void updateFlightSchedule ();
		void searchByDestination ();
		void revenuePerFlight (ReservationManagement &RMng);
		void sortFlightByPrice();
		void searchByDepartureTime();
		
		// sub-attribute
		double revenueByFID ;
		
		// sub - method
		vector<Flight> findFlightByDestination(string Des);
		Flight* findFlightByFID (string FID);
		
		// Hàm in header
		void headerFlight ();

		// Getter
		vector <Flight> &getListFlight (){
			return listFlight;
		}
		double getRevenueByFID (){
			return revenueByFID;
		}
		// Setter
		
		void setListFlight(vector <Flight> LF){
			this -> listFlight = LF;
		}
		
		
};

#endif
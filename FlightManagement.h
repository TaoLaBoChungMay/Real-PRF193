#ifndef FLIGHTMANAGEMENT_H
#define FLIGHTMANAGEMENT_H

#include <iostream>
#include <vector>
#include "Flight.h"
#include "ReservationManagement.h"
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
		
		// Hàm bổ trợ cho việc tìm kiếm Destination và đặt vé
		vector<Flight> findFlightByDestination(string Des);
		bool searchFID (string fid);
		
		// Hàm in header
		void displayHeader ();

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
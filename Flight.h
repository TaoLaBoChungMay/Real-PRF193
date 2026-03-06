#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;
class Flight {
	private :
		string FlightID;
		string Destination;
		string DepartureTime;
		double TicketPrice;

	public :
		// Constructor
		Flight ()
			:	FlightID (""), Destination (""), DepartureTime (""), TicketPrice (0)
		{}

		// Getter
		string getFlightID () {
			return FlightID;
		}

		string getDestination () {
			return Destination;
		}

		string getDepartureTime () {
			return DepartureTime;
		}

		double getTicketPrice () {
			return TicketPrice;
		}
		// Setter

		void setFlightID (string FID) {
			this -> FlightID = FID;
		}

		void setDestination (string Des) {
			this -> Destination = Des;
		}

		void setDepartureTime (string Dep) {
			this -> DepartureTime = Dep;
		}

		void setTicketPrice (double TP) {
			this -> TicketPrice = TP;
		}

		// Sub - method
		
		void displayFlight();
		
};


#endif
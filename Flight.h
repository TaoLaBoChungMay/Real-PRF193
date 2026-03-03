#include <iostream>
#include <string>
#ifndef FLIGHT_H
#define FLIGHT_H

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

		string getTicketPrice () {
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
};

#endif
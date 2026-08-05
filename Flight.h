#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
#include <string>

using namespace std;

class Flight {
	private:
		string FlightID;
		string Destination;
		string DepartureTime;
		double TicketPrice;

	public:
		// Constructor
		Flight();

		// Getter
		string getFlightID() const;
		string getDestination() const;
		string getDepartureTime() const;
		double getTicketPrice() const;

		// Setter
		void setFlightID(string FID);
		void setDestination(string Des);
		void setDepartureTime(string Dep);
		void setTicketPrice(double TP);

		// Method
		void displayFlight() const;
};

#endif
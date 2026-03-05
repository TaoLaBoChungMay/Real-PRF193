#include <iostream>
#include <vector>
#include "FlightManagement.h"

using namespace std;

//
void FlightManagement::addFlightSchedule() {

	Flight Fl;

	//1. Enter destination
	string Des ="";
	cout <<"Add Destination  : ";
	getline(cin >> ws, Des);
	Fl.setDestination(Des);

	//2. Enter Departure Time
	string Dep ="";
	cout <<"Add Departure Time : ";
	getline(cin >> ws, Dep);
	Fl.setDepartureTime(Dep);


	//3. Enter Ticket Price
	double TP =0;
	do {
		cout <<"Add Ticket Price ( Ticket Price >= 50.00) : ";
		cin >> TP;
		if (TP < 50)
			cout <<"Please enter Ticket Price again ! \n";
	} while (TP < 50);

	Fl.setTicketPrice(TP);

	//4. Update FLT ID by 1
	// Limit FLT ID = 100 Flight
	unsigned int intID = listFlight.size() + 1;
	string FID ="FLT"; // FLT xxx
	if (listFlight.size() < 10) {
		FID +="00";
	} else if (listFlight.size() >=10 && listFlight.size() <=99 ) {
		FID +="0";
	} else {																		// Reach limit number of flights
		cout <<"The flight has reached its maximum capacity ! \n";
		return;
	}
	FID += to_string(intID);
	Fl.setFlightID(FID);
	
	//5. Notify add succesfully
	
	cout <<"Add successfully ! \n";
	
}


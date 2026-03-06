#include <iostream>
#include "Flight.h"

using namespace std;

void Flight ::displayFlight () {
	cout << left
	     << "| " << setw(8)  << FlightID
	     << "| " << setw(20) << Destination
	     << "| " << setw(15) << DepartureTime
	     << "| " << setw(12) << fixed << setprecision(2) << TicketPrice
	     << "|\n";
}
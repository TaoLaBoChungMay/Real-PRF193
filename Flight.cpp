#include <iostream>
#include <iomanip>
#include "Flight.h"

using namespace std;

// Constructor
Flight::Flight()
	: FlightID(""), Destination(""), DepartureTime(""), TicketPrice(0) {}

// Getter
string Flight::getFlightID() const {
	return FlightID;
}

string Flight::getDestination() const {
	return Destination;
}

string Flight::getDepartureTime() const {
	return DepartureTime;
}

double Flight::getTicketPrice() const {
	return TicketPrice;
}

// Setter
void Flight::setFlightID(string FID) {
	this->FlightID = FID;
}

void Flight::setDestination(string Des) {
	this->Destination = Des;
}

void Flight::setDepartureTime(string Dep) {
	this->DepartureTime = Dep;
}

void Flight::setTicketPrice(double TP) {
	this->TicketPrice = TP;
}

// Display
void Flight::displayFlight() const {
	cout << left
	     << "| " << setw(8)  << FlightID
	     << "| " << setw(20) << Destination
	     << "| " << setw(15) << DepartureTime
	     << "| " << setw(12) << fixed << setprecision(2) << TicketPrice
	     << "|\n";
}
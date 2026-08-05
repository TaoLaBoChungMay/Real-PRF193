#include <iostream>
#include <string>
#include <iomanip>
#include "Reservation.h"

using namespace std;

// Constructor
Reservation::Reservation()
	: BookingID(""), PassengerID(""), FullName(""), SeatClass(""), FIDBooking("") {}

// Setter
void Reservation::setBookingID(string &BID) {
	this->BookingID = BID;
}

void Reservation::setPassengerID(string &PID) {
	this->PassengerID = PID;
}

void Reservation::setFullName(string &FN) {
	this->FullName = FN;
}

void Reservation::setSeatClass(string &seatType) {
	this->SeatClass = seatType;
}

void Reservation::setFIDBooking(string &FID) {
	this->FIDBooking = FID;
}

void Reservation::setDestination(string &Des) {
	this -> Destination = Des;
}
// Getter
string Reservation::getBookingID() const {
	return BookingID;
}

string Reservation::getPassengerID() const {
	return PassengerID;
}

string Reservation::getFullName() const {
	return FullName;
}

string Reservation::getSeatClass() const {
	return SeatClass;
}

string Reservation::getFIDBooking() const {
	return FIDBooking;
}

string Reservation::getDestination() const {
	return Destination;
}

// Display
void Reservation::displayReservation() const {
	cout << left
	     << "| " << setw(10) << BookingID
	     << "| " << setw(9)  << FIDBooking
	     << "| " << setw(9)  << Destination
	     << "| " << setw(10) << PassengerID
	     << "| " << setw(10) << FullName
	     << "|\n";
}

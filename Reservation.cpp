#include <iostream>
#include <string>
#include <iomanip>
#include "Reservation.h"

using namespace std;

void Reservation::displayHeader() {
	cout << "==========================================\n";
	cout << left
	     << "| " << setw(8)  << "BOOKING ID"
	     << "| " << setw(8)  << "FLT ID"
	     << "| " << setw(8)  << "PAS ID"
	     << "| " << setw(20) << "FULL NAME"
	     << "|\n";
	cout << "-------------------------------------------\n";
}
void Reservation::displayReservation() {
	cout << left
	     << "| " << setw(8) << BookingID
	     << "| " << setw(8)  << FIDBooking
	     << "| " << setw(8) << PassengerID
	     << "| " << setw(20) << FullName
	     << "|\n";
}
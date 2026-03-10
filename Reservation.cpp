#include <iostream>
#include <string>
#include <iomanip>
#include "Reservation.h"

using namespace std;

void Reservation::displayReservation() {
	cout << left
	     << "| " << setw(8) << BookingID
	     << "| " << setw(8)  << FIDBooking
	     << "| " << setw(8) << PassengerID
	     << "| " << setw(14) << FullName
	     << "|\n";
}
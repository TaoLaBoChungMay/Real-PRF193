#include <iostream>
#include <string>
#include <iomanip>
#include "Reservation.h"

using namespace std;

void Reservation::displayReservation() {
	cout << left
	     << "| " << setw (10) << BookingID
	     << "| " << setw (9)  << FIDBooking
	     << "| " << setw (10) << PassengerID
	     << "| " << setw (10) << FullName
	     << "|\n";
}
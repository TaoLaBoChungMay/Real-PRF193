#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <vector>
#include "Flight.h"
using namespace std;

class Reservation {
	private :
		string BookingID;
		string PassengerID;			// PASxxx
		string FullName;			// Min 2 words
		string SeatClass;			// Economy = 10 / Business = 20

		// Sub attribute
		string FIDBooking;
	public :
		// Constructor
		Reservation () :
			BookingID(""), PassengerID(""), FullName(""), SeatClass(""), FIDBooking("")
		{}

		void setBookingID(string &BID) {
			this->BookingID = BID;
		}
		void setPassengerID(string &PID) {		// PASxxx
			this->PassengerID = PID;
		}
		void setFullName(string &FN) {
			this->FullName = FN;
		}
		void setSeatClass(string &seatType) {
			this->SeatClass = seatType;
		}

		void setFIDBooking (string &FID) {
			this ->FIDBooking = FID;
		}

		// GETTER
		string getBookingID () {
			return BookingID;
		}
		string getPassengerID () {
			return PassengerID;
		}
		string getFullName() {
			return FullName;
		}
		string getSeatClass() {
			return SeatClass;
		}
		string getFIDBooking () {
			return FIDBooking;
		}
		
		// Method
		void displayReservation();
		void displayHeader();
};

#endif
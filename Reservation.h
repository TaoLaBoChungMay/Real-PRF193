#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <vector>

using namespace std;

class Reservation {
	private :
		string BookingID;
		string PassengerID;			// PASxxx
		string FullName;			// Min 2 words
		string SeatClass;			// Economy = 10 / Business = 20

	public :
		// Constructor
		Reservation () :
			BookingID(""), PassengerID(""), FullName(""), SeatClass("")
		{}

		// SETTER
		void setBookingID(string BID) {
			this->BookingID = BID;
		}
		void setPassengerID(string PID) {		// PASxxx
			this->PassengerID = PID;
		}
		void setFullName(string FN) {
			this->FullName = FN;
		}
		void setSeatClass(string seatType) {
			this->SeatClass = seatType;
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

		// Method
		void displayReservation();
};

#endif
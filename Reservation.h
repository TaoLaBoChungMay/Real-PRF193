#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <vector>
#include "Flight.h"
using namespace std;

class Reservation {
	private:
		string BookingID;
		string PassengerID;
		string FullName;
		string SeatClass;
		string FIDBooking;
		// Sub - attribute
		string Destination;
	public:
		// Constructor
		Reservation();

		// Setter
		void setBookingID(string &BID);
		void setPassengerID(string &PID);
		void setFullName(string &FN);
		void setSeatClass(string &seatType);
		void setFIDBooking(string &FID);
		void setDestination(string &Des);
		// Getter
		string getBookingID() const;
		string getPassengerID() const;
		string getFullName() const;
		string getSeatClass() const ;
		string getFIDBooking()const ;
		string getDestination() const;
		// Method
		void displayReservation() const;
		void displayHeader() const;
		void displayTicket() const;

		// Sub-Method
		
};

#endif
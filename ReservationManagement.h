#ifndef RESERVATION_MANAGEMENT_H
#define RESERVATION_MANAGEMENT_H

#include <iostream>
#include <string>
#include <vector>
#include "Reservation.h"


using namespace std;


class FlightManagement;   // Clare to link Flight

class ReservationManagement {
	private :
		vector <Reservation> listReservation;
		FlightManagement& FMng;			// Can get method from FlightManagement

	public :
		// Construct
		ReservationManagement (FlightManagement& FMng) :
			FMng(FMng)
		{}

		// Method
		void bookTicket ();
		void cancelReservation();
		void displayPassengerGroup();

		// SETTER
		void setlistReservation (vector <Reservation> lR) {
			this -> listReservation = lR;
		}

		// GETTER
		vector <Reservation> &getlistReservation() {
			return listReservation;
		}
		
		// Sub- method
		void headerReservation ();
};

#endif
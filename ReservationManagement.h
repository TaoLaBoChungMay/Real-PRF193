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
		int NextBID = 0;
		int NextPID = 0;

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
		void setlistReservation(const vector<Reservation>& lR);

		// GETTER
		const vector<Reservation>& getlistReservation() const;

		// Sub- method
		void headerReservation ();
		void updateNextIDFromData();
};

#endif
#include <iostream>
#include <vector>
#include <iomanip>
#include "Flight.h"
#include "FlightManagement.h"
#include "ReservationManagement.h"
#include "HelperReservation.h"
#include "HelperFlight.h"
using namespace std;

void ReservationManagement::headerReservation () {
	cout << "===========================================================\n";
	cout << left
	     << "| " << setw(8)  << "BOOKING ID"
	     << "| " << setw(8)  << "FLT ID"
	     << "| " << setw(8)  << "PAS ID"
	     << "| " << setw(9) <<  "DESTINATION"
	     << "| " << setw(12) << "FULL NAME"
	     << "|\n";
	cout << "-----------------------------------------------------------\n";

}

// SETTER
void ReservationManagement::setlistReservation(const vector<Reservation>& lR) {
	this->listReservation = lR;
}

// GETTER
const vector<Reservation>& ReservationManagement::getlistReservation() const {
	return listReservation;
}

//==================== UPDATE ID FOR PID AND BID ==========//
void ReservationManagement::updateNextIDFromData() {
	int maxBID = 0;
	int maxPID = 0;
	for (const auto &r : listReservation) {
		string BID = r.getBookingID(); // FLT001
		string PID = r.getPassengerID();
		if (BID.length() > 3) {
			int num = stoi(BID.substr(3));
			if (num > maxBID) {
				maxBID = num;
			}
		}
		if (PID.length() > 3) {
			int num = stoi(PID.substr(3));
			if (num > maxPID) {
				maxPID = num;
			}
		}
	}

	NextPID = maxPID;
	NextBID = maxBID;
}
//--------------------------------------------------------------------------------//
//=========================== 8.Book a ticket ====================================//
void ReservationManagement::bookTicket() {

	HelperReservation hr;
	HelperFlight hf;
	// TH 1 : None Flight
	if (FMng.getListFlight().empty()) {
		cout <<"None Flight exist in List ! Return back MAIN MENU \n";
		return;
	}

	// TH 2 : Flight has been existed
	FMng.headerFlight ();
	for (auto &f : FMng.getListFlight()) {
		f.displayFlight();
	}

	//1. Enter Destination
	vector <Flight> foundFlight;
	do {
		string Des = hf.readStringDestination();

		//1.1 show Flight match Destination
		foundFlight = FMng.findFlightByDestination(Des);

		//1.12 None Flight was found
		if (foundFlight.size() == 0) {
			cout << Des << " Not Found ! \n";
		}
	} while (foundFlight.size() == 0);


	//1.2 show all Flight matched Destination
	FMng.headerFlight ();
	for (auto f : foundFlight) {
		f.displayFlight();
	}


//2. Choose FLT ID to book
	string FID ="";
	string Des ="";
	Flight *choicedFlight = nullptr;

	do {
		cout <<"Choose FLT ID you want book (FLTxxx, e.g., FLT001) \n ";
		FID = hf.readStringFID();

		for (auto f : foundFlight) {
			//2.1 Choose Flight ordered
			if (f.getFlightID () == FID) {
				choicedFlight = FMng.findFlightByFID(FID);
				Des = f.getDestination();
				break;
			}
		}

		if (choicedFlight == nullptr)
			cout <<"Please Enter FLT ID again (FLTxxx, e.g., FLT001) \n";
	} while (choicedFlight == nullptr);

	//2.2 Enter Name
	string FN = hr.readFullName();

	//3. Seat Class
	double Price = choicedFlight->getTicketPrice();
	string seatType = hr.readSeatType (Price);

	//4. Calc Revenue
	double PriceTicket =0;	// Final Price
	if (seatType == "Economy") {
		PriceTicket = choicedFlight->getTicketPrice() + 10;
	} else if (seatType == "Business") {
		PriceTicket = choicedFlight->getTicketPrice() + 100;
	}

//5. Auto Update PAS ID and BK ID
	NextPID++;
	NextBID++;
	string BID ="BK" + hr.updateID(NextPID);
	string PID ="PAS" + hr.updateID(NextBID);

//6. Create object
	Reservation r;

	r.setBookingID (BID);
	r.setPassengerID(PID);
	r.setFIDBooking(FID);
	r.setDestination(Des);
	r.setFullName (FN);
	r.setSeatClass(seatType);

	listReservation.push_back(r);

	// 8. Print ticket
	cout << "\n========= BOOKING SUCCESSFUL =========\n";
	cout << "Booking ID   : " << BID << endl;
	cout << "Passenger ID : " << PID << endl;
	cout << "Full Name    : " << FN  << endl;
	cout << "Flight ID    : " << FID << endl;
	cout << "Destination  : " << Des << endl;
	cout << "Seat Class   : " << seatType << endl;
	cout << "Final Price  : " << fixed << setprecision(2)
	     << PriceTicket <<"$" << endl;
	cout << "======================================\n";
}

//================= 9.Cancel reservation ===================//

void ReservationManagement::cancelReservation() {
	HelperReservation hr;
	// Display Booking for user
	headerReservation();
	for (auto r : listReservation)
		r.displayReservation();

	// Processing cancel Book Ticket
	cout <<"Enter Your BookingID on your ticket (BKxxx, e.g : BK001) : \n";
	string BID = hr.readStringBID();

	for (int i=0; i < listReservation.size(); i++) {
		if (listReservation[i].getBookingID () == BID) {
			listReservation.erase(listReservation.begin() + i);
			cout << "Reservation cancelled successfully! \n";
			return;
		}
	}

	cout << "Booking ID " << BID << " was not found. Cancellation failed.\n";
	return;
}


//============== 5.Display passenger lists grouped by flight =====================//
void ReservationManagement :: displayPassengerGroup() {
	HelperReservation hr;
	HelperFlight hf;
	FMng.headerFlight();

	for (auto f : FMng.getListFlight() ) {
		f.displayFlight();
	}

	string FID = "";
	cout <<"Enter FLT ID you want to check list Passenger (FLTxxx, e.g., FLT001) \n ";
	FID = hf.readStringFID();

	bool found = false;
	headerReservation ();
	for (auto &r : listReservation)
		if (r.getFIDBooking() == FID) {
			r.displayReservation();
			found = true;
		}

	if (found == false)
		cout << "Flight ID " << FID << " was not found. Display failed.\n";

	return;
}



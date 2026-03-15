#include <iostream>
#include <vector>
#include <iomanip>
#include "Flight.h"
#include "FlightManagement.h"
#include "ReservationManagement.h"

using namespace std;

void ReservationManagement::headerReservation () {
	cout << "==============================================\n";
	cout << left
	     << "| " << setw(8)  << "BOOKING ID"
	     << "| " << setw(8)  << "FLT ID"
	     << "| " << setw(8)  << "PAS ID"
	     << "| " << setw(12) << "FULL NAME"
	     << "|\n";
	cout << "----------------------------------------------\n";

}

//=========================== Book a ticket ====================================//
void ReservationManagement::bookTicket() {

	FileHelper fHelper;
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
		string Des = fHelper.readStringDestination();

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

//================== Booking Ticket =========================

//2. Choose FLT ID to book
	string FID ="";
	Flight *choicedFlight = nullptr;

	do {
		cout <<"Choose FLT ID you want book (FLTxxx, e.g., FLT001) : ";
		getline(cin >> ws, FID);

		for (auto f : foundFlight) {
			if (f.getFlightID () == FID) {
				choicedFlight = FMng.findFlightByFID(FID);
				break;
			}
		}

		if (choicedFlight == nullptr)
			cout <<"Please Enter FLT ID again (FLTxxx, e.g., FLT001) \n";
	} while (choicedFlight == nullptr);


//2.1 Choose Flight ordered
	string FN = "";
	do {
		cout << "Enter Your Name (length >=2 words) : ";
		getline(cin >> ws, FN);

		if ( FN.size() < 2)
			cout << "Please Enter Your Name Again ! \n";

	} while ( FN.size() < 2 );

//3. Seat Class
	int choice =-1;
	string seatType ="";

	do {
		cout <<"Choose Seat Type (1. Economy / 2. Bussiness ) \n" ;
		cout <<"1. Price Economy Seat : " << choicedFlight->getTicketPrice() + 10 <<"$ \n";
		cout <<"2. Price Business Seat : " << choicedFlight->getTicketPrice() + 100 <<"$ \n";
		cin >> choice;

		if (choice != 1 && choice != 2)
			cout << "Invalid choice. Please try again.\n";

	} while (choice != 1 && choice != 2);

	double PriceTicket =0;	// Final Price

	if (choice == 1 ) {
		PriceTicket = choicedFlight->getTicketPrice() + 10;
		seatType ="Economy";
	}

	else {
		PriceTicket = choicedFlight->getTicketPrice() + 100;
		seatType ="Business";
	}

//5. Auto Update PAS ID and BK ID
	string BID ="BK";
	string PID ="PAS";

	unsigned int ID = listReservation.size() + 1;

	if (listReservation.size() < 10) {
		BID +="00";
		PID +="00";
	} else if (listReservation.size() >=10 && listReservation.size() <=99 ) {
		BID +="0";
		PID +="0";
	} else { // Reach limit number of flights  ( 100 ticket)
		cout <<"The quantity of ticket has reached its maximum capacity ! \n";
		return;
	}
	BID += to_string (ID);
	PID += to_string (ID);


//6. Create object
	Reservation r;

	r.setBookingID (BID);
	r.setFullName (FN);
	r.setPassengerID(PID);
	r.setSeatClass(seatType);
	r.setFIDBooking(FID);

	listReservation.push_back(r);

	// 8. Print ticket
	cout << "\n========= BOOKING SUCCESSFUL =========\n";
	cout << "Booking ID   : " << BID << endl;
	cout << "Passenger ID : " << PID << endl;
	cout << "Full Name    : " << FN << endl;
	cout << "Flight ID    : " << FID << endl;
	//	cout << "Destination  : " <<
	cout << "Seat Class   : " << seatType << endl;
	cout << "Final Price  : " << fixed << setprecision(2)
	     << PriceTicket <<"$" << endl;
	cout << "======================================\n";
}

//================= Cancel reservation ===================//

void ReservationManagement::cancelReservation() {
	string BID = "";
	cout <<"Enter Your BookingID on your ticket (BKxxx, e.g : BK001) : ";
	cin >> BID;
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


//============== Display passenger lists grouped by flight =====================//
void ReservationManagement :: displayPassengerGroup() {

	FMng.headerFlight();
	for (auto f : FMng.getListFlight() ) {
		f.displayFlight();
	}
	
	string FLTID = "";
	cout <<"Enter FLT ID you want to check list Passenger (FLTxxx, e.g., FLT001) : ";
	getline(cin >> ws, FLTID);

	bool found = false;
	headerReservation ();
	for (auto &r : listReservation)
		if (r.getFIDBooking() == FLTID) {
			r.displayReservation();
			found = true;
		}

	if (found == false)
		cout << "Flight ID " << FLTID << " was not found. Display failed.\n";

	return;
}



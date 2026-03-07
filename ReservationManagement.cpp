#include <iostream>
#include <vector>
#include "Flight.h"
#include "FlightManagement.h"
#include "ReservationManagement.h"

using namespace std;


//=========================== 5. Book a ticket ====================================//
void ReservationManagement::bookTicket() {

	// TH 1 : Không có chuyến bay nào trong danh sách
	if (FMng.getListFlight().empty()) {
		cout <<"None Flight left in List ! \n";
		return;
	}

	// TH 2 : Có chuyến bay trong danh sách
	FMng.displayHeader();
	for (auto &f : FMng.getListFlight()) {
		f.displayFlight();
	}

	//1 Enter Destination
	vector <Flight> foundFlight;
	do {
		cout <<"Enter destination you want to go : ";
		string Des ="";
		getline(cin >> ws, Des);

		//1.1 Tìm địa điểm và trả về chuyến bay cần đặt vé
		foundFlight = FMng.findFlightByDestination(Des);

		//1.12 Trường hợp không có chuyến bay nào được tìm thấy
		if (foundFlight.size() == 0) {
			cout << Des << " Not Found ! \n";
		}
	} while (foundFlight.size() == 0);


	//1.2 In tất cả chuyến bay trùng địa điểm yêu cầu
	FMng.displayHeader();
	for (auto f : foundFlight) {
		f.displayFlight();
	}

//================== Đặt vé =========================

//2. Chọn FLT ID để đặt vé
	string FID ="";
	cout <<"Choose FLT ID you want book : ";
	getline(cin >> ws, FID);

//2.1 Chọn chuyến bay đã đặt
	Flight choicedFlight;
	for (auto &f : foundFlight) {
		if (f.getFlightID () == FID) {
			choicedFlight = f;
			break;
		}
	}

	string FN ="";
	do {
		cout << "Enter Your Name (length >=2 words) ";
		getline(cin >> ws, FN);

		if ( FN.size() < 2)
			cout << "Please Enter Your Name Again ! \n";

	} while ( FN.size() < 2 );

	//4. Chọn ghế ngồi
	int choice =-1;
	string seatType ="";

	do {
		cout <<"Choose Seat Type (1. Economy / 2. Bussiness ) \n" ;
		cout <<"1. Price Economy Seat : " << choicedFlight.getTicketPrice() + 10 <<"$ \n";
		cout <<"2. Price Business Seat : " << choicedFlight.getTicketPrice() + 100 <<"$ \n";
		cin >> choice;

		if (choice != 1 && choice != 2)
			cout << "Invalid choice. Please try again.\n";

	} while (choice != 1 && choice != 2);

	double PriceTicket =0;	// Giá chốt đơn

	if (choice == 1 ) {
		PriceTicket = choicedFlight.getTicketPrice() + 10;
		seatType ="Economy";
	}

	else {
		PriceTicket = choicedFlight.getTicketPrice() + 100;
		seatType ="Business";
	}


//5. Cập nhập BookingID và PAS ID
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


//6. Tạo object Reservation để push_back và listReservation
	Reservation r;

	r.setBookingID (BID);
	r.setFullName (FN);
	r.setPassengerID(PID);
	r.setSeatClass(seatType);
	r.setFIDBooking(FID);
//7. Đẩy vào listReservation
	listReservation.push_back(r);

// 7. Print ticket
	cout << "\n========= BOOKING SUCCESSFUL =========\n";
	cout << "Booking ID   : " << BID << endl;
	cout << "Passenger ID : " << PID << endl;
	cout << "Full Name    : " << FN << endl;
	cout << "Flight ID    : " << FID << endl;
	cout << "Seat Class   : " << seatType << endl;
	cout << "Final Price  : " << fixed << setprecision(2)
	     << PriceTicket <<"$" << endl;
	cout << "======================================\n";
}

//================= 6. Cancel reservation ===================//

void ReservationManagement::cancelReservation() {
	string BID = "";
	cout <<"Enter Your BookingID on your ticket (BKxxx) : ";

	for (int i=0; i < listReservation.size(); i++) {
		if (listReservation[i].getBookingID () == BID) {
			listReservation.erase(listReservation.begin() + i);
			cout << "Reservation cancelled successfully! \n";
			return;
		}
	}
	
	cout << "Reservation cancelled successfully!\n";
	return;
}


//============== 7. Display passenger lists grouped by flight =====================//
void ReservationManagement :: displayPassengerGroup() {

	string FLTID = "";
	cout <<"Enter FLT ID you want to check list Passenger : ";
	getline(cin >> ws, FLTID);

	for (auto &r : listReservation) {
		if (r.getFIDBooking() == FLTID) {
			r.displayReservation();
		}
	}
}



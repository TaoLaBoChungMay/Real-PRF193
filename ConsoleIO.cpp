#include <iostream>
#include "ConsoleIO.h"
#include "FileHelper.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

enum MenuOption {
	SAVE_EXIT = 0,

	add_Flight = 1,
	update_Flight = 2,
	search_Destination = 3,
	calc_Revenue = 4,
	display_Passengers = 5,
	sort_FLight_by_Price = 6,
	search_by_Departure_Time = 7,

	book_Ticket = 8,
	cancel_Reservation = 9,
};

using namespace std;

//========================= SHOW MAIN MENU ==============//
int ConsoleIO::showMainMenu() {

	int choice = -1;

	cout << "=========== MAIN MENU ===========\n";
	cout << "1. Flight Management\n";
	cout << "2. Reservation Management\n";
	cout << "0. Save & Exit (-_-) \n";

	while (true) {

		cout << "Enter your choice: ";
		cin >> choice;

		if (choice >= 0 && choice <= 2) {
			return choice;
		}

		cout << "Choice must be from 0 -> 2\n";
	}
	return choice;
}

int ConsoleIO::showFlightMenu() {
	FileHelper fHelper;
	int choice = -1;

	cout << "------------ FLIGHT MANAGEMENT MENU ------------- \n";
	cout << "1. Add flight schedules (<= 100 Schedules) \n";
	cout << "2. Update flight schedules \n";
	cout << "3. Search by Destination \n";
	cout << "4. Calculate total revenue per flight \n";
	cout << "5. Display passenger lists grouped by flight \n";
	cout << "6. Sort flights by Ticket Price (Ascending) \n";
	cout << "7. Search by Departure Time \n";
	cout << "0. BACK MAIN MENU *(^O^)* \n";

	choice = fHelper.readIntChoice(0,9);

	// Return choice
	if (choice == add_Flight || choice == update_Flight || choice == search_Destination || choice == calc_Revenue||
	        choice == display_Passengers || choice == sort_FLight_by_Price || choice == search_by_Departure_Time || choice == SAVE_EXIT)
		return choice;

	return 0;
}
int ConsoleIO::showReservationMenu() {

	FileHelper fHelper;
	int choice = -1;

	cout << "------------ RESERVATION MANAGEMENT MENU ------------- \n";
	cout << "1. Book a ticket \n";
	cout << "2. Cancel reservation \n";
	cout << "0. BACK MAIN MENU \n";

	choice = fHelper.readIntChoice(0,2);

	if (choice == 0)
		return 0;
	if (choice == 1)
		return book_Ticket;
	if (choice == 2)
		return cancel_Reservation;

	return -1;

}

//======================= save file from FMng and RMng ======================//
void ConsoleIO::saveData(FlightManagement &FMng, ReservationManagement &RMng) {

	//0. Init File
	ofstream outputFlightFile ("Flight.txt");
	ofstream outputReservationFile ("Reservation.txt");

	if (!outputFlightFile) {
		cout << "Cannot open file!\n";
		return;
	}
	if (!outputReservationFile) {
		cout << "Cannot open file!\n";
		return;
	}
	//1. get list from FlightManagement and ReservationManagement
	vector <Flight> LF = FMng.getListFlight();
	vector <Reservation> LR = RMng.getlistReservation();

	//---------------2. Write data on file ---------------

	//2.1 Adding listFlight
	outputFlightFile <<"[FLIGHT]" << "\n";
	for (auto &f : LF) {
		outputFlightFile << f.getFlightID () <<"|"
		                 << f.getDestination () <<"|"
		                 << f.getDepartureTime () <<"|"
		                 << f.getTicketPrice () << "\n";
	}

	//2.2 Adding listReservation
	outputReservationFile <<"[RESERVATION]" << "\n";
	for (auto &r : LR) {
		outputReservationFile << r.getBookingID() <<"|"
		                      << r.getFIDBooking() <<"|"
		                      << r.getPassengerID() <<"|"
		                      << r.getFullName()  <<"|"
		                      << r.getSeatClass() << "\n";
	}

	//3. Close File
	outputFlightFile.close();
	outputReservationFile.close();
}

//======================== Read file and push on listFlight and listReservation  =========================== //
void ConsoleIO::loadData(FlightManagement &FMng, ReservationManagement &RMng) {
	ifstream inputFlightFile ("Flight.txt");
	ifstream inputReservationFile ("Reservation.txt");
	// Case 1 : Error open File
	if (!inputFlightFile) {
		cout << "No previous Flight.txt data file found (-_-) . Starting new data.\n";
		return;
	}
	if (!inputReservationFile) {
		cout << "No previous Reservation.txt data file found (-_-) . Starting new data.\n";
		return;
	}
	bool isLineFlight = false;
	bool isLineReservation = false;
	string line ="";

	vector <Flight > LF;
	vector <Reservation> LR;

	// Read File from Flight.txt
	while (getline(inputFlightFile, line)) {

		if(line.empty()) continue;

		if (line == "[FLIGHT]") {
			isLineFlight = true;
			isLineReservation = false;
			continue;
		}

		stringstream ss(line);

		if (isLineFlight) {

			Flight f;

			string FID, Des, Dep, sTP;
			getline(ss, FID, '|');
			getline(ss, Des, '|');
			getline(ss, Dep, '|');
			getline(ss, sTP);
			//1. Lack of one of attribute Flight, thus skip
			if (FID.empty() || Des.empty() || Dep.empty() || sTP.empty())
				continue;

			//2. Error 2 : ticketPrice is string / char
			double TP =0;
			try {
				TP = stod(sTP);
			} catch (const invalid_argument& e) {
				cout << "Invalid number format Ticket Price ! \n";
				continue;
			}

			f.setFlightID(FID);
			f.setDestination(Des);
			f.setDepartureTime(Dep);
			f.setTicketPrice(TP);

			LF.push_back(f);
		}

	}


// Read File from Reservation.txt
	while (getline(inputReservationFile, line)) {

		if(line.empty()) continue;
		if (line == "[RESERVATION]") {
			isLineReservation = true;
			isLineFlight = false;
			continue;
		}

		stringstream ss(line);

		if (isLineReservation) {

			Reservation r;

			string BID, PID, FN, seatType, FID;

			getline(ss, BID, '|');
			getline (ss, FID, '|');
			getline(ss, PID, '|');
			getline(ss, FN, '|');
			getline(ss, seatType);

			//1. Lack 1 over 5 atrribute, thus skip
			if (BID.empty() || FID.empty() || PID.empty() || FN.empty() || seatType.empty())
				continue;

			r.setBookingID(BID);
			r.setFIDBooking(FID);
			r.setPassengerID(PID);
			r.setFullName(FN);
			r.setSeatClass(seatType);

			LR.push_back(r);
		}
	}

	// 3. Pushing on listFlight and listReservation
	FMng.setListFlight(LF);
	RMng.setlistReservation(LR);

	//4. close File
	inputFlightFile.close();
	inputReservationFile.close();

}

//================== OPTIONAL : Wether clear ================= //

void ConsoleIO::askClearScreen() {

	char choice;

	do {

		cout << "\nClear screen? (Y/N): ";
		cin >> choice;

		if (choice == 'Y' || choice == 'y') {
			system("cls");
			break;
		}

		else if (choice == 'N' || choice == 'n') {
			break;
		}

		else {
			cout << "Invalid choice! Please enter Y or N.\n";
		}

	} while (true);

}
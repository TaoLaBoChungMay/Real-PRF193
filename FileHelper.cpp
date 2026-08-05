#include "FileHelper.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//----------------- READE choice for ConsoleIO ---------------//
int FileHelper::readIntChoice(int min, int max) {
	int choice;

	while (true) {
		cout << "Enter your choice: ";

		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input! Please enter a number.\n";
			continue;
		}

		if (choice >= min && choice <= max) {
			cin.ignore(1000, '\n');
			return choice;
		}

		cout << "Choice must be from " << min << " -> " << max << endl;
	}
}
//================== OPTIONAL : Wether clear ================= //


//======================= save file from FMng and RMng ======================//
void FileHelper::saveData(FlightManagement &FMng, ReservationManagement &RMng) {

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

	//2.1 Adding listFlight for Flight.txt
	for (auto &f : LF) {
		outputFlightFile << f.getFlightID () <<"|"
		                 << f.getDestination () <<"|"
		                 << f.getDepartureTime () <<"|"
		                 << f.getTicketPrice () << "\n";
	}

	//2.2 Adding listReservation for Reservation.txt
	for (auto &r : LR) {
		outputReservationFile << r.getBookingID() <<"|"
		                      << r.getFIDBooking() <<"|"
		                      << r.getDestination() <<"|"
		                      << r.getPassengerID() <<"|"
		                      << r.getFullName()  <<"|"
		                      << r.getSeatClass() << "\n";
	}

	//3. Close File
	outputFlightFile.close();
	outputReservationFile.close();
}

//======================== Read file and push on listFlight and listReservation  =========================== //

void FileHelper::loadData(FlightManagement &FMng, ReservationManagement &RMng) {
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
	string line ="";

	vector <Flight > LF;
	vector <Reservation> LR;

	// Read File from Flight.txt
	while (getline(inputFlightFile, line)) {

		if(line.empty()) continue;

		stringstream ss(line);


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
	line ="";
// Read File from Reservation.txt

	while (getline(inputReservationFile, line)) {

		if(line.empty()) continue;
		stringstream ss(line);


		Reservation r;

		string BID, FID, Des, PID, FN, seatType;

		getline(ss, BID, '|');
		getline(ss, FID, '|');
		getline(ss, Des, '|');
		getline(ss, PID, '|');
		getline(ss, FN, '|');
		getline(ss, seatType);

		//1. Lack 1 over 6 atrribute, thus skip
		if (BID.empty() || FID.empty() || Des.empty() || PID.empty() || FN.empty() || seatType.empty())
			continue;

		r.setBookingID(BID);
		r.setFIDBooking(FID);
		r.setDestination(Des);
		r.setPassengerID(PID);
		r.setFullName(FN);
		r.setSeatClass(seatType);

		LR.push_back(r);
	}

	// 3. Pushing on listFlight and listReservation
	FMng.setListFlight(LF);
	RMng.setlistReservation(LR);
	FMng.updateNextIDFromData();
	RMng.updateNextIDFromData();
	//4. close File
	inputFlightFile.close();
	inputReservationFile.close();

}
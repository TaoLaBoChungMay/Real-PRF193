#include <iostream>
#include "ConsoleIO.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

//========================= DISPLAY MENU==============//
int ConsoleIO::showMenu() {
	int choice = -1;
	cout << "=================== MENU ====================== \n";
	cout << "1. Add flight schedules (<= 100 Schedules) \n";
	cout << "2. Update flight schedules \n";
	cout << "3. Search by Destination \n";
	cout << "4. Calculate total revenue per flight \n";
	cout << "5. Book a ticket \n";
	cout << "6. Cancel reservation \n";
	cout << "7. Display passenger lists grouped by flight \n";
	cout << "8. Sort flights by Ticket Price (Ascending) \n";
	cout << "9. Search by Departure Time \n";
	cout << "0. SAVE & EXIT \n";
	cout << "Enter your choice : ";
	cin >> choice;

	while (choice < 0 || choice > 10) {
		cout << "Please enter again ! : ";
		cin >> choice;
	}
	return choice;
}


//======================= Truyền list danh sách vào file TXT để lưu file ======================//
void ConsoleIO::saveData(FlightManagement &FMng, ReservationManagement &RMng) {

	//0. Khởi tạo tên File cần lưu
	ofstream outputFile ("AirFlight_PassengerReservation.txt");

	if (!outputFile) {
		cout << "Cannot open file!\n";
		return;
	}
	//1. Nhận cách list từ FlightManagement và ReservationManagement
	vector <Flight> LF = FMng.getListFlight();
	vector <Reservation> LR = RMng.getlistReservation();

	//2. Lưu dữ liệu vào file

	//2.1 Đưa listFlight vào
	outputFile <<"[FLIGHT]" << "\n";
	for (auto &f : LF) {
		outputFile << f.getFlightID () <<"|"
		           << f.getDestination () <<"|"
		           << f.getDepartureTime () <<"|"
		           << f.getTicketPrice () << "\n";
	}

	//2.2 Đưa listReservation vào
	outputFile <<"[RESERVATION]" << "\n";
	for (auto &r : LR) {
		outputFile << r.getBookingID() <<"|"
		           << r.getFIDBooking() <<"|"
		           << r.getPassengerID() <<"|"
		           << r.getFullName()  <<"|"
		           << r.getSeatClass() << "\n";
	}

	//3. Đóng File
	outputFile.close();
}

//======================== Đọc dữ liệu từ File để bắt đầu chỉnh sửa =========================== //
void ConsoleIO::loadData(FlightManagement &FMng, ReservationManagement &RMng) {
	ifstream inputFile ("AirFlight_PassengerReservation.txt");

	bool isLineFlight = false;
	bool isLineReservation = false;
	string line ="";

	vector <Flight > LF;
	vector <Reservation> LR;

	while (getline(inputFile, line)) {

		if(line.empty()) continue;

		if (line == "[FLIGHT]") {
			isLineFlight = true;
			isLineReservation = false;
			continue;
		}

		if (line == "[RESERVATION]") {
			isLineReservation = true;
			isLineFlight = false;
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

			double TP = stod(sTP);

			f.setFlightID(FID);
			f.setDestination(Des);
			f.setDepartureTime(Dep);
			f.setTicketPrice(TP);

			LF.push_back(f);
		}

		if (isLineReservation) {

			Reservation r;

			string BID, PID, FN, seatType, FID;

			getline(ss, BID, '|');
			getline (ss, FID, '|');
			getline(ss, PID, '|');
			getline(ss, FN, '|');
			getline(ss, seatType);

			r.setBookingID(BID);
			r.setFIDBooking(FID);
			r.setPassengerID(PID);
			r.setFullName(FN);
			r.setSeatClass(seatType);

			LR.push_back(r);
		}
	}
	FMng.setListFlight(LF);
	RMng.setlistReservation(LR);
	inputFile.close();
}
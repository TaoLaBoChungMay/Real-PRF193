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
	cout << "4. Calculate total revenue  per flight \n";
	cout << "5. Display passenger lists grouped by flight \n";
	cout << "6. Sort flights by Ticket Price (Ascending) \n";
	cout << "7. Search by Departure Time \n";
	cout << "8. Book a ticket \n";
	cout << "9. Cancel reservation \n";
	cout << "0. SAVE & EXIT (-_-) \n";

	while (true) {
		cout << "Enter your choice: ";

		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(1000, '\n');		// Xoá buffer còn sót lại
			cout << "Invalid input! Please enter a number.\n";
			continue;
		}

		if (choice >= 0 && choice <= 9) {
			cin.ignore(1000, '\n');
			break;
		}

		cout << "Choice must be from 0 -> 9\n";
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

	// TH 1 : Mở file bị lỗi
	if (!inputFile) {
		cout << "No previous data file found. Starting new data.\n";
		return;
	}

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
			//1. Trong trường hợp thiếu 1 trong các attribute, skip các dòng còn lại
			if (FID.empty() || Des.empty() || Dep.empty() || sTP.empty())
				continue;

			//2. Lỗi 2 : cố tình ticketPrice là nhập chuỗi ký tự
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

		if (isLineReservation) {

			Reservation r;

			string BID, PID, FN, seatType, FID;

			getline(ss, BID, '|');
			getline (ss, FID, '|');
			getline(ss, PID, '|');
			getline(ss, FN, '|');
			getline(ss, seatType);

			//1. Trong trường hợp thiếu 1 trong các attribute, skip các dòng còn lại
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

	// 3. Đẩy vào listFlight và listReservation
	FMng.setListFlight(LF);
	RMng.setlistReservation(LR);

	inputFile.close();
}

//================== OPTIONAL : Người dùng muốn clear màn hình hay không ================= //

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
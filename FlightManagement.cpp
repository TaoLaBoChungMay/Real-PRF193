#include <iostream>
#include <vector>
#include "FlightManagement.h"

using namespace std;


void FlightManagement ::headerFlight () {
	cout << "===============================================================\n";
	cout << left
	     << "| " << setw(8)  << "FLT ID"
	     << "| " << setw(20) << "Destination"
	     << "| " << setw(15) << "Departure"
	     << "| " << setw(12) << "Ticket Price"
	     << "|\n";
	cout << "--------------------------------------------------------------\n";

}

// ========================== Hàm tìm kiếm địa điểm và trả về con trỏ cho foundFlight ==============

vector<Flight> FlightManagement::findFlightByDestination(string Des) {
	vector <Flight> a;
	for (auto &f : listFlight) {
		if (f.getDestination() == Des)
			a.push_back(f);
	}

	return a;
}

Flight* FlightManagement::findFlightByFID(string FID) {
	for (auto &f : listFlight) {
		if (f.getFlightID() == FID)
			return &f;
	}
	return nullptr;
}
//==========================1. Add Flight Schedules ============================//
void FlightManagement::addFlightSchedule() {

	Flight Fl;

	//1. Enter destination
	string Des ="";
	cout <<"Add Destination  : ";
	getline(cin >> ws, Des);


	//2. Enter Departure Time
	string Dep ="";
	cout << "Enter Departure Time (HH:MM, e.g., 14:30): ";
	getline(cin >> ws, Dep);


	//3. Enter Ticket Price
	double TP =0;
	do {
		cout <<"Add Ticket Price ( Ticket Price >= 50.00) : ";
		cin >> TP;

		if (cin.fail()) {				// Lỗi người dùng nhập ký tự
			cin.clear();				// Xoá trạng thái lỗi
			cin.ignore(1000,'\n');		// Xoá dữ liệu sai trong buffer
			cout << "Invalid input! Please enter a number ! \n";
			TP = 0;						// Reset lại giá tiền
			continue;
		}

		if (TP < 50)
			cout <<"Please enter Ticket Price again ! \n";
	} while (TP < 50);



	//4. Update FLT ID by 1
	// Limit FLT ID = 100 Flight
	unsigned int intID = listFlight.size() + 1;
	string FID ="FLT"; // FLT xxx

	if (listFlight.size() < 10) {
		FID +="00";
	} else if (listFlight.size() >=10 && listFlight.size() <=99 ) {
		FID +="0";
	} else {																		// Reach limit number of flights
		cout <<"The flight has reached its maximum capacity ! \n";
		return;
	}
	FID += to_string(intID);


	//5. Notify add succesfully

	cout <<"Add successfully ! \n";

	Fl.setDestination(Des);
	Fl.setDepartureTime(Dep);
	Fl.setTicketPrice(TP);
	Fl.setFlightID(FID);

	listFlight.push_back(Fl);
}

//==========================2. Update Flight Schedules ========================//
void FlightManagement::updateFlightSchedule() {

	//0. In ra các chuyến bay để chọn và sửa
	headerFlight ();
	for (auto &f : listFlight)
		f.displayFlight();

	//1. Nhập FlightID cần cập nhật
	string FID;
	cout << "Enter Flight ID to update: ";
	getline(cin >> ws, FID);

	//2. Tìm chuyến bay trong danh sách

	//2. Tìm chuyến bay trong danh sách
	for (auto &f : listFlight) {
		if (f.getFlightID() == FID) {

			//3. Nhập thông tin mới
			string Des, Dep;
			double TP;

			cout << "Enter new Destination: ";
			getline(cin >> ws, Des);
			cout << "Enter new Departure Time: ";
			getline(cin >> ws, Dep);

			cout << "Enter new Ticket Price: ";
			cin >> TP;

			//4. Cập nhật thông tin chuyến bay
			f.setDestination(Des);
			f.setDepartureTime(Dep);
			f.setTicketPrice(TP);

			cout << "Update successful!\n";
			return;
		}
	}

	//5. Không tìm thấy FlightID
	cout << "Flight not found!\n";
}

//==========================3. Search by Destination ==========================//
void FlightManagement::searchByDestination() {

	//1. Nhập Destination cần tìm
	string Des;
	cout << "Enter Destination: ";
	getline(cin >> ws, Des);

	//2. Tìm các chuyến bay có cùng Destination
	vector<Flight> result = findFlightByDestination(Des);

	//3. Kiểm tra nếu không tìm thấy
	if (result.empty()) {
		cout << "No flight found!\n";
		return;
	}

	//4. In header bảng
	headerFlight ();

	//5. In danh sách chuyến bay tìm được
	for (auto &f : result)
		f.displayFlight();
}

//=====================4. Calculate total revenue per flight  ===================//

void FlightManagement::revenuePerFlight(ReservationManagement &RMng) {
	string FID = "";
	cout <<"Enter FLTID you want to show Renevue : ";
	getline (cin >> ws, FID);

	Flight *flight = findFlightByFID(FID);

	if (flight == nullptr) {
		cout << "Flight not found!\n";
		return;
	}

	double revenue = 0;

	// 1. Lấy danh sách đã đặt vé thành công
	vector<Reservation> LR = RMng.getlistReservation();

	for (auto &r : LR) {
		if (r.getFIDBooking() == FID) {
			if (r.getSeatClass() == "Economy")
				revenue += flight->getTicketPrice() + 10;

			else if (r.getSeatClass() == "Business")
				revenue += flight->getTicketPrice() + 100;
		}
	}

	cout << "Total revenue of " << FID << " = "
	     << fixed << setprecision(2) << revenue << "$\n";
}

//==========================8. Sort flights by Ticket Price ============================//
void FlightManagement::sortFlightByPrice() {
	// 0. Khởi tạo vector chứa Flight và danh sách Flight
	vector <Flight > sortFlight = listFlight;

	//1. Sắp xếp danh sách chuyến bay theo TicketPrice tăng dần
	for (int i = 0; i < sortFlight.size() - 1; i++) {
		for (int j = i + 1; j < sortFlight.size(); j++) {
			if (sortFlight[i].getTicketPrice() > sortFlight[j].getTicketPrice()) {
				Flight temp = sortFlight[i];
				sortFlight[i] = sortFlight[j];
				sortFlight[j] = temp;
			}
		}
	}

	//2. In danh sách chuyến bay sau khi sắp xếp
	headerFlight ();

	for (auto &f : sortFlight) {
		f.displayFlight();
	}
}

//==========================9. Search by Departure Time =======================//
void FlightManagement::searchByDepartureTime() {

	//1. Nhập Departure Time cần tìm
	string Dep;
	cout << "Enter Departure Time: ";
	getline(cin >> ws, Dep);

	bool found = false;

	//2. In header bảng
	headerFlight ();

	//3. Tìm và in chuyến bay
	for (auto &f : listFlight) {
		if (f.getDepartureTime() == Dep) {
			f.displayFlight();
			found = true;
		}
	}

	//4. Nếu không tìm thấy chuyến bay
	if (!found)
		cout << "No flight found!\n";

}
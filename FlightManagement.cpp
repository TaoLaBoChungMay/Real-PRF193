#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
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

// ===================== Fuction for Find by Destination ==============

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
	FileHelper fHelper;
	//1. Enter destination
	string Des = fHelper.readStringDestination();
	//2. Enter Departure Time
	string Dep = fHelper.readStringDepartureTime();

	//3. Enter Ticket Price
	double TP = fHelper.readDoubleTicketPrice();

	//4. Update FLT ID by 1
	// Limit FLT ID = 100 Flight
	unsigned int sizeListFlight = listFlight.size() + 1;
	string FID = fHelper.updateFlightID(sizeListFlight);
	if (FID =="") {
		return;
	}

	//5. Notify add succesfully

	cout <<"Add successfully *(^O^)* ! \n";

	Fl.setDestination(Des);
	Fl.setDepartureTime(Dep);
	Fl.setTicketPrice(TP);
	Fl.setFlightID(FID);

	listFlight.push_back(Fl);
}

//==========================2. Update Flight Schedules ========================//
void FlightManagement::updateFlightSchedule() {
	FileHelper fHelper;

	//0. Show Flight to adjust
	headerFlight ();
	for (auto &f : listFlight)
		f.displayFlight();

	//1. Enter FlightID need update
	string FID;
	cout << "Enter Flight ID to update (FLTxxx, e.g., FLT001) : ";
	getline(cin >> ws, FID);


	//2. Find Flight in listFlight
	for (auto &f : listFlight) {
		if (f.getFlightID() == FID) {

			//3. Adjust new infor
			string Des = fHelper.readStringDestination();
			string Dep = fHelper.readStringDepartureTime();
			double TP = fHelper.readDoubleTicketPrice();

			//4. update new infor
			f.setDestination(Des);
			f.setDepartureTime(Dep);
			f.setTicketPrice(TP);

			cout << "Update successful! *(^O^)* \n";
			return;
		}
	}

	//5. None Flight exist in listFLight
	cout << "Flight not found!\n";
}

//==========================3. Search by Destination ==========================//
void FlightManagement::searchByDestination() {

	FileHelper fHelper;
	//1. Enter Destination need to find
	string Des = fHelper.readStringDestination();
	
	//2. Finding Flight same Destination
	vector<Flight> result = findFlightByDestination(Des);

	//3. If Flight's Destination not exist
	if (result.empty()) {
		cout << "No flight found ! Return to MAIN MENU (*-*) \n";
		return;
	}

	//4. Print Header
	headerFlight ();

	//5. Show Flight has been found
	for (auto &f : result)
		f.displayFlight();
}

//=====================4. Calculate total revenue per flight  ===================//

void FlightManagement::revenuePerFlight(ReservationManagement &RMng) {

	//0. Print Header and show all Flight from listFlight
	headerFlight ();
	for(auto &f : listFlight) {
		f.displayFlight();
	}

	string FID = "";
	cout <<"Enter FLTID you want to show Renevue (FLTxxx, e.g., FLT001 ): ";
	getline (cin >> ws, FID);

	Flight *flight = findFlightByFID(FID);

	if (flight == nullptr) {
		cout << "Flight not found!\n";
		return;
	}

	double revenue = 0;

	// 1. Calc Revenue
	double BusRevenue = 0;
	double EcoRevenue = 0;
	for (auto &r : RMng.getlistReservation()) {
		if (r.getFIDBooking() == FID) {
			if (r.getSeatClass() == "Economy") {
				revenue += flight->getTicketPrice() + 10;
				EcoRevenue +=flight->getTicketPrice() + 10;
			}


			else if (r.getSeatClass() == "Business") {
				revenue += flight->getTicketPrice() + 100;
				BusRevenue +=flight->getTicketPrice() + 100;
			}
		}
	}

	cout <<"Economy Seat Revenue : " << EcoRevenue <<"$\n";
	cout <<"Business Seat Revenue : " << BusRevenue <<"$\n";
	cout << "Total revenue of " << FID << " = "
	     << fixed << setprecision(2) << revenue << "$\n";
}

//==========================8. Sort flights by Ticket Price ============================//
void FlightManagement::sortFlightByPrice() {
	// 0. Init vector sortFlight
	vector <Flight > sortFlight = listFlight;

	//1. sortFlight is sorted by algorithm
	sort(sortFlight.begin(), sortFlight.end(), [](Flight &a,  Flight &b) {
		return a.getTicketPrice() < b.getTicketPrice();
	});

	//2. Print sortFlight after sorting
	headerFlight ();

	for (auto &f : sortFlight) {
		f.displayFlight();
	}
}

//==========================9. Search by Departure Time =======================//
void FlightManagement::searchByDepartureTime() {

	FileHelper fHelper;
	//1. Enter Departure need to FIND
	string Dep = fHelper.readStringDepartureTime();

	bool found = false;

	//2. show Header
	headerFlight ();

	//3. Find and show Flight
	for (auto &f : listFlight) {
		if (f.getDepartureTime() == Dep) {
			f.displayFlight();
			found = true;
		}
	}

	//4. If not found Flight
	if (!found)
		cout << "No flight found! (=_=) \n";

}
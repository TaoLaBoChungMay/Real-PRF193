#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include "FlightManagement.h"
#include "HelperFlight.h"

using namespace std;

//--------------- Function to display headerFlight
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

// Getter
const vector<Flight>& FlightManagement::getListFlight() const {
	return listFlight;
}

// Setter
void FlightManagement::setListFlight(vector<Flight>& LF) {
	this ->listFlight = LF;
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

//================ Function for Find Flight by FID==================//
Flight* FlightManagement::findFlightByFID(const string& FID) {
	for (auto &f : listFlight) {
		if (f.getFlightID() == FID)
			return &f;
	}
	return nullptr;
}

//============== Function find Flight Iterator by FID ===============//
vector<Flight>::iterator FlightManagement::findItByFID(const string& FID) {
	for (auto it = listFlight.begin(); it != listFlight.end(); ++it) {
		if (it->getFlightID() == FID) {
			return it;
		}
	}
	return listFlight.end(); // Not found
}

//=============== FUNCTION for updateID ==================//
void FlightManagement::updateNextIDFromData() {
    int maxID = 0;

    for (const auto &f : listFlight) {
        string FID = f.getFlightID(); // FLT001

        if (FID.length() > 3) {
            int num = stoi(FID.substr(3));
            if (num > maxID) {
                maxID = num;
            }
        }
    }

    NextFID = maxID;
}
//==========================1. Add Flight Schedules ============================//
void FlightManagement::addFlightSchedule() {

	Flight Fl;
	HelperFlight hf;
	//1. Enter destination
	string Des = hf.readStringDestination();
	//2. Enter Departure Time
	string Dep = hf.readStringDepartureTime();

	//3. Enter Ticket Price
	double TP = hf.readDoubleTicketPrice();

	//4. Update FLT ID by 1
	// Limit FLT ID = 100 Flight
	NextFID++;
	string FID = "FLT" + hf.updateID(NextFID);


	//5. Notify add succesfully
	cout <<"Add successfully *(^O^)* ! \n";

	Fl.setDestination(Des);
	Fl.setDepartureTime(Dep);
	Fl.setTicketPrice(TP);
	Fl.setFlightID(FID);

	listFlight.push_back(Fl);
}
//----------------- 2. DELETE FLIGHT SCHEDULE -----------------//
void FlightManagement::deleteFlightSchedule() {
	HelperFlight hf;

	// 0. Print list Flight
	headerFlight();
	for (auto &f : listFlight)
		f.displayFlight();

	string FID;
	vector<Flight>::iterator it;

	while (true) {
		cout << "Enter Flight ID to DELETE (FLTxxx, e.g., FLT001) \n";
		FID = hf.readStringFID();

		it = findItByFID(FID);

		if (it != listFlight.end()) {
			break; // Found flight - > break loop
		} else {
			cout << "Flight " << FID << " not found! Please try again.\n";
		}
	}

	// 2. Verify Delete
	cout << "Are you sure DELETE " << FID << " ?\n";
	cout << "Enter your choice (Y/N): ";

	string option;
	cin >> option;

	if (option == "Y" || option == "y") {
		listFlight.erase(it);
		cout << "Deleted successfully!\n";

		// 3. Print after processing
		headerFlight();
		for (auto &f : listFlight)
			f.displayFlight();

	} else {
		cout << "Delete cancelled. Return to MAIN MENU.\n";
		return;
	}
}

//==========================3. Update Flight Schedules ========================//
void FlightManagement::updateFlightSchedule() {
	HelperFlight hf;	// Suppoter help read input safety for listFlight

	//0. Show Flight to adjust
	headerFlight ();
	for (const auto &f : listFlight)
		f.displayFlight();

	//1. Enter FlightID need update

	cout << "Enter Flight ID to update (FLTxxx, e.g., FLT001) \n";
	string FID = hf.readStringFID();

	//2. Find Flight in listFlight
	Flight* f = findFlightByFID(FID);

	if (f == nullptr) {
		cout <<"! No exist Flight " << FID <<" !";
		return;
	}

	//3. Adjust new infor
	string Des = hf.readStringDestination();
	string Dep = hf.readStringDepartureTime();
	double TP = hf.readDoubleTicketPrice();

	//4. Update new infor
	f->setDestination(Des);
	f->setDepartureTime(Dep);
	f->setTicketPrice(TP);

	cout << "Update successful! *(^O^)* \n";
	return;

}

//==========================4. Search by Destination ==========================//
void FlightManagement::searchByDestination() {

	HelperFlight hf;
	//1. Enter Destination need to find
	string Des = hf.readStringDestination();

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
	HelperFlight hf;
	//0. Print Header and show all Flight from listFlight
	headerFlight ();
	for(const auto &f : listFlight) {
		f.displayFlight();
	}


	cout <<"Enter FLTID you want to show Renevue (FLTxxx, e.g., FLT001 ): \n";
	string FID = hf.readStringFID();

	Flight *f = findFlightByFID(FID);

	if (f == nullptr) {
		cout << "Flight " << FID << " not found!\n";
		return;
	}

	double revenue = 0;

	// 1. Calc Revenue
	double BusRevenue = 0;
	double EcoRevenue = 0;

	for (const auto &r : RMng.getlistReservation()) {
		if (r.getFIDBooking() == FID) {
			if (r.getSeatClass() == "Economy") {
				revenue += f->getTicketPrice() + 10;
				EcoRevenue +=f->getTicketPrice() + 10;
			}

			else if (r.getSeatClass() == "Business") {
				revenue += f->getTicketPrice() + 100;
				BusRevenue +=f->getTicketPrice() + 100;
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

	for (const auto &f : sortFlight) {
		f.displayFlight();
	}
}

//==========================9. Search by Departure Time =======================//
void FlightManagement::searchByDepartureTime() {

	HelperFlight hf;
	//1. Enter Departure need to FIND
	string Dep = hf.readStringDepartureTime();

	bool found = false;

	//2. show Header
	headerFlight ();

	//3. Find and show Flight
	for (const auto &f : listFlight) {
		if (f.getDepartureTime() == Dep) {
			f.displayFlight();
			found = true;
		}
	}

	//4. If not found Flight
	if (!found)
		cout << "No flight found! (=_=) \n";
	return;
}
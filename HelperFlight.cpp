#include "HelperFlight.h"
#include <iostream>
#include <vector>

using namespace std;

//---------------- READ double Ticket Price for Method FlightManagement ---------------
double HelperFlight::readDoubleTicketPrice() {
	double TP;
	do {
		cout << "Add Ticket Price ( Ticket Price >= 50.00) : ";
		cin >> TP;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid input! Please enter a numeric value.\n";
			continue;
		}

		if (TP < 50) {
			cout << "Ticket price must be at least 50.00. Try again.\n";
			continue;
		}
	} while (TP < 50);
	return TP;
}

//------------------- READ String Destination -----------------//
string HelperFlight::readStringDestination() {
	string Des = "";
	cout << "Enter Destination (e.g., Viet Nam ) : ";
	getline(cin >> ws, Des);

	// Upcase Letter
	for (int i = 0; i < Des.length(); i++)
		Des[i] = toupper(Des[i]);

	return Des;
}

string HelperFlight::readStringDepartureTime() {

	string Dep;

	while (true) {

		cout << "Enter Departure Time (HH:MM, e.g., 14:30): ";
		getline(cin >> ws, Dep);

		int pos = Dep.find(':');

		// Must ':'
		if (pos == string::npos) {
			cout << "Enter Departure Time again!\n";
			continue;
		}

		string hourStr = Dep.substr(0, pos);
		string minStr = Dep.substr(pos + 1);

		// Check if empty
		if (hourStr.empty() || minStr.empty()) {
			cout << "Enter Departure Time again!\n";
			continue;
		}

		bool valid = true;

		// Check hour digit
		for (char c : hourStr) {
			if (!isdigit(c)) {
				valid = false;
				break;
			}
		}

		// Check minute digit
		for (char c : minStr) {
			if (!isdigit(c)) {
				valid = false;
				break;
			}
		}

		if (!valid) {
			cout << "Enter Departure Time again!\n";
			continue;
		}

		int hour = stoi(hourStr);
		int minute = stoi(minStr);

		if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
			cout << "Invalid time! Enter again.\n";
			continue;
		}

		return Dep;
	}
}

//----------------- READ STRING ID -----------------//
string HelperFlight::readStringFID() {

	string FID ="";
	// Upcase FID from user enter keyboard
	cout << "Enter FID : ";
	getline (cin >> ws, FID);

	for (int i=0; i < FID.length(); i++) {
		FID[i]= toupper(FID[i]);
	}

	return FID;
}

//------------------- AUTO UPDATE FID -----------------//
string HelperFlight::updateID(int NextID) {
	string ID ="";
	if (NextID < 10) {
		ID += "00";
	} else if (NextID >= 10 && NextID <= 99) {
		ID += "0";
	} else {
		// Reach limit
		cout << "The flight has reached its maximum capacity ! (-_-) \n";
		return "";
	}
	ID += to_string(NextID);
	return ID;
}

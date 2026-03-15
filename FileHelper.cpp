#include "FileHelper.h"
#include <iostream>
#include <string>
using namespace std;

//---------------- READ double Ticket Price for Method FlightManagement ---------------
double FileHelper::readDoubleTicketPrice() {
	double TP;
	do {
		cout <<"Add Ticket Price ( Ticket Price >= 50.00) : ";
		cin >> TP;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000,'\n');
			cout << "Invalid input! Please enter a number (-_-) ! \n";
			TP = 0;
		}

		if (TP < 50)
			cout <<"Please enter Ticket Price again (-_-) ! \n";
	} while (TP < 50);
	return TP;
}

//------------------- READ String Destination -----------------//
string FileHelper::readStringDestination() {
	string Des = "";
	cout << "Enter Destination (e.g., Viet Nam ) : ";
	getline(cin >> ws, Des);

	// Upcase Letter
	for (int i=0; i < Des.length(); i++)
		Des[i] = toupper(Des[i]);

	return Des;
}

string FileHelper::readStringDepartureTime() {

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
		string minStr  = Dep.substr(pos + 1);

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

//------------------- AUTO UPDATE FLIGHT ID -----------------//
string FileHelper::updateFlightID(unsigned int sizeListFlight) {

	string FID ="FLT"; // FLT xxx

	if (sizeListFlight < 10) {
		FID +="00";
	} else if (sizeListFlight >=10 && sizeListFlight <=99 ) {
		FID +="0";
	} else {																		// Reach limit number of flights
		cout <<"The flight has reached its maximum capacity ! (-_-) \n";
		return "";
	}
	FID += to_string(sizeListFlight);
	return FID;
}

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


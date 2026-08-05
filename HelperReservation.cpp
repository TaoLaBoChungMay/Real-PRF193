#include "HelperReservation.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

//------------------- AUTO UPDATE F/ BK / PAS ID -----------------//
string HelperReservation::updateID(unsigned int nID) {
	string ID ="";
	if (nID < 10) {
		ID += "00";
	} else if (nID >= 10 && nID <= 99) {
		ID += "0";
	} else {
		// Reach limit
		cout << "The flight has reached its maximum capacity ! (-_-) \n";
		return "";
	}
	ID += to_string(nID);
	return ID;
}

//----------------------- READ STRING BID ----------------//
string HelperReservation::readStringBID() {

	string BID ="";
	// Upcase FID from user enter keyboard
	cout << "Enter BID : ";
	getline (cin >> ws, BID);

	for (int i=0; i < BID.length(); i++) {
		BID[i]= toupper(BID[i]);
	}

	return BID;
}

string HelperReservation:: readFullName() {

	string FN = "";
	do {
		cout << "Enter Your Name (length >=2 words) : ";
		getline(cin >> ws, FN);

		if ( FN.size() < 2)
			cout << "Please Enter Your Name Again ! \n";

	} while ( FN.size() < 2 );
	return FN;
}

string HelperReservation:: readSeatType (double Price) {
	int choice =-1;
	string seatType ="";

	do {
		cout <<"Choose Seat Type (1. Economy / 2. Bussiness ) \n" ;
		cout <<"1. Price Economy Seat : " << Price + 10 << endl;
		cout <<"2. Price Business Seat : " << Price + 100 << endl;
		cin >> choice;

		if (choice != 1 && choice != 2)
			cout << "Invalid choice. Please try again.\n";

	} while (choice != 1 && choice != 2);


	if (choice == 1 ) {
		seatType = "Economy";
	} else if (choice == 2) {
		seatType = "Business";
	}
	return seatType;
}


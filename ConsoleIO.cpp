#include <iostream>
#include "ConsoleIO.h"
#include "FileHelper.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

enum MenuOption {
	SAVE_EXIT = 0,

	add_Flight,
	delete_Flight,
	update_Flight,
	search_Destination,
	calc_Revenue,
	display_Passengers,
	sort_FLight_by_Price,
	search_by_Departure_Time,

	book_Ticket,
	cancel_Reservation
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
	cout <<	"2. Delete flight schedules \n";
	cout << "3. Update flight schedules \n";
	cout << "4. Search by Destination \n";
	cout << "5. Calculate total revenue per flight \n";
	cout << "6. Display passenger lists grouped by flight \n";
	cout << "7. Sort flights by Ticket Price (Ascending) \n";
	cout << "8. Search by Departure Time \n";
	cout << "0. BACK MAIN MENU *(^O^)* \n";

	choice = fHelper.readIntChoice(0,9);

	// Return choice
	if (choice == add_Flight || choice ==delete_Flight || choice == update_Flight || choice == search_Destination || choice == calc_Revenue||
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
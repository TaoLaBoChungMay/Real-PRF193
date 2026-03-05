#include <iostream>
#include "ConsoleIO.h"

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
#include <iostream>
#include "ConsoleIO.h"
#include "FlightManagement.h"
int main(int argc, char** argv) {

	ConsoleIO cIO;

	int choice = -1;
	do {
		choice =cIO.showMenu();

		switch (choice) {
			case 1 : {				// 1. Add flight schedules
				break;
			}

			case 2 : {				// 2. Update flight schedules
				break;
			}

			case 3 : {				// 3. Search by Destination

				break;
			}

			case 4 : {				// 4. Calculate total revenue per flight

				break;
			}

			case 5 : {				// 5. Book a ticket
				break;
			}

			case 6 : {				// 6. Cancel reservation

				break;
			}

			case 7 : {				// 7. Display passenger lists grouped by flight

				break;
			}

			case 8 : {				// 8. Sort flights by Ticket Price (Ascending)

				break;
			}

			case 9 : {				// 9. Search by Departure Time

				break;
			}

			case 0 : {				// 0. SAVE & EXIT
				cout <<"Thank you and SAVE before you exit ! ";
				break;
			}
		}
	} while (choice !=0);


	return 0;
}
#include <iostream>
#include <fstream>
#include "ConsoleIO.h"
#include "FlightManagement.h"
#include "ReservationManagement.h"

using namespace std;
int main(int argc, char** argv) {

	ConsoleIO cIO;
	FlightManagement FMng;
	ReservationManagement RMng(FMng);
	cIO.loadData(FMng, RMng);

	int choice = -1;
	do {
		choice =cIO.showMenu();

		switch (choice) {
			case 1 : {				// 1. Add flight schedules
				FMng.addFlightSchedule();
				cIO.askClearScreen ();
				break;
			}

			case 2 : {				// 2. Update flight schedules
				FMng.updateFlightSchedule();
				cIO.askClearScreen ();
				break;
			}

			case 3 : {				// 3. Search by Destination
				FMng.searchByDestination();
				cIO.askClearScreen ();
				break;
			}

			case 4 : {				// 4. Calculate total revenue per flight
				FMng.revenuePerFlight (RMng);
				cIO.askClearScreen ();
				break;
			}

			case 5 : {				// 5. Book a ticket
				RMng.bookTicket();
				cIO.askClearScreen ();
				break;
			}

			case 6 : {				// 6. Cancel reservation
				RMng.cancelReservation();
				cIO.askClearScreen ();
				break;
			}

			case 7 : {				// 7. Display passenger lists grouped by flight
				RMng.displayPassengerGroup();
				cIO.askClearScreen ();
				break;
			}

			case 8 : {				// 8. Sort flights by Ticket Price (Ascending)
				FMng.sortFlightByPrice();
				cIO.askClearScreen ();
				break;
			}

			case 9 : {				// 9. Search by Departure Time
				FMng.searchByDepartureTime();
				cIO.askClearScreen ();
				break;
			}

			case 0 : {				// 0. SAVE & EXIT
				cout <<"Thank you and SAVE before you exit ! ";
				cIO.saveData(FMng, RMng);
				break;
			}
		}
	} while (choice !=0);


	return 0;
}
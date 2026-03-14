#include <iostream>
#include <fstream>
#include "ConsoleIO.h"
#include "FlightManagement.h"
#include "ReservationManagement.h"

using namespace std;

enum MenuOption {
	SAVE_EXIT = 0,

	add_Flight = 1,
	update_Flight = 2,
	search_Destination = 3,
	calc_Revenue = 4,
	display_Passengers = 5,
	sort_FLight_by_Price = 6,
	search_by_Departure_Time = 7,

	book_Ticket = 8,
	cancel_Reservation = 9,
};

int main () {

	ConsoleIO cIO;
	FlightManagement FMng;
	ReservationManagement RMng(FMng);
	cIO.loadData(FMng, RMng);

	int choice = -1;
	do {
		choice = cIO.showMenu();

		switch (choice) {
			case add_Flight : {				// 1. Add flight schedules
				FMng.addFlightSchedule();
				cIO.askClearScreen ();
				break;
			}

			case update_Flight : {				// 2. Update flight schedules
				FMng.updateFlightSchedule();
				cIO.askClearScreen ();
				break;
			}

			case search_Destination : {				// 3. Search by Destination
				FMng.searchByDestination();
				cIO.askClearScreen ();
				break;
			}

			case calc_Revenue : {				// 4. Calculate total revenue per flight
				FMng.revenuePerFlight (RMng);
				cIO.askClearScreen ();
				break;
			}

			case display_Passengers : {				// 7. Display passenger lists grouped by flight
				RMng.displayPassengerGroup();
				cIO.askClearScreen ();
				break;
			}

			case sort_FLight_by_Price : {				// 8. Sort flights by Ticket Price (Ascending)
				FMng.sortFlightByPrice();
				cIO.askClearScreen ();
				break;
			}

			case search_by_Departure_Time : {				// 9. Search by Departure Time
				FMng.searchByDepartureTime();
				cIO.askClearScreen ();
				break;
			}

			case book_Ticket : {				// 5. Book a ticket
				RMng.bookTicket();
				cIO.askClearScreen ();
				break;
			}

			case cancel_Reservation : {				// 6. Cancel reservation
				RMng.cancelReservation();
				cIO.askClearScreen ();
				break;
			}

			case SAVE_EXIT : {				// 0. SAVE & EXIT
				cout <<"Thank you and SAVE before you exit *(^O^)* ";
				cIO.saveData(FMng, RMng);
				break;
			}
		}
	} while (choice !=0);


	return 0;
}
#include <iostream>
#include <fstream>
#include "ConsoleIO.h"
#include "FlightManagement.h"
#include "ReservationManagement.h"

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


using namespace std;
int main(int argc, char** argv) {

	ConsoleIO cIO;
	FlightManagement FMng;
	ReservationManagement RMng(FMng);
	cIO.loadData(FMng, RMng);

	int MenuChoice = -1;
	int subFlightChoice =-1;
	int subReservationChoice =-1;
	do {

		MenuChoice = cIO.showMainMenu();

		switch (MenuChoice) {

			//===================== FLIGHT MANAGEMENT =================//
			case 1: {

				do {

					subFlightChoice = cIO.showFlightMenu();
					
					switch (subFlightChoice) {

						case add_Flight:
							FMng.addFlightSchedule();
							cIO.askClearScreen();
							break;

						case update_Flight:
							FMng.updateFlightSchedule();
							cIO.askClearScreen();
							break;

						case search_Destination:
							FMng.searchByDestination();
							cIO.askClearScreen();
							break;

						case calc_Revenue:
							FMng.revenuePerFlight(RMng);
							cIO.askClearScreen();
							break;

						case display_Passengers:
							RMng.displayPassengerGroup();
							cIO.askClearScreen();
							break;

						case sort_FLight_by_Price:
							FMng.sortFlightByPrice();
							cIO.askClearScreen();
							break;

						case search_by_Departure_Time:
							FMng.searchByDepartureTime();
							cIO.askClearScreen();
							break;

					}

				} while (subFlightChoice != 0);

				break;
			}

			//===================== RESERVATION MANAGEMENT =================//
			case 2: {

				do {

					subReservationChoice = cIO.showReservationMenu();

					switch (subReservationChoice) {

						case book_Ticket:
							RMng.bookTicket();
							cIO.askClearScreen();
							break;

						case cancel_Reservation:
							RMng.cancelReservation();
							cIO.askClearScreen();
							break;

					}

				} while (subReservationChoice != 0);

				break;
			}

			//===================== SAVE & EXIT =================//
			case SAVE_EXIT:
				cout << "Thank you and SAVE before you exit *(^O^)*";
				cIO.saveData(FMng, RMng);
				break;
		}

	} while (MenuChoice != 0);



	return 0;
}
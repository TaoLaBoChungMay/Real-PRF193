#ifndef CONSOLEIO_H
#define CONSOLEIO_H

#include <iostream>
#include "FlightManagement.h"
#include "ReservationManagement.h"
using namespace std;

class ConsoleIO {
	public :
		int showMainMenu ();
		int showFlightMenu ();
		int showReservationMenu ();
		void askClearScreen ();
};

#endif
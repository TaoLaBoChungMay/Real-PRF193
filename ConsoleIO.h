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
		void saveData (FlightManagement &Fmng, ReservationManagement &RMng);
		void loadData (FlightManagement &FMng, ReservationManagement &RMng);
		void askClearScreen ();
};

#endif
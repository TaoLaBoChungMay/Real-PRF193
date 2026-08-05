#ifndef FILEHELPER_H
#define FILEHELPER_H
#include <iostream>
#include "FlightManagement.h"
#include "ReservationManagement.h"
using namespace std;
class FileHelper {
	public :

		int readIntChoice(int min, int max);

		// Save File
		void saveData (FlightManagement &Fmng, ReservationManagement &RMng);

		// Load File
		void loadData (FlightManagement &FMng, ReservationManagement &RMng);
};

#endif
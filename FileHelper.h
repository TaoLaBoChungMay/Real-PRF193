#ifndef FILEHELPER_H
#define FILEHELPER_H
#include <iostream>

using namespace std;
class FileHelper {
	public :
		double readDoubleTicketPrice ();
		string readStringDestination ();
		string readStringDepartureTime ();
		string updateFlightID (unsigned int sizeListFlight);
		int readIntChoice (int min, int max);
};

#endif
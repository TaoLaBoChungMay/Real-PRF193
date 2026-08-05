#ifndef HELPERFLIGHT_H
#define HELPERFLIGHT_H
#include <iostream>
#include <string>
using namespace std;
class HelperFlight {
	public :
		double readDoubleTicketPrice ();
		string readStringDestination ();
		string readStringDepartureTime ();
		string readStringFID();
		string updateID (int NextID);
};

#endif
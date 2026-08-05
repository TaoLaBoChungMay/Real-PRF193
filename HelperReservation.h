#ifndef HELPERRESERVATION_H
#define HELPERRESERVATION_H

#include <iostream>
#include <vector>
using namespace std;
class HelperReservation {
	public :
		string updateID (unsigned int nID);
		string readStringBID ();
		string readFullName ();
		string readSeatType (double Price);
};

#endif
/*
***********************************
Student Name:<Badal Sarkar>
Student#:  <137226189>
Student e-mail: bsarkar2@myseneca.ca
Subject: OOP244
Section:   <SAA>
Topic: Assignment MS 5
***********************************
*/


#ifndef ama_Utilities_H
#define ama_Utilities_h

#include "iProduct.h"
#include"Perishable.h"
#include<iostream>
using namespace std;

namespace ama {
	double& operator+=(double& total, const iProduct& prod);			//adds total cost of prod to total
	ostream& operator<<(ostream& out, const iProduct& prod);
	istream& operator>>(istream& in, iProduct& prod);
	iProduct* createInstance(char tag);
}

#endif
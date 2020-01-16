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

#include <iomanip>
using namespace std;
#include "Product.h"
#include "Perishable.h"
#define _CRT_SECURE_NO_WARNINGS



namespace ama {

	//constructor
	Perishable::Perishable() :Product('P'){
		//empty body
	}





	//function read()
	//this function reads data from either file or user input
	std::istream& Perishable::read(std::istream& in, bool interractive){
		//call base class read function
		Product::read(in, interractive);
		if (interractive) {
			in.clear();
			in.ignore(2000, '\n');
			std::cout <<std::setw(max_length_label)<< std::right<<"Expiry date (YYYY/MM/DD): ";
			in >> productExpiryDate;
			//check if reading was successful
			if (productExpiryDate.status() != no_error) {
				in.setstate(std::ios::failbit);
			}
			//update the errorsstate message 
			switch (productExpiryDate.status()) {
			case error_year:
				message("Invalid Year in Date Entry");
				break;
			case error_mon:
				message("Invalid Month in Date Entry");
				break;
			case error_day:
				message("Invalid Day in Date Entry");
				break;
			case error_input:
				message("Invalid Date Entry");
			}
		}
		else {
			in.ignore(2000, ',');
			//if not interractive
			productExpiryDate.read(in);
		}
		return in;
	}







	//function write()
	//this function writes the product information either 
	//into console or in the file
	ostream& Perishable::write(ostream& out, int writeMode)const{
		//call base class write
		Product::write(out, writeMode);
		if (isClear() && !isEmpty()) {
			//print date
			switch (writeMode) {
			case write_human:
				out << std::setw(max_length_label) << std::right <<"Expiry Date: "<< productExpiryDate<<std::endl;
				break;
			case write_table:
				out << " " << productExpiryDate << " |";
				break;
			case write_condensed:
				out << ", " << productExpiryDate;
			}
		}
		return out;
	}
}


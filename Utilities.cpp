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
#include "Utilities.h"
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS


namespace ama {
	
	//function to add the total cost of the object to 
	//total given as parameter
	double & operator+=(double & total, const iProduct & prod){
		return(total += prod.total_cost());
	}




	//overloaded << operator
	//writes in human format
	std::ostream& operator<<(std::ostream& out, const iProduct& prod){
		prod.write(out, write_human);
		return out;
	}





	//overloaded operator>>
	std::istream& operator>>(istream& in, iProduct& prod) {
		prod.read(in, true);
		return in;
	}




	//function create instance
	//this function instantiates either product or perishable object
	iProduct * createInstance(char tag){
		iProduct* newProduct=nullptr;
		if (tag == 'n' || tag == 'N') {
			newProduct = new Product;
		}
		else if (tag == 'p' || tag=='P') {
			newProduct = new Perishable;
		}
		return newProduct;
	}
}

#endif

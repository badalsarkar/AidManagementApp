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


#ifndef AMA_PERISHABLE_H
#define AMA_PERISHABLE_H


#include "Product.h"
#include "Date.h"


namespace ama {
	class Perishable :public Product {
		Date productExpiryDate;
	public:
		Perishable();
		std::ostream& write(std::ostream& out, int writeMode)const;		//override Product class defination
		std::istream& read(std::istream& in, bool interractive);		//override Product class defination
	};
	
}

#endif
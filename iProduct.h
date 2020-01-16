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


#ifndef AMA_IPRODUCT_H
#define AMA_IPRODUCT_H
#include <iostream>

namespace ama {

	const int max_length_label(30),
		max_length_sku(7),
		max_length_name(75),
		max_length_unit(10),
		write_condensed(0),
		write_table(1),
		write_human(2);
	const double tax_rate = .13;

	//abstract base class
	class iProduct {
	public:
		virtual std::ostream& write(std::ostream& os, int writeMode) const=0;
		virtual std::istream& read(std::istream& is, bool interractive) = 0;
		virtual bool operator==(const char* sku)const = 0;
		virtual double total_cost()const = 0;
		virtual int qtyNeeded()const = 0;
		virtual int qtyAvailable()const = 0;
		virtual const char* name()const = 0;
		virtual int operator+=(int qty) = 0;
		virtual bool operator>(const iProduct& other)const = 0;
		virtual ~iProduct() {};
	};
}



#endif
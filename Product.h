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

#ifndef ama_Product_H
#define ama_Product_H


#include "ErrorState.h"
#include "iProduct.h"

namespace ama {
	class Product:public iProduct {
		const char type;
		char sku[max_length_sku + 1], 
			unit[max_length_unit + 1];
		char * productName;		//resource member
		int quantityOnHand, 
			quantityNeeded;
		double unitPrice;
		bool taxStatus;
        //provides copy functionality
		void init(const char* prodSKU, const char* prodName,const char* prodUnit,		
			double price=0,int qtNeeded=0, int qtHand=0, bool tax=true);
        //for data validation
		bool dataIsValid(const char* prodSKU, const char* prodName,						
			const char* prodUnit, double priceBeforeTax,
			int quantityNeeded, int quantOnHand);
		ErrorState ProductError;														

	public:
		Product(char prodType = 'N');												//default constructor
		Product(const char* prodSKU, const char* prodName,							//constructor
			const char* prodUnit, double Price= 0, 
			int qtNeeded = 0, int qtOnHand = 0, bool taxStatus = true);
		Product(const Product& src);												//copy const
		~Product();																	//destructor
		Product& operator=(const Product& rhs);										//copy assignment
		int operator+=(int cnt);						                            //adds cnt to available quantity
		bool operator==(const char* sku)const;										//match sku
		bool operator>(const char* sku)const;										//compare sku
		bool operator>(const iProduct&)const;										//compare name
		int qtyAvailable() const;													//query available qty
		int qtyNeeded()const;														//query quantity needed
		double total_cost()const;													//returns total cost of qty on hand after tax
		bool isEmpty()const;														//check if obj is empty
		const char* name()const;
		std::istream& read(std::istream& in, bool interractive);					//read from stream and store into obj
		std::ostream& write(std::ostream& out, int writeMode)const;					//write to stream
	protected:
		void message(const char* pText);	//store errorstate message to ProductError
		bool isClear()const;				//checks if ProductError holds a error message
	};
}

#endif

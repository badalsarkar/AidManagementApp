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


#include<iostream>
#include <cstring>
#include<string>
#include <iomanip>
using namespace std;
#include"Product.h"
#include "ErrorState.h"
#define _CRT_SECURE_NO_WARNINGS

namespace ama {


	//default constructor
	Product::Product(char prodType):type(prodType),productName(nullptr){
		//empty
	}




	//custom constructor with 7 argument
	Product::Product(const char * prodSKU, const char * prodName, const char * prodUnit, 
		double price, int qtNeeded, int qtOnHand, bool taxStatus):type('N'), ProductError(){
		//check if the data is valid
		//call init function to store data
		if (dataIsValid(prodSKU, prodName, prodUnit, price, qtNeeded, qtOnHand)) {
			init(prodSKU, prodName, prodUnit, price, qtNeeded, qtOnHand, taxStatus);
		}
		else {
			//if data is not valid, store safe empty
			(*this) = Product();		
		}
	}

	




	//copy constructor
	Product::Product(const Product& src):type(src.type) {
		productName = nullptr;
		init(src.sku, src.productName, src.unit, src.unitPrice, src.quantityNeeded, src.quantityOnHand, src.taxStatus);
	}






	//destructor
	Product::~Product() {
		delete[]productName;
		productName = nullptr;
	}





	//copy assignment
	Product& Product::operator=(const Product& rhs) {
		//check for self assignment
		if (this != &rhs) {
			delete[]productName;
			init(rhs.sku, rhs.productName, rhs.unit, rhs.unitPrice, rhs.quantityNeeded, rhs.quantityOnHand, rhs.taxStatus);
		}
		return *this;
	}






	//Overloaded operator +=
	//this function adds cnt to the qty on hand
	int Product::operator+=(int cnt) {
		if (cnt > 0) {
			quantityOnHand += cnt;
		}
		return quantityOnHand;
	}





	//overloaded operator ==
	//returns true if sku matches 
	bool Product::operator==(const char* sku)const {
		return (strcmp(this->sku, sku) == 0 ? true : false);
	}





	//overloaded operator >
	//returns true if current sku is greater than sku
	bool Product::operator>(const char* sku)const {
		return(strcmp(this->sku, sku) > 0 ? true : false);
	}




	//overloaded operator<
	//returns true if current name is greater that rhs name
	bool Product::operator>(const iProduct& rhs)const {
		return(strcmp(productName, rhs.name()) > 0 ? true : false);
	}




	//this function query the available quantity
	int Product::qtyAvailable()const {
		return quantityOnHand;
	}





	//this function query the quantity needed
	int Product::qtyNeeded()const {
		return quantityNeeded;
	}





	//this function returns total after tax price of 
	//all available unit
	double Product::total_cost()const {
		double totalCost;
		if (taxStatus) {
			totalCost=(quantityOnHand*unitPrice)*(1 + tax_rate);
		}
		else {
			totalCost = (quantityOnHand*unitPrice);
		}
		return totalCost;
	}






	//function to check if object is empty
	bool Product::isEmpty()const {
		return(productName == nullptr ? true : false);
	}




	const char * Product::name() const{
		return productName;
	}



	   	 


	//function init
	//This function copies the parameter into the data members
	void Product::init(const char * prodSKU, const char * prodName, const char * prodUnit, 
		double price, int qtNeeded, int qtHand, bool tax){
		//copy static members
		strncpy(sku, prodSKU, max_length_sku);
		sku[max_length_sku] = '\0';
		strncpy(unit, prodUnit, max_length_unit);
		unit[max_length_unit] = '0';
		unitPrice = price;
		quantityOnHand = qtHand;
		quantityNeeded = qtNeeded;
		taxStatus = tax;
		//resource allocation
		int totalElement = strlen(prodName);
		productName = new(nothrow) char[totalElement+1];
		//memory allocation successful
		if (productName != nullptr) {
			strncpy(productName, prodName, totalElement);
			productName[totalElement] = '\0';
		}
		else {
			//if memory allocation fails, 
			//safe empty state
			productName =nullptr;
		}
	}







	//function to validate data
	bool Product::dataIsValid(const char* prodSKU, const char* prodName,const char* prodUnit, double priceBeforeTax,
		int quantityNeeded, int quantOnHand){
		bool result;
		if (prodName == nullptr || prodName[0] == '\0') {
			result = false;
		}
		else {
			result = (prodSKU == nullptr || prodUnit == nullptr || priceBeforeTax < 0 || quantityNeeded < 0 || quantOnHand < 0) ? false : true;
		}
		return result;
	}






	//this function stores the error status 
	//into the errorstate object of product object
	void Product::message(const char* pText) {
		ProductError.message(pText);
	}





	//this function returns true if the object has no error message
	//false otherwise
	bool Product::isClear()const {
		return((ProductError) ? false : true);
	}




	   	  


	//read function
	//this function reads from stream
	std::istream& Product::read(std::istream& in, bool interractive) {
		//declare temporary variable
		char tempSku[max_length_sku + 1]{ '\0' },
			tempUnit[max_length_unit + 1]{ '\0' },
			tempTax,*tempName = nullptr;
		string name;
		double tempPrice=-1;
		int tempQtyOnHand=-1, tempQtyNeed=-1, tax;
		bool taxStatus=true;
		//if it is interactive
		if (interractive == true) {
			//get SKU from stream
			cout << setw(max_length_label) <<right<< "Sku: ";
			in.get(tempSku, max_length_sku + 1);
			//read name and store dynamically
			if (!in.fail()) {
				in.ignore(2000, '\n');
				//get name from stream
				cout << setw(max_length_label) <<right<< "Name (no spaces): ";
				in >> name;
				if (!in.fail()) {
					in.ignore(2000, '\n');
					//get unit from stream
					cout << setw(max_length_label) <<right<< "Unit: ";
					in.get(tempUnit, max_length_sku + 1);
					if (!in.fail()) {
						in.ignore(2000, '\n');
						//get tax from stream
						cout << setw(max_length_label) <<right<< "Taxed? (y/n): ";
						in.get(tempTax);
						//validate input
						if (!in.fail() && (tempTax == 'y' || tempTax == 'Y' || tempTax == 'n' || tempTax == 'N')) {
							in.ignore(2000, '\n');
							//get price
							cout << setw(max_length_label) <<right<< "Price: ";
							in >> tempPrice;
							if (!in.fail() && tempPrice >= 0) {
								in.ignore(2000, '\n');
								//get qt on hand
								cout << setw(max_length_label) <<right<< "Quantity on hand: ";
								in >> tempQtyOnHand;
								if (!in.fail() && tempQtyOnHand >= 0) {
									in.ignore(2000, '\n');
									//get qt needed
									cout << setw(max_length_label) <<right<< "Quantity needed: ";
									in>>tempQtyNeed;
									if (!in.fail() && tempQtyNeed >= 0) {
										//store name into a cstyle string
										tempName = new(nothrow) char[name.length() + 1];
										if (tempName != nullptr) {
											strcpy(tempName, name.c_str());
										}
										//determine tax status
										taxStatus = (tempTax == 'y' || tempTax == 'Y') ? true : false;
										//copying to the object
										delete[] productName;
										init(tempSku, tempName, tempUnit, tempPrice, tempQtyNeed, tempQtyOnHand, taxStatus);
									}
									else {
										//error state for qty needed
										in.setstate(ios::failbit);
										message("Invalid Quantity Needed Entry!");
									}
								}
								else {
									//error state for qty on hand
									in.setstate(ios::failbit);
									message("Invalid Quantity Available Entry!");
								}
							}
							else {
								//error state for price
								in.setstate(ios::failbit);
								message("Invalid Price Entry!");
							}
						}
						else {
							//error state for tax
							in.setstate(ios::failbit);
							message("Only (Y)es or (N)o are acceptable!");
						}
					}
				}
			}
		}
		else {
			//if not interractive
			in.getline(tempSku, max_length_sku + 1, ',');
			//read the name from the stream
			//dynamically allocate memory for c style string
			getline(in, name, ',');
			//delete::://readingStat = in.fail();
			tempName = new char[name.length() + 1];
			if (tempName != nullptr) {
				strcpy(tempName, name.c_str());
			}
			//read unit from stream
			in.getline(tempUnit, max_length_unit + 1, ',');
			//read price from unit
			in >> tempPrice;
			in.ignore();
			//read tax from stream
			in >> tax;
			taxStatus = (tax > 0) ? true : false;
			in.ignore();
			in >> tempQtyOnHand;
			in.ignore();
			in >> tempQtyNeed;
			//store into the object
			if (!in.fail()) {
				if (dataIsValid(tempSku, tempName, tempUnit, tempPrice, tempQtyNeed, tempQtyOnHand)) {
					//deallocate existing resource
					delete[] productName;
					init(tempSku, tempName, tempUnit, tempPrice, tempQtyNeed, tempQtyOnHand, taxStatus);
				}
			}
		}
		//deallocate temporary resource
		delete[] tempName;
		tempName = nullptr;
		return in;
	}







	//function write
	//this function write to stream
	std::ostream& Product::write(std::ostream& out, int writeMode)const {
		//check error message
		if (isClear()){
			//if empty don't do anything
			if(!isEmpty()){
				switch (writeMode) {
				case write_condensed:
					out << type << "," << sku << "," << productName << ","
						<< unit << "," << fixed<<setprecision(2) << unitPrice << ","
						<< taxStatus << "," << quantityOnHand << "," 
						<< quantityNeeded;
					break;
				case write_table:
					if (strlen(productName) > 16) {
						out << " " << setw(max_length_sku) << right << sku << " | ";
						for (int i = 0; i < 13; i++) {
							out << left << productName[i];
						}
						out << "... | ";
						out<<setw(10)<<left<<unit<<" | "
							<<setw(7)<<fixed<<setprecision(2)<<right<<unitPrice<<" | "
							<<setw(3)<<right<<(taxStatus==0?"no":"yes")<<" | "
							<<setw(6)<<right<<quantityOnHand<<" | "
							<<setw(6)<<right<<quantityNeeded<<" |";
					}
					else {
						out << " " << setw(max_length_sku) << right << sku << " | ";
						out <<setw(16)<< left << productName<<" | "
							<< setw(10) <<left<<unit << " | "
							<< setw(7) << setprecision(2) <<right<< unitPrice << " | "
							<< setw(3) <<right<< (taxStatus == 0 ? "no" : "yes") << " | "
							<< setw(6) << right<<quantityOnHand << " | "
							<< setw(6) << right<<quantityNeeded << " |";
					}
					break;
				case write_human:
					out << setw(max_length_label) <<right<< "Sku: " << sku << endl;
					out << setw(max_length_label) <<right<< "Name: " << productName << endl;
					out << setw(max_length_label) <<"Price: " <<fixed<<setprecision(2)<< right<<unitPrice << endl;
					out << setw(max_length_label) << "Price after Tax: " <<fixed<<setprecision(2)<<right<<(taxStatus?(unitPrice*(1+tax_rate)):unitPrice)<< endl;
					out << setw(max_length_label) <<right<< "Quantity Available: " << quantityOnHand <<" "<<unit<< endl;
					out << setw(max_length_label) <<right<< "Quantity Needed: " << quantityNeeded <<" "<<unit<< endl;
				}//end of switch
			}
		}
		else {
			//print the error message
			out << this->ProductError;
		}
		return out;
	}
}
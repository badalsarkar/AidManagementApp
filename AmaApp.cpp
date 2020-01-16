#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
using namespace std;
#include "AmaApp.h"
#include "Utilities.h"
#define _CRT_SECURE_NO_WARNINGS

namespace ama {
	//custom constructor
	AmaApp::AmaApp(const char fileName[]) :m_filename{ '\0' }, m_products{ nullptr }, m_noOfProducts(0){
		if (fileName!= nullptr&&fileName[0]!='\0') {
			std::strncpy(m_filename, fileName, 255);
			m_filename[256] = '\0';
		}
		//load the prduct records from the file
		loadProductRecords();
	}




	//function to deallocate all dynamic memory
	//the function traverse through m_Products array
	//and deallocate memory for object
	void AmaApp::deleteElements() {
		for (int i = 0; i < m_noOfProducts; i++) {
			delete m_products[i];
			m_products[i] = nullptr;
		}
	}




	//destructor
	AmaApp::~AmaApp() {
		//deallocate all dynamic memory
		deleteElements();
	}





	//function pause()
	//this function pauses the execution at console
	void AmaApp::pause()const {
		cout << "Press Enter to continue...";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}






	//function menu()
	//show the menue to the user and accept user input
	//returns -1 if invalid input
	int AmaApp::menu()const {
		int userSelection = 0;
		cout << "Disaster Aid Supply Management Program" << '\n' <<
			"--------------------------------------" << '\n' <<
			"1- List products" << '\n' <<
			"2- Search product" << '\n' <<
			"3- Add non-perishable product" << '\n' <<
			"4- Add perishable product" << '\n' <<
			"5- Add to product quantity" << '\n' <<
			"6- Delete product" << '\n' <<
			"7- Sort products" << '\n'<<
			"0- Exit program" << '\n' <<
			"> ";
		cin >> userSelection;
		//clear the input buffer
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		//validate user input
		if (userSelection<0&&userSelection>7) {
			userSelection = -1;
		}
		return userSelection;
	}






	//function loadProductRecords()
	//this funciton loads product information from the file
	//if the file is not found it creates an empty file
	void AmaApp::loadProductRecords() {
		int readIndex = 0;
		//delete existing content from m_product
		deleteElements();
		std::ifstream file(m_filename);
		if (file.is_open()) {
			//read m_products_size number of records 
			//and until eof is reached
			//the loop reads one line from the file
			for (int i = 0; i < m_products_size && (!file.eof()); i++) {
				bool continueReading = false;
				//read first character from file
				//use this character to create instance of 
				//either product or perishable object
				char tempvar = file.get();
				iProduct* temp = createInstance(tempvar);
				//check if object is created
				//if created store it in m_products array
				//continue with further reading
				//if not created clear the whole line
				if (temp != nullptr) {
					m_products[i] = temp;
					continueReading = true;
				}
				else {
					file.clear();
					file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}

				//when object creation successful
				//read the rest of the line
				//store it in the member variables
				if (continueReading) {
					file.ignore(2000,',');
					//read in non-interractive mode
					m_products[i]->read(file, false);
					file.ignore(2000, '\n');
					readIndex++;
				}
			}	//loop
			file.clear();
			file.close();
		}
		else {
			//file not opened
			//create empty file
			std::ofstream file(m_filename);
			file.close();
		}
		//update the no of products in the file
		m_noOfProducts = readIndex;
	}







	//this function saves the product record 
	//stored in the m_products array into the file
	void AmaApp::saveProductRecords()const {
		//check if there are records in the array
		if (m_noOfProducts > 0) {
			ofstream file(m_filename);
			if (file.is_open()) {
				//write data in condensed mode
				for (int i = 0; i < m_noOfProducts; i++) {
					m_products[i]->write(file, write_condensed);
					file << endl;
				}
			}
		}
	}






	//function to print title into the console
	void AmaApp::printTitle()const{
		cout << "------------------------------------------------------------------------------------------------" << '\n'
			<< "|" << setw(4) << right << "Row" << " |"
			<< setw(8) << right << "SKU" << " |"
			<< setw(17) << left << " Product Name" << " |"
			<< setw(11) << left << " Unit" << " |"
			<< setw(8) << right << "Price" << " |"
			<< setw(4) << right << "Tax" << " |"
			<< setw(7) << right << "QtyA" << " |"
			<< setw(7) << right << "QtyN" << " |"
			<< setw(11) << left << " Expiry" << " |" << '\n'
			<< "|-----|---------|------------------|------------|---------|-----|--------|--------|------------|" << endl;
	}








	//this function prints the footer including the total cost
	void AmaApp::printFooter(double totalCost)const
	{
		cout << "------------------------------------------------------------------------------------------------" << '\n'
			<< "|" << setw(83) << right << "Total cost of support ($): | "
			<< setprecision(2) << fixed << setw(10) << right << totalCost << " |" << '\n'
			<< "------------------------------------------------------------------------------------------------" << endl << endl;
	}








	//this function prints the product infromation
	//stored in the file into the console in table format
	void AmaApp::listProducts()const {
		double totalCost=0;
		printTitle();
		//print product information
		for (int i = 0; i < m_noOfProducts; i++) {
			cout << "|" << setw(4) << right << i + 1 << " |";
			m_products[i]->write(cout, write_table);
			cout << endl;
			//calculate total cost
			totalCost += *m_products[i];
		}
		//print the footer with total cost
		printFooter(totalCost);
		pause();
	}







	//this function finds the SKU parameter in the m_products array
	//returns the address if found, otherwise nullptr
	iProduct* AmaApp::find(const char* skuToFind)const {
		iProduct* result=nullptr;
		bool skuFound=false;
		for (int i = 0; i < m_noOfProducts && !skuFound; i++) {
			if (*(m_products[i]) == skuToFind) {
				result = m_products[i];
				skuFound = true;
			}
		}
		return result;
	}







	//function addQty
	//this function display the existing record of the product parameter
	//then ask user to input desired quantity
	//adds the quantity to the quantity on hand
	//save the updated record in the file
	//the maximum quantity acceptable is qtyNeeded - qtyAvailable
	void AmaApp :: addQty(iProduct* product) {
		int qty;
		int maxQty;
		cout << *product << endl << endl
			<< "Please enter the number of purchased items: ";
		cin >> qty;
		//if the reading was successful, find the max qty needed
		//if reading was not successful print error msg
		if (!cin.fail()) {
			maxQty = product->qtyNeeded() - product->qtyAvailable();
			//only accept qty which is less than/equal max qty
			if (qty <= maxQty) {
				*product += qty;
			}
			else {
				//if there is extra qty print message
				*product += maxQty;
				cout << "Too many items; only " << maxQty
					<< " is needed. Please return the extra "
					<< (qty - maxQty) << " items." << endl;
			}
			//update the file
			saveProductRecords();
			cout << endl << "Updated!" << endl;
		}
		else {
			//prints error message
			cout<<"Invalid quantity value!"<<endl;
		}
		//clear error state
		cin.clear();
		//flush buffer
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}








	//function to add product
	//this function adds new product into the array
	//get product information from the user
	//update the file
	void AmaApp::addProduct(char tag) {
		//create instance
		iProduct* newProduct = createInstance(tag);
		if (newProduct != nullptr) {
			//read information from the stream
			cin >> *newProduct;
		}
		//check if reading was successful
		if (cin.rdstate()==0) {
			//add to the iProducts array
			m_products[m_noOfProducts] = newProduct;
			m_noOfProducts++;
			//save product info ino the file
			saveProductRecords();
			cout << endl << "Success!" << endl;
		}
		else {
			//print error message
			cin.clear();
			cin.ignore(2000, '\n');
			cout << endl<<*newProduct<<endl;
		}
	}









	//function to get SKU input from user
	//this function ask user to input a SKU
	//returns the SKU
	const char* AmaApp::getSKUfromUser(char* skuToFind)const {
		cout << "Please enter the product SKU: ";
		cin.get(skuToFind, max_length_sku + 1, '\n');
		//clear error state if any
		cin.clear();
		//clear buffer
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return(skuToFind[0] != '\0' ? skuToFind : nullptr);
	};








	//function run()
	//this function provides the user interaction functionality
	int AmaApp::run() {
		int userSelection = 0;
		iProduct* tempProduct;
		char skuToFind[max_length_sku + 1];
		do {
			//show the menu
			userSelection = menu();
			switch (userSelection){
			case 1:
				listProducts();
				break;
			case 2:
				getSKUfromUser(skuToFind);
				tempProduct = find(skuToFind);
				if (tempProduct != nullptr) {
					//display product info in human redable form
					cout << endl<<*tempProduct<<endl;
				}
				else {
					cout <<endl<< "No such product!" << endl;
				}
				pause();
				break;
			case 3:
				addProduct('N');
				loadProductRecords();
				break;
			case 4:
				addProduct('P');
				loadProductRecords();
				break;
			case 5:
				getSKUfromUser(skuToFind);
				tempProduct = find(skuToFind);
				cout << endl;
				if (tempProduct != nullptr) {
					addQty(tempProduct);
				}
				else {
					cout << "No such product!" << endl;
				}
				break;
            case 6:
                cout<<"This feature has not been implemented"<<endl;
                break;
            case 7:
                cout<<"This feature has not been implemented"<<endl;
                break;
			case 0:
				cout << "Goodbye!";
				break;
			default:
				cout << "~~~Invalid selection, try again!~~~" << endl;
				pause();
			}
			cout << endl;
		} while (userSelection != 0);
		return 0;
	}
}

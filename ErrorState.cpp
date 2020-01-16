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
#include<cstring>
#include"ErrorState.h"
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

namespace ama {

	//default constructor
	ErrorState::ErrorState(const char* errorMessage){
		init(errorMessage);
	}


	//destructor
	ErrorState::~ErrorState() {
		delete[]errorStateMsg;
		errorStateMsg = nullptr;
	}



	//bool operator
	//returns true if there is error
	ErrorState::operator bool() const{
		return(errorStateMsg != nullptr ? true : false);
	}



	
	//operator=
	//this function sotres the text in the parameter
	//into the data member
	ErrorState & ErrorState::operator=(const char * pText){
		delete[] errorStateMsg;
		init(pText);
		return *this;
	}





	//message function
	void ErrorState::message(const char* pText) {
		delete[] errorStateMsg;
		init(pText);
	}




	//function to query stored message
	const char* ErrorState::message() const {
		return((errorStateMsg) ? errorStateMsg : nullptr);
	}




	//function to validate message
	bool ErrorState::dataIsValid(const char* message)const{
		return ((message != nullptr&&message[0] != '\0') ? true : false);
	}





	//function init
	//this function provides the copy functionality
	void ErrorState::init(const char* message) {
		if (dataIsValid(message)) {
			//allocate dynamic memory
			int totalElement = strlen(message);
			errorStateMsg = new (nothrow) char[totalElement + 1];
			//if memory allocation is successful
			//store message into member
			if (errorStateMsg != nullptr) {
				strncpy(errorStateMsg, message, totalElement);
				errorStateMsg[totalElement] = '\0';
			}
			//if memory not allocated
			else {
				errorStateMsg = nullptr;
			}
		}
		//when data is not valid
		else {
			errorStateMsg = nullptr;
		}
	}
}



//function operator<<
std::ostream& operator<<(std::ostream& os, const ama::ErrorState& src){
	if (src.message() != nullptr) {
		os << src.message();
	}
	return os;
}
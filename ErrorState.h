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


#ifndef error_ama_h
#define error_ama_h
#include<iostream>

namespace ama {
	class ErrorState {
		char * errorStateMsg;
		bool dataIsValid(const char* message)const;
		void init(const char* message);
	public:
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState(const ErrorState& other) = delete;
		ErrorState& operator=(const ErrorState& other) = delete;
		~ErrorState();
		operator bool() const;
		ErrorState& operator=(const char* pText);
		void message(const char* pText);
		const char* message() const;
	};
}
//helper function 
std::ostream& operator<<(std::ostream& os, const ama::ErrorState& src);


#endif
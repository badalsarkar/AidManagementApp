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


#ifndef ama_date_h
#define ama_date_h
#include<iostream>

namespace ama {
	//declare constants
	const int min_year = 2019;
	const int max_year = 2028;
	const int no_error = 0;
	const int error_year = 1;
	const int error_mon = 2;
	const int error_day = 3;
	const int error_invalid_operation = 4;
	const int error_input = 5;

	//class declaration
	class Date {
		int year;
		int month;
		int day;
		int dateStatus;
		void status(int);
		int mdays(int year, int mon) const;
		int validateDate(int, int, int)const;

	public:
		Date();
		Date(int, int, int);
		int status();
		void clearError();
		bool isGood();
		Date& operator+=(int days);
		Date& operator++();
		Date operator++(int);
		Date operator+(int);
		bool operator==(const Date&);
		bool operator!=(const Date&);
		bool operator<(const Date&);
		bool operator>(const Date&);
		bool operator<=(const Date&);
		bool operator>=(const Date&);
		std::ostream& write(std::ostream& os)const;
		std::istream& read(std::istream& is);
	};

	//helper function
	std::ostream& operator<<(std::ostream&, const Date&);
	std::istream& operator>>(std::istream&, Date&);
}
#endif
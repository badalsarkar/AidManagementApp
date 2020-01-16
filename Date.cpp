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
#include<iomanip>
#include "Date.h"
using namespace std;
#define _CRT_SECURE_NO_WARNINGS



namespace ama {

	//default constructor
	Date::Date(){
		year = month = day = dateStatus = 0;
	}




	//this function updates the status with the parameter value
	void Date::status(int newStatus){
		dateStatus = newStatus;
	}




	//this function find the last day of a given month
	int Date::mdays(int year, int mon)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}




	


	//function to validate data
	int Date::validateDate(int yr, int mon, int dy)const
	{
		bool validYr, validMon, validDy;
		int result, maxDay = mdays(yr, mon);
		//check if value within range
		validYr = (yr >= min_year && yr <= max_year);
		validMon = (mon > 0 && mon < 13);
		validDy = (dy > 0 && dy < maxDay + 1);
		if (!validYr) {
			result = error_year;
		}
		else if (!validMon) {
			result = error_mon;
		}
		else if (!validDy) {
			result = error_day;
		}
		else {
			result = no_error;
		}
		return result;
	}








	//custom constructor
	Date::Date(int yr, int mon, int dy) {
		//store if data is valid
		int dataStatus = validateDate(yr, mon, dy);
		if (dataStatus==no_error) {
			year = yr;
			month = mon;
			day = dy;
			dateStatus = no_error;
		}
		//if data not valid put into safe empty state
		else {
			*this = Date();
			dateStatus = dataStatus;
		}
	}







	//this function returns the status
	int Date::status() {
		return dateStatus;
	}




	//function to clear error
	void Date::clearError() {
		dateStatus = no_error;
	}






	//function isGood
	bool Date::isGood() {
		return((year != 0 && month != 0 && day != 0 && dateStatus == no_error) ? true : false);
	}







	//function to overload +=
	//this function adds the days in the parameter
	//into the data member
	Date& Date::operator+=(int days) {
		int newDays;
		//checking if object has valid data and no error
		if (isGood()) {
			int maxDay = mdays(year, month);
			newDays = day + days;
			//checking if new day will be within range
			if (newDays>=1&&newDays<= maxDay) {
				day = newDays;
			}
			else {
				dateStatus = error_invalid_operation;
			}
		}
		else {
			dateStatus = error_invalid_operation;
		}
		return *this;
	}








	//function to overload operator ++
	//this function increase the day by 1
	Date& Date::operator++() {
		*this += 1;
		return *this;
	}






	//functioin to overload operator ++ postfix
	//increase the day by 1 in postfix manner
	Date Date::operator++(int num) {
		Date temp = *this;
		//call prefix operator
		++(*this);
		return temp;
	}






	//function to overload operator +
	//this function adds days in parameter to the day
	Date Date::operator+(int days) {
		Date temp = *this;
		temp += days;
		return temp;
	}






	//function to overload operator ==
	//this function check if two object is identical
	bool Date::operator==(const Date& rhs) {
		return((year == rhs.year)&&(month == rhs.month)&&(day == rhs.day));
	}





	//function to overload operator!=
	//this function checks if two objects are different
	bool Date::operator!=(const Date& rhs) {
		return(!(*this == rhs));
	}




	//function to overload operator <
	//this function compares two objects
	bool Date::operator<(const Date& rhs) {
		bool result;
		if (year < rhs.year) {
			result = true;
		}
		else if (month < rhs.month) {
			result = true;
		}
		else if (day < rhs.day) {
			result = true;
		}
		else {
			result = false;
		}
		return result;
	}





	

	//function to overload operator >
	//this function compares two objects
	bool Date::operator>(const Date& rhs) {
		return((*this == rhs || *this < rhs) ? false : true);
	}






	//function to overload operator<=
	//this function compares two objects
	bool Date::operator<=(const Date& rhs) {
		return((*this < rhs || *this == rhs) ? true : false);
	}




	
	//function to overload operator >=
	//this function compares two objects
	bool Date::operator>=(const Date& rhs) {
		return((*this > rhs || *this == rhs) ? true : false);
	}





	//function to write to output stream
	std::ostream& Date::write(std::ostream& os)const {
		os << setfill('0') << setw(4)<<right<< year << "/" << setw(2) << month << "/" << setw(2) << day; 
		os<< setfill(' ');
		return os;
	}






	//function to read from input stream
	std::istream& Date::read(std::istream& is) {
		int yr=0, mon=0, dy=0;
		int readFailCount=0;
		is >> yr;
		//check if the reading failed
		if (is.fail()) {
			readFailCount++;
		}
		is.ignore();
		is >> mon;
		if (is.fail()) {
			readFailCount++;
		}
		is.ignore();
		is >> dy;
		//delete::://is.ignore();
		if (is.fail()) {
			readFailCount++;
		}
		//if read failed
		if (readFailCount > 0) {
			*this = Date();
			this->dateStatus = error_input;
		}
		else {
			*this = Date(yr, mon, dy);
		}
		return is;

	}




	/*
	*************************************
	helper functions
	*************************************
	*/
	//overloading << operator
	std::ostream& operator<<(std::ostream& os, const Date& outputDate) {
		outputDate.write(os);
		return os;
	}



	
	//overloading >>operator
	std::istream& operator>>(std::istream& is, Date& inputDate) {
		inputDate.read(is);
		return is;
	}
}

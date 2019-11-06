#pragma once
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


class Date {
public:
	Date(int new_year, int new_month, int new_day);
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

private:
	int year;
	int day;
	int month;
};

bool operator<(const Date& a, const Date& b);
bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);
bool operator<=(const Date& a, const Date& b);
bool operator>(const Date& a, const Date& b);
bool operator>=(const Date& a, const Date& b);

ostream& operator<<(ostream& stream, const Date& date);
Date ParseDate(istream& date_stream);

#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "date.h"
using namespace std;

// конструктор выбрасывает исключение, если его аргументы некорректны
Date::Date(int new_year, int new_month, int new_day){
	year = new_year;
	if (new_month > 12 || new_month < 1) {
		throw logic_error("Month value is invalid: " + to_string(new_month));
	}
	month = new_month;
	if (new_day > 31 || new_day < 1) {
		throw logic_error("Day value is invalid: " + to_string(new_day));
	}
	day = new_day;
}

int Date::GetYear() const {
	return year;
}
int Date::GetMonth() const {
	return month;
}
int Date::GetDay() const {
	return day;
}

// определить сравнение для дат необходимо для использования их в качестве ключей словаря
bool operator<(const Date& lhs, const Date& rhs) {
	// воспользуемся тем фактом, что векторы уже можно сравнивать на <:
	// создадим вектор из года, месяца и дня для каждой даты и сравним их
	return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
		vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator==(const Date& a, const Date& b)
{
	return a.GetYear() == b.GetYear() && a.GetMonth() == b.GetMonth() && a.GetDay() == b.GetDay();
}

bool operator!=(const Date& a, const Date& b)
{
	return !(a == b);
}

bool operator<=(const Date& a, const Date& b)
{
	return (a < b) || (a == b);
}

bool operator>(const Date& a, const Date& b)
{
	return (a != b) && !(a < b);
}

bool operator>=(const Date& a, const Date& b)
{
	return (a > b) || (a == b);
}


// даты будут по умолчанию выводиться в нужном формате
ostream& operator<<(ostream& stream, const Date& date) {
	stream << setw(4) << setfill('0') << date.GetYear() <<
		"-" << setw(2) << setfill('0') << date.GetMonth() <<
		"-" << setw(2) << setfill('0') << date.GetDay();
	return stream;
}

Date ParseDate(istream& date_stream) {
	//istringstream date_stream(date);
	bool ok = true;

	int year;
	date_stream >> year;
	date_stream.ignore(1);

	int month;
	date_stream >> month;
	date_stream.ignore(1);

	int day;
	date_stream >> day;

	return Date(year, month, day);
}
#include <string>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include "date.h"
#include "database.h"

using namespace std;


void Database::Add(const Date& date, const string& event) {
	if (storage.count(date) == 0 || Set[date].count(event) == 0) {
		storage[date].push_back(event);
		Set[date].insert(event);
	}
}

pair<Date,string> Database::Last(const Date& date) const {
	if (date < storage.begin()->first || storage.empty()) {
		throw invalid_argument("invalid_argument");
	}
	auto it = --(storage.upper_bound(date));
	return { it->first,it->second.back() };
}

void Database::Print(ostream& os) const { //оставляем как есть
	for (const auto& item : storage) {
		for (const string& event : item.second) {
			os << item.first << " " << event << endl;
		}
	}
}

ostream& operator<<(ostream& stream, const pair<Date, string>& p) {
	return stream << p.first << " " << p.second;
};

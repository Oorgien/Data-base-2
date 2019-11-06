#pragma once
#include <string>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "date.h"

class Database {
public:
	void Add(const Date& date, const string& event);
	template<class F>
	vector<pair<Date, string>> FindIf(F predicate) const {
		vector<pair<Date, string>> revealedPair;
		auto it_storage = storage.begin();

		while (it_storage != storage.end()) {

			auto it_events = it_storage->second.begin();
			while (it_events != it_storage->second.end()) {

				it_events = find_if(it_events, it_storage->second.end(),
					[&](const string str) { return predicate(it_storage->first, str); });
				if (it_events != it_storage->second.end()) {
					revealedPair.emplace_back(it_storage->first, *it_events);
					++it_events;
				};
			}
			++it_storage;
		}
		return revealedPair;
	};
	template <class F>
	int RemoveIf(F predicate) {
		int k = 0;
		auto it_storage = begin(storage);
		while (it_storage != end(storage)) {
			auto it_events = stable_partition(it_storage->second.begin(), it_storage->second.end(),
				[&](const string str) { return !predicate(it_storage->first, str); });
			//предикат верен - в конец
			if (it_events != it_storage->second.end()) {
				k += distance(it_events, it_storage->second.end());
				it_storage->second.erase(it_events, it_storage->second.end());
				Set[it_storage->first].clear();
				Set[it_storage->first].insert(it_storage->second.begin(), it_storage->second.end());
			};

			if (it_storage->second.empty()) {
				Set.erase(it_storage->first);
				it_storage = storage.erase(it_storage);
			}
			else {
				++it_storage;
			}
		}
		return k;
	}
	pair<Date, string> Last(const Date& date) const;
	void Print(ostream& os) const;
private:
	map<Date, set<string>> Set;
	map<Date, vector<string>> storage;
};

ostream& operator<<(ostream& stream, const pair<Date, string>& p);
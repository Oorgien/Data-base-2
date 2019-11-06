#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "database.h"

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <iterator>

using namespace std;

string ParseEvent(istream& is) {
  // Реализуйте эту функцию
	string line;
	getline(is, line);
	auto p1 = find_if(begin(line), end(line), [](const char& c) {return c != ' '; });
	string event = string(p1, end(line));
	//auto p2 = find_if(event.rbegin(), event.rend(), [](const char& c) {return c != ' '; });
	//string res = string(event.rend(),p2);
	return event;
}



int main() {


  Database db;

  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    } else if (command == "Print") {
      db.Print(cout);
    } else if (command == "Del") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;
    } else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
      try {
          cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
          cout << "No entries" << endl;
      }
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }

  return 0;
}


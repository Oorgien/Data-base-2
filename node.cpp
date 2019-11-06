#include "node.h"
using namespace std;

template <class T>
bool Compare(Comparison cmp,const T& a, const T& b) {
	switch (cmp) {
	case Comparison::Equal:
		return a == b;
	case Comparison::Greater:
		return a > b;
	case Comparison::GreaterOrEqual:
		return a >= b;
	case Comparison::Less:
		return a < b;
	case Comparison::LessOrEqual:
		return a <= b;
	case Comparison::NotEqual:
		return a != b;
	}

	throw invalid_argument("Invalid logical operation");
}

bool EmptyNode::Evaluate(const Date& date, const string& event) const  {
	return true;
}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const  {
	return Compare(cmp_, date, date_);
}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
	return Compare(cmp_, event, event_);
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
	switch (op_)
	{
	case LogicalOperation::Or:
		return left_->Evaluate(date, event) || right_->Evaluate(date, event);

	case LogicalOperation::And:
		return left_->Evaluate(date, event) && right_->Evaluate(date, event);
	}

	throw invalid_argument("Invalid logical operation");
}
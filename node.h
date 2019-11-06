#pragma once
#include <memory>
#include "date.h"
using namespace std;

enum class Comparison
{
	Less, LessOrEqual,
	Greater, GreaterOrEqual,
	Equal, NotEqual
};

enum class LogicalOperation {
	Or,
	And
};

struct Node {	//������������ ����� �����
	virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

struct EmptyNode : public Node {	//������ ����
	EmptyNode() {}
	bool Evaluate(const Date& date, const string& event) const override;
};

struct DateComparisonNode : public Node {	//���� ��������� ���
public:	
	DateComparisonNode(Comparison cmp, const Date& date) : cmp_(cmp), date_(date) {}
	bool Evaluate(const Date& date, const string& event) const override;
private:
	Comparison cmp_;
	Date date_;
};

struct EventComparisonNode : public Node {	//���� ��������� �������
public:
	EventComparisonNode(Comparison cmp, const string& event) : cmp_(cmp), event_(event) {}
	bool Evaluate(const Date& date, const string& event) const override;
private:
	Comparison cmp_;
	string event_;
};

struct LogicalOperationNode : public Node {	//���� ���������� ��������
public:
	LogicalOperationNode(LogicalOperation op, shared_ptr<Node> left, shared_ptr<Node> right) : op_(op), left_(left), right_(right) {}
	bool Evaluate(const Date& date, const string& event) const override;
private:
	LogicalOperation op_;
	shared_ptr<Node> left_;
	shared_ptr<Node> right_;
}; 


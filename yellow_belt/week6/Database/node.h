#pragma once

#include <vector>
#include <memory>

#include "token.h"
#include "date.h"

using namespace std;

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum class LogicalOperation {
	Or,
	And
};

class Node {
public:
	Node() {}
	virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node {
public:
	EmptyNode() {}
	bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison& cmp, const Date& date);
	bool Evaluate(const Date& date, const string& event) const override;

private:
	const Comparison cmp_;
	const Date date_;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(const Comparison& cmp, const string& event);
	bool Evaluate(const Date& date, const string& event) const override;

private:
	const Comparison cmp_;
	const string event_;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(const LogicalOperation& op, const shared_ptr<Node>& lhs, const shared_ptr<Node>& rhs);
	bool Evaluate(const Date& date, const string& event) const override;

private:
	const LogicalOperation op_;
	const shared_ptr<Node> lhs_, rhs_;
};
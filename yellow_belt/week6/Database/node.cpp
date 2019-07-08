#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
	return true;
}


DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date) : cmp_(cmp), date_(date) {}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
	if (cmp_ == Comparison::Equal) {
		return date == date_;
	}
	else if (cmp_ == Comparison::Greater) {
		return date > date_;
	}
	else if (cmp_ == Comparison::GreaterOrEqual) {
		return date >= date_;
	}
	else if (cmp_ == Comparison::Less) {
		return date < date_;
	}
	else if (cmp_ == Comparison::LessOrEqual) {
		return date <= date_;
	}
	else if (cmp_ == Comparison::NotEqual) {
		return date != date_;
	}
	return false;
}


EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& event) : cmp_(cmp), event_(event) {}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
	if (cmp_ == Comparison::Equal) {
		return event == event_;
	}
	else if (cmp_ == Comparison::Greater) {
		return event > event_;
	}
	else if (cmp_ == Comparison::GreaterOrEqual) {
		return event >= event_;
	}
	else if (cmp_ == Comparison::Less) {
		return event < event_;
	}
	else if (cmp_ == Comparison::LessOrEqual) {
		return event <= event_;
	}
	else if (cmp_ == Comparison::NotEqual) {
		return event != event_;
	}
	return false;
}


LogicalOperationNode::LogicalOperationNode(const LogicalOperation& op,
	const shared_ptr<Node>& lhs, const shared_ptr<Node>& rhs) : op_(op), lhs_(lhs), rhs_(rhs) {}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
	if (op_ == LogicalOperation::Or) {
		return (lhs_->Evaluate(date, event) || rhs_->Evaluate(date, event));
	}
	else if (op_ == LogicalOperation::And) {
		return (lhs_->Evaluate(date, event) && rhs_->Evaluate(date, event));
	}
	return true;
}

#include "pch.h"
#include "FlowFinder.h"

TEST(FlowFinder, constructor) {
	FlowFinder test("input.txt");
	ASSERT_EQ(test.head->name, 'S');
	ASSERT_EQ(test.tail->name, 'T');
}

TEST(FlowFinder, findFlow) {
	FlowFinder test("input.txt");
	ASSERT_EQ(test.findFlow(), 5);
}

TEST(FlowFinder, findPath) {
	FlowFinder test("input.txt");
	ASSERT_STREQ(test.findPath().c_str(), "SOQT");
}

TEST(FlowFinder, pushNode) {
	string str = "qwertyuiop";
	FlowFinder test("");

	for (size_t i = 0; i < str.size(); i++) {
		test.pushNode(str[i]);
	}

	Node* lst = test.head;

	for (size_t i = 0; i < str.size(); i++) {
		ASSERT_EQ(lst->name, str[i]);
		lst = lst->next;
	}
}

TEST(FlowFinder, pushAdjacency) {
	string str = "qwertyuiop";
	FlowFinder test("");

	for (size_t i = 0; i < str.size()-1; i++) {
		test.pushAdjacency(str[i], str[i+1], i+1);
	}

	Node* lst = test.head;

	for (size_t i = 0; i < str.size()-1; i++) {
		ASSERT_EQ(lst->adjacencyHead->flow, i+1);
		ASSERT_EQ(lst->adjacencyHead->name, str[i+1]);
		ASSERT_EQ(lst->name, str[i]);
		lst = lst->next;
	}
}

TEST(FlowFinder, getNode) {
	string str = "qwertyuiop";
	FlowFinder test("");

	for (size_t i = 0; i < str.size(); i++) {
		test.pushNode(str[i]);
	}

	for (size_t i = 0; i < str.size(); i++) {
		ASSERT_EQ(test.getNode(str[i])->name, str[i]);
	}
}

TEST(FlowFinder, getAdjacency) {
	string str = "qwertyuiop";
	FlowFinder test("");

	for (size_t i = 0; i < str.size() - 1; i++) {
		test.pushAdjacency(str[i], str[i + 1], i + 1);
	}

	for (size_t i = 0; i < str.size() - 1; i++) {
		ASSERT_EQ(test.getAdjacency(str[i], str[i+1])->name, str[i+1]);
	}
}

TEST(FlowFinder, flow) {
	FlowFinder test("input.txt");
	test.findFlow();

	ASSERT_EQ(test.flow(), 5);
}


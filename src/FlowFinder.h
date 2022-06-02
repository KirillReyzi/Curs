#pragma once
#include <fstream>
#include <iostream>
#include "Structs.h"

class FlowFinder {
public:
	FlowFinder(string path);

	int findFlow();
	string findPath();
	void output();
	Node* pushNode(char c);
	AdjacencyList* pushAdjacency(char a, char b, int flow);
	Node* getNode(char c);
	AdjacencyList* getAdjacency(char a, char b);
	int flow();

	Node* head;
	Node* tail;
	FlowFinder* start;
	int min;

private:
	void reset();
	FlowFinder() : queueTail(nullptr), tail(nullptr), queueHead(nullptr), head(nullptr), min(999999), start(nullptr) {};
	void input(string path);
	void push(Node* node, string way);
	PriorityQueue* pop();
	PriorityQueue* queueHead;
	PriorityQueue* queueTail;
};

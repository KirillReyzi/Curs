#pragma once
#include <string>

using namespace std;

class AdjacencyList;

class Node {
public:
	Node(char c) : name(c), visited(false), next(nullptr), adjacencyHead(nullptr), adjacencyTail(nullptr) {};
	char name;
	bool visited;
	AdjacencyList* adjacencyHead;
	AdjacencyList* adjacencyTail;
	Node* next;
};

class AdjacencyList {
public:
	AdjacencyList(char c) : name(c), flow(0), node(nullptr), next(nullptr) {};
	char name;
	int flow;
	Node* node;
	AdjacencyList* next;
};

class PriorityQueue {
public:
	PriorityQueue() : node(nullptr), next(nullptr) {};
	Node* node;
	string way;
	PriorityQueue* next;
};
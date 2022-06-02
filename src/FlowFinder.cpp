#include "FlowFinder.h"

FlowFinder::FlowFinder(string path) : queueTail(nullptr), tail(nullptr), queueHead(nullptr), head(nullptr), min(999999), start(new FlowFinder())
{
	ifstream file(path);
	if (!file.is_open())
	{
		return;
	}

	string str;
	char a, b;

	int flow;

	while (file >> a >> b >> flow)
	{
		pushAdjacency(a, b, flow);
	}

	file.close();

	start->input(path);
}

void FlowFinder::input(string path)
{
	ifstream file(path);
	string str;

	char a, b;
	int flow;

	while (file >> a >> b >> flow)
	{
		pushAdjacency(a, b, flow);
	}

	file.close();
}

int FlowFinder::findFlow()
{
	string way = findPath();

	while (!way.empty())
	{
		for (size_t i = 0; i < way.size() - 1; i++)
		{
			getAdjacency(way[i], way[i + 1])->flow -= min;
			AdjacencyList* buff = getAdjacency(way[i + 1], way[i]);
			if (buff)
				buff->flow += min;
		}

		way = findPath();
	}

	return flow();
}

Node* FlowFinder::pushNode(char c)
{
	Node* buff = getNode(c);
	if (buff)
		return buff;

	if (head == nullptr)
	{
		head = new Node(c);
		tail = head;
		return head;
	}

	tail->next = new Node(c);
	tail = tail->next;
	return tail;
}

Node* FlowFinder::getNode(char c)
{
	Node* buff = head;
	while (buff)
	{
		if (buff->name == c)
			return buff;
		buff = buff->next;
	}
	return nullptr;
}

AdjacencyList* FlowFinder::getAdjacency(char a, char b)
{
	AdjacencyList* buff = getNode(a)->adjacencyHead;
	while (buff)
	{
		if (buff->name == b)
			return buff;
		buff = buff->next;
	}
	return nullptr;
}

AdjacencyList* FlowFinder::pushAdjacency(char a, char b, int flow)
{
	Node* node_a = pushNode(a);
	Node* node_b = pushNode(b);

	if (node_a->adjacencyHead == nullptr)
	{
		node_a->adjacencyHead = new AdjacencyList(b);
		node_a->adjacencyHead->node = node_b;
		node_a->adjacencyHead->flow = flow;
		node_a->adjacencyTail = node_a->adjacencyHead;
		return node_a->adjacencyHead;
	}

	node_a->adjacencyTail->next = new AdjacencyList(b);
	node_a->adjacencyTail->next->flow = flow;
	node_a->adjacencyTail->next->node = node_b;
	node_a->adjacencyTail = node_a->adjacencyTail->next;
	return node_a->adjacencyTail;
}

string FlowFinder::findPath()
{
	reset();
	push(getNode('S'), "S");

	PriorityQueue* curent = pop();
	curent->node->visited = true;
	while (curent) {
		if (curent->node->name == 'T') {
			min = getAdjacency(curent->way[0], curent->way[1])->flow;
			for (size_t i = 0; i < curent->way.size() - 1; i++) {
				int a = getAdjacency(curent->way[i], curent->way[i + 1])->flow;
				if (a < min)
					min = a;
			}
			return curent->way;
		}
		AdjacencyList* lst = curent->node->adjacencyHead;
		while (lst)
		{
			if ((lst->node->visited == false) && (lst->flow > 0)) {
				push(lst->node, curent->way + lst->name);
				lst->node->visited = true;
			}
			lst = lst->next;
		}

		curent = pop();
	}
	return "";
}

void FlowFinder::push(Node* node, string path)
{
	if (queueHead == nullptr) {
		queueHead = new PriorityQueue();
		queueHead->node = node;
		queueHead->way = path;
		queueTail = queueHead;
		return;
	}

	queueTail->next = new PriorityQueue();
	queueTail->next->node = node;
	queueTail->next->way = path;
	queueTail = queueTail->next;
}

PriorityQueue* FlowFinder::pop()
{
	if (queueHead == nullptr)
		return nullptr;
	PriorityQueue* buff = queueHead;

	if (queueHead->next)
		queueHead = queueHead->next;
	else
		queueHead = nullptr;

	return buff;
}

void FlowFinder::output()
{
	Node* iter_h = head;
	Node* iter_s = start->head;
	while (iter_h)
	{
		AdjacencyList* lst_h = iter_h->adjacencyHead;
		AdjacencyList* lst_s = iter_s->adjacencyHead;
		while (lst_h)
		{
			cout << iter_h->name << " -> " << lst_h->name <<
				" Start: " << lst_s->flow <<
				" Max flow: " << lst_s->flow - lst_h->flow << endl;
			lst_h = lst_h->next;
			lst_s = lst_s->next;
		}
		iter_h = iter_h->next;
		iter_s = iter_s->next;
	}
}

void FlowFinder::reset()
{
	min = 999999;
	Node* node = head;
	while (node)
	{
		node->visited = false;
		AdjacencyList* lst = node->adjacencyHead;
		while (lst)
		{
			lst = lst->next;
		}
		node = node->next;
	}

	delete queueHead;
	queueHead = nullptr;
}

int FlowFinder::flow()
{
	AdjacencyList* a = start->getNode('S')->adjacencyHead;
	AdjacencyList* b = getNode('S')->adjacencyHead;

	int flow = 0;

	while (a)
	{
		flow += a->flow - b->flow;
		a = a->next;
		b = b->next;
	}
	return flow;
}
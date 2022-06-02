#include <iostream>
#include "FlowFinder.h"

using namespace std;

int main() {
	FlowFinder test("input.txt");
	cout << "Max flow:" << test.findFlow() << endl;
	test.output();
}
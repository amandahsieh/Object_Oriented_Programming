#pragma once
#include <iostream>
#include <queue>
using namespace std;


struct QNode
{
	int val;
	QNode* next;
	QNode() : val(0), next(NULL) {};
	QNode(int x) : val(x), next(NULL) {};
};

class Queue {
public:
	Queue();
	void enqueue(int val);
	void dequeue();
	void print();
private:
	QNode* Head;
};

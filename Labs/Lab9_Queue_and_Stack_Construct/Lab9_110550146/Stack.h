#pragma once
#include <iostream>
#include <stack>
using namespace std;
struct SNode
{
	int val;
	SNode* next;
	SNode() : val(0), next(NULL) {};
	SNode(int x) : val(x), next(NULL) {};
};

class Stack {
public:
	Stack() {};
	void push(int val);
	void pop();
	void print();
private:
	SNode* Head;
};
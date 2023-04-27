#include "Stack.h"
#include <iostream>
#include <vector>
#include <stack>;
using namespace std;

void Stack::push(int val) {
	if (this->Head == NULL) {
		this->Head = new SNode;
		this->Head->val = val;
		return;
	}
	else {
		SNode* tmp = this->Head;
		while (tmp->next!=NULL) {
			tmp = tmp->next;
		}
		tmp->next = new SNode(val);
	}
}

void Stack::pop() {
	if (this->Head == NULL)
		return;
	else if (this->Head->next == NULL) {
		this->Head = NULL;
		return;
	}

	SNode* tmp = this->Head;
	while (tmp->next->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = NULL;
}

void Stack::print() {
	SNode* tmp = this->Head;
	while (tmp != NULL) {
		cout << tmp->val << " ";
		tmp = tmp->next;
	}
	cout << endl;
}
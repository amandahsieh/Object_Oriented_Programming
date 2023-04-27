#include "Queue.h"
#include <iostream>
#include <queue>
using namespace std;
Queue::Queue() {

}

void Queue::dequeue() {
	if (this->Head == NULL)
		return;
	this->Head = this->Head->next;
	/*QNode* tmp = this->Head;
	while (tmp != NULL) {
		if (tmp->next == NULL) {
			tmp = NULL;
			break;
		}
		tmp = tmp->next;
	}*/
}

void Queue::enqueue(int val) {
	if (this->Head == NULL) {
		this->Head = new QNode;
		this->Head->val = val;
	}
	else {
		QNode* tmp = this->Head;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = new QNode(val);
		tmp = tmp->next;
	}
}

void Queue::print() {
	QNode* tmp = this->Head;
	vector <int> keep;
	while (tmp != NULL) {
		keep.push_back(tmp->val);
		tmp = tmp->next;
	}
	for (int i = 0; i < keep.size(); i++) {
		cout << keep[keep.size()-i-1] << " ";
	}
	cout << endl;
}
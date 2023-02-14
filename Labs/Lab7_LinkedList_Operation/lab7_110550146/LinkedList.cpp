#include "LinkedList.h"
#include <vector>

LinkedList::LinkedList() {
	// Constructor
	Head = NULL;
}

void LinkedList::Push_back(int x) {
	// TODO : Insert a node to the end of the linked list, the node¡¦s value is x.
	if (this->Head == NULL) {
		this->Head = new ListNode;
		this->Head->val = x;
	}
	else {
		ListNode* tmp = this->Head;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}	
		tmp->next = new ListNode(x);
		tmp = tmp->next;
	}
	
}

void LinkedList::Push_front(int x) {
	if (!Head) {
		Head = new ListNode(x);
		return;
	}
	ListNode* temp = new ListNode(x);

	temp->next = Head;
	Head = temp;
}

void LinkedList::Insert(int index, int x) {
	// TODO : Insert a node to the linked list at position ¡§index¡¨, the node's
	// value is x. The index of the first node in the linked list is 0.
	ListNode* temp = this->Head;
	ListNode* b = new ListNode;
	ListNode* s = new ListNode(x);
	if (index == 0) {
		s->next = this->Head;
		this->Head = s;
		return;
	}
	for (int i = 0; i < index-1; i++) {
		temp = temp->next;
	}
	b = temp->next;
	if (b!=NULL) {
		temp->next = s;
		s->next = b;
	}
	else {
		temp->next = new ListNode;
		temp->next = s;
		s->next = b;
	}
	return;
}

void LinkedList::Delete(int index) {
	// TODO : Remove the node with index ¡§index¡¨ in the linked list.
	ListNode* a = this->Head;
	ListNode* b = a;
	if (index == 0) {
		this->Head = this->Head->next;
		return;
	}
	for (int i = 0; i < index - 1; i++)	a = a->next;
	b = a->next->next;
	a->next = b;
	return;
}

void LinkedList::Reverse() {
	// TODO : Reverse the linked list.
	// Example :
	//
	// Original List : 1 -> 2 -> 3 -> 4 -> NULL
	// Updated List  : 4 -> 3 -> 2 -> 1 -> NULL
	ListNode* acquire = this->Head;
	ListNode* temp = this->Head;
	vector <int> num;
	while (acquire != NULL) {
		num.push_back(acquire->val);
		acquire = acquire->next;
	}
	for (int i = 0; i < num.size(); i++) {
		temp->val = num[num.size() - i - 1];
		temp = temp->next;
	}
}

void LinkedList::Swap(int index_1, int index_2) {
	if (index_1 == index_2) return;
	ListNode* a = this->Head;
	ListNode* b = this->Head;
	for (int i = 0; i < index_1; i++) a = a->next;
	for (int i = 0; i < index_2; i++) b = b->next;
	int tmp = a->val;
	a->val = b->val;
	b->val = tmp;
	// TODO : Swap two nodes in the linked list
	// Example : 
	// index_1 : 1   ,  index_2 : 3
	// 
	// Original List : 1 -> 2 -> 3 -> 4 -> NULL
	// Updated List  : 1 -> 4 -> 3 -> 2 -> NULL
}

void LinkedList::Print() {
	cout << "List: ";
	// TODO : Print all the elements in the linked list in order.
	while (this->Head!=NULL) {
		cout << this->Head->val<<"  ";
		this->Head = this->Head->next;
	}
	cout << endl;
}

LinkedList::~LinkedList()
{
	while (Head) {
		ListNode* temp = Head;
		Head = Head->next;
		delete temp;
	}
}

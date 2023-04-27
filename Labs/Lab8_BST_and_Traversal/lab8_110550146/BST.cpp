#include "BST.h"
#include<iostream>
#include<queue>
using namespace std;

void BST::insert(Node* insertNode) {
	//TODO: insert a node to BST
	Node* tmp = this->root;
	if (this->root == NULL) {
		this->root = new Node (* insertNode);
	}
	else {
		bool notyet = 1;
		while (notyet) {
			if (insertNode->getValue() < tmp->getValue()) {
				if (tmp->getLchild()== NULL) {
					tmp->setLchild(insertNode);
					notyet = 0;
				}
				tmp = tmp->getLchild();
			}
			else if (insertNode->getValue() > tmp->getValue()) {
				if (tmp->getRchild() == NULL) {
					tmp->setRchild(insertNode);
					notyet = 0;
				}
				tmp = tmp->getRchild();
			}
		}
	}
}

void BST::InOrder_traversal(Node* root)
{
	//TODO: Inorder traversal
	if (root != NULL) {
		InOrder_traversal(root->getLchild());
		cout << (root->getValue())<<"  ";
		InOrder_traversal(root->getRchild());
	}
}

void BST::LevelOrder_traversal(Node* root)
{
	//TODO: Level order traversal
	queue<Node* > q;
	q.push(root);
	while (!q.empty()) {
		Node* tmp = q.front();
		cout << q.front()->getValue() <<"  ";
		q.pop();
		if (tmp->getLchild() != NULL) {
			q.push(tmp->getLchild());
		}
		if (tmp->getRchild() != NULL) {
			q.push(tmp->getRchild());
		}
	}
	cout << endl;
}


Node* BST::getRoot() {
	//TODO: return root of BST
	return this->root;
}
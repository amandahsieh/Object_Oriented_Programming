#include "Node.h"
int Node::getValue() {
	// TODO: return the value of node
	return this->value;
}

Node* Node::getLchild() {
	// TODO: return the left child of this node
	return this->lchild;
}
Node* Node::getRchild() {
	// TODO: return the right child of this node
	return this->rchild;
}

void Node::setLchild(Node* node) {
	// TODO: set the left child of this node
	this->lchild = node;
}
void Node::setRchild(Node* node) {
	// TODO: set the right child of this node
	this->rchild = node;
}
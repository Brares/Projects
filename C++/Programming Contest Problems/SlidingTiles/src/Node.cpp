#include "Node.h"

Node::Node() {
}

Node::~Node() {
}

// Function to create a new binary tree node having given key
Node* Node::newNode(int key)
{
	Node* node = new Node;
	node->data = key;
	node->left = node->right = nullptr;

	return node;
}

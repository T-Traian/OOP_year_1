#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <exception>

using namespace std;

//Worst Case: Theta(1)
//Best Case: Theta(1)
//Average Case: Theta(1)
//Total Complexity: Theta(1)
SortedSet::SortedSet(Relation r) {
	this->r = r;
	root = nullptr;
	nodesNumber = 0;
}

// Worst Case: Theta(n)
// Best Case: Theta(1)
// Average Case: O(n)
// Total Complexity: O(n)
bool SortedSet::add(TComp elem) {
	Node* newNode = new Node{ elem, nullptr, nullptr, nullptr }; 
	Node* current = root;
	Node* prev = nullptr;

	if (current == nullptr) {
		root = newNode;
		nodesNumber++;
		return true;
	}

	while (current != nullptr) {
		if (current->info == elem) {
			delete newNode;
			return false;
		}
		prev = current;

		if (r(elem, current->info)) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	newNode->parent = prev;

	if (r(elem, prev->info)) {
		prev->left = newNode;
	}
	else {
		prev->right = newNode;
	}
	nodesNumber++;
	return true;
}

// Worst Case: Theta(n)
// Best Case: Theta(1)
// Average Case: O(n)
// Total Complexity: O(n)
bool SortedSet::remove(TComp elem) {
	Node* current = root;
	Node* prev = nullptr;

	while (current != nullptr and current->info != elem) {
		prev = current;
		if (r(elem, current->info)) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	if (current == nullptr) {
		return false;
	}


	if (current->left == nullptr && current->right == nullptr) {
		if (prev == nullptr) {
			root = nullptr;
		}
		else if (prev->left == current) {
			prev->left = nullptr;
		}
		else {
			prev->right = nullptr;
		}
	}
	else if (current->left == nullptr) {
		if (prev == nullptr) {
			root = current->right;
			root->parent = nullptr;
		}
		else if (prev->left == current) {
			prev->left = current->right;
			current->right->parent = prev; 
		}
		else {
			prev->right = current->right;
			current->right->parent = prev;
		}
	}
	else if (current->right == nullptr) {
		if (prev == nullptr) {
			this->root = current->left;
			root->parent = nullptr;
		}
		else if (prev->left == current) {
			prev->left = current->left;
			current->left->parent = prev;
		}
		else {
			prev->right = current->left;
			current->left->parent = prev;
		}
	}
	else {
		Node* successor = current->right;
		while (successor->left != nullptr) {
			successor = successor->left;
		}

		current->info = successor->info;

		current = successor; 

		if (successor->parent->left == successor) {
			successor->parent->left = successor->right;
		}
		else {
			successor->parent->right = successor->right;
		}
		if (successor->right != nullptr) {
			successor->right->parent = successor->parent;
		}
	}

	delete current;
	nodesNumber--;
	return true;
}

//Worst Case: Theta(n)
//Best Case: Theta(1)
//Average Case: O(n)
//Total Complexity: O(n)
bool SortedSet::search(TComp elem) const {
	Node* current = root;

	while (current != nullptr) {
		if (current->info == elem) {
			return true;
		}
		if (r(elem, current->info)) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	return false;
}

// Worst Case: Theta(1)
// Best Case: Theta(1)
// Average Case: Theta(1)
// Total Complexity: Theta(1)
int SortedSet::size() const {
	return nodesNumber;
}


// Worst Case: Theta(1)
// Best Case: Theta(1)
// Average Case: Theta(1)
// Total Complexity: Theta(1)
bool SortedSet::isEmpty() const {
	return nodesNumber == 0;
}

// Worst Case: Theta(1)
// Best Case: Theta(1)
// Average Case: Theta(1)
// Total Complexity: Theta(1)
SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}

// Worst Case: Theta(1)
// Best Case: Theta(1)
// Average Case: Theta(1)
// Total Complexity: Theta(1)
SortedSet::~SortedSet() {
	if (root == nullptr) {
		return;
	}

	Node* current = root;
	Node* lastVisited = nullptr;

	while (current != nullptr) {
		if (current->left != nullptr && lastVisited != current->left) {
			current = current->left;
		}
		else if (current->right != nullptr && lastVisited != current->right) {
			current = current->right;
		}
		else {
			Node* parent = current->parent;
			if (parent != nullptr) {
				if (parent->left == current) {
					parent->left = nullptr;
				}
				else {
					parent->right = nullptr;
				}
			}
			else {
				root = nullptr;
			}
			lastVisited = current;
			delete current;
			current = parent;
		}
	}
	nodesNumber = 0;
}


// Worst Case: Theta(n)
// Best Case: Theta(1)
// Average Case: O(n)
// Total Complexity: O(n)
bool SortedSet::isSubsetOf(SortedSet& s) const {
	SortedSetIterator it = this->iterator();
	while (it.valid()) {
		if (!s.search(it.getCurrent())) {
			return false;
		}
		it.next();
	}
	return true;
}
#include "SortedSetIterator.h"
#include <exception>

using namespace std;


//Worst Case: Theta(n)
//Best Case: Theta(n)
//Average Case: Theta(n)
//Total Complexity: Theta(n)
SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
    current = multime.root;
    if (current != nullptr) {
        while (current->left != nullptr) {
            current = current->left;
        }
    }
}

//Worst Case: Theta(n)
//Best Case: Theta(n)
//Average Case: Theta(n)
//Total Complexity: Theta(n)
void SortedSetIterator::first() {
    current = multime.root;
    if (current != nullptr) {
        while (current->left != nullptr) {
            current = current->left;
        }
    }
}

//Worst Case: Theta(n)
//Best Case: Theta(1)
//Average Case: O(n)
//Total Complexity: O(n)
void SortedSetIterator::next() {
    if (current == nullptr) {
        throw exception("No next element"); 
    }

    if (current->right != nullptr) {
        current = current->right;
        while (current->left != nullptr) {
            current = current->left;
        }
    }
    else {
        SortedSet::Node* tempParent = current->parent;
        while (tempParent != nullptr && tempParent->right == current) {
            current = tempParent;
            tempParent = tempParent->parent;
        }
        current = tempParent;
    }
}

//Worst Case: Theta(1)
//Best Case: Theta(1)
//Average Case: Theta(1)
//Total Complexity: Theta(1)
TElem SortedSetIterator::getCurrent()
{
    if (current != nullptr) {
        return current->info;
    }
    else {
        throw exception("Invalid iterator");
    }
}

//Worst Case: Theta(1)
// Best Case: Theta(1)
// Average Case: Theta(1)
// Total Complexity: Theta(1)
bool SortedSetIterator::valid() const {
    if (current != nullptr) {
        return true;
    }
    else {
        return false;
    }
}

#include "SetIterator.h"
#include "Set.h"

//Best case: Theta(1)
//Worst case: Theta(m)
//Average case: O(m)
//Total complexity: O(m)
SetIterator::SetIterator(const Set& m) : set(m)
{
	current = 0;
	while (current < set.m && set.TKey[current] == NULL_TELEM) {
		current++;
	}
}

//Best case: Theta(1)
//Worst case: Theta(m)
//Average case: O(m)
//Total complexity: O(m)
void SetIterator::first() {
	current = 0;
	while (current < set.m && set.TKey[current] == NULL_TELEM) {
		current++;
	}
}

//Best case: Theta(1)
//Worst case: Theta(m)
//Average case: O(m)
//Total complexity: O(m)
void SetIterator::next() {
	if (current >= set.m || set.TKey[current] == NULL_TELEM) {
		throw std::exception();
	}
	current++;
	while (current < set.m && set.TKey[current] == NULL_TELEM) {
		current++;
	}
}

//Best case: Theta(1)
//Worst case: Theta(1)
//Average case: Theta(1)
//Total complexity: Theta(1)
TElem SetIterator::getCurrent()
{
	if (current < set.m) {
		if (set.TKey[current] != NULL_TELEM) {
			return set.TKey[current];
		}
	}
	else
		throw std::exception();
}

//Best case: Theta(1)
//Worst case: Theta(1)
//Average case: Theta(1)
//Total complexity: Theta(1)
bool SetIterator::valid() const {
	return current < set.m && set.TKey[current] != NULL_TELEM;
}




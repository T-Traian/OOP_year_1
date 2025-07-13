#include "Set.h"
#include "SetITerator.h"


//Best case: Theta(1)
//Worst case: Theta(1)
//Average case: Theta(1)
//Total complexity: Theta(1)
Set::Set() {
	m = 2;
	TKey = new TElem[m];
	next = new TElem[m];
	firstEmpty = 0;
	for (int i = 0; i < m; i++) {
		TKey[i] = NULL_TELEM;
		next[i] = -1;
	}
}

//Best case: Theta(1)
//Worst case: Theta(m)
//Average case: O(m)
//Total complexity: O(m)
bool Set::add(TElem elem) {
	int pos = hashFunction(elem);
	int current = pos;

	while (current != -1) {
		if (TKey[current] == elem) {
			return false;
		}
		current = next[current];
	}

	if (firstEmpty >= m) {
		int oldM = m;
		m *= 2;

		TElem* newTKey = new TElem[m];
		TElem* newNext = new TElem[m];

		for (int i = 0; i < m; i++) {
			newTKey[i] = NULL_TELEM;
			newNext[i] = -1;
		}

		firstEmpty = 0;
		for (int i = 0; i < oldM; i++) {
			if (TKey[i] != NULL_TELEM) {
				TElem e = TKey[i];
				int newPos = hashFunction(e);

				if (newTKey[newPos] == NULL_TELEM) {
					newTKey[newPos] = e;
					newNext[newPos] = -1;

					if (newPos == firstEmpty) {
						firstEmpty++;
						while (firstEmpty < m && newTKey[firstEmpty] != NULL_TELEM) {
							firstEmpty++;
						}
					}
				}
				else {
					int current = newPos;
					while (newNext[current] != -1) {
						current = newNext[current];
					}

					newTKey[firstEmpty] = e;
					newNext[current] = firstEmpty;
					newNext[firstEmpty] = -1;

					firstEmpty++;
					while (firstEmpty < m && newTKey[firstEmpty] != NULL_TELEM) {
						firstEmpty++;
					}
				}
			}
		}

		delete[] TKey;
		delete[] next;
		TKey = newTKey;
		next = newNext;
	}


	pos = hashFunction(elem);

	if (TKey[pos] == NULL_TELEM) {
		TKey[pos] = elem;
		next[pos] = -1;
		if (pos == firstEmpty) {
			firstEmpty++;
			while (firstEmpty < m && TKey[firstEmpty] != NULL_TELEM) {
				firstEmpty++;
			}
		}
	}
	else {
		current = pos;
		while (next[current] != -1) {
			current = next[current];
		}
		TKey[firstEmpty] = elem;
		next[current] = firstEmpty;
		next[firstEmpty] = -1;

		firstEmpty++;
		while (firstEmpty < m && TKey[firstEmpty] != NULL_TELEM) {
			firstEmpty++;
		}
	}
	return true;
}

//Best case: Theta(1)
//Worst case: Theta(m)
//Average case: O(m)
//Total complexity: O(m)
bool Set::remove(TElem elem) {
	int pos = hashFunction(elem);
	int prev = -1;
	int current = pos;

	while (current != -1 && TKey[current] != elem) {
		prev = current;
		current = next[current];
	}

	if (current == -1) {
		return false;
	}

	if (prev == -1) {
		if (next[current] != -1) {
			int next_elem = next[current];
			TKey[current] = TKey[next_elem];
			next[current] = next[next_elem];
			TKey[next_elem] = NULL_TELEM;
			next[next_elem] = -1;

			if (next_elem < firstEmpty) {
				firstEmpty = next_elem;
			}
		}
		else {
			TKey[current] = NULL_TELEM;
			next[current] = -1;
			if (current < firstEmpty) {
				firstEmpty = current;
			}
		}
	}
	else {
		next[prev] = next[current];
		TKey[current] = NULL_TELEM;
		next[current] = -1;
		if (current < firstEmpty) {
			firstEmpty = current;
		}
	}

	return true;
}


//Best case: Theta(1)
//Worst case: Theta(m)
//Average case: O(m)
//Total complexity: O(m)
bool Set::search(TElem elem) const {
	int current = hashFunction(elem);

	while (current != -1 and TKey[current] != elem) {
		current = next[current];
	}

	if (current == -1) {
		return false;
	}
	else {
		return true;
	}
}

//Best case: Theta(m)
//Worst case: Theta(m)
//Average case: Theta(m)
//Total complexity: Theta(m)
int Set::size() const {
	int count = 0;
	for (int i =0 ;i<m;i++)
		if (TKey[i] != NULL_TELEM) {
			count++;
		}
	return count;
}

//Best case: Theta(1)
//Worst case: Theta(m)
//Average case: O(m)
//Total complexity: O(m)
bool Set::isEmpty() const {
	for (int i = 0; i < m; i++) {
		if (TKey[i] != NULL_TELEM) {
			return false;
		}
	}
	return true;
}

//Best case: Theta(1)
//Worst case: Theta(1)
//Average case: Theta(1)
//Total complexity: Theta(1)
Set::~Set() {
	delete[] TKey;
	delete[] next;
}


SetIterator Set::iterator() const {
	return SetIterator(*this);
}

//Best case: Theta(m)
//Worst case: Theta(m)
//Average case: Theta(m)
//Total complexity: Theta(m)
void Set::Union(const Set& s) {
	SetIterator it = s.iterator();
	while (it.valid()) {
		add(it.getCurrent());
		it.next();
	}
}
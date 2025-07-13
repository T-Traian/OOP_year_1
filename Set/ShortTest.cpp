#include "ShortTest.h"
#include <assert.h>
#include "Set.h"
#include "SetIterator.h"

void testAll() { 
	Set s;
	assert(s.isEmpty() == true);
	assert(s.size() == 0); 
	assert(s.add(5)==true);
	assert(s.add(1)==true);
	assert(s.add(10)==true);
	assert(s.add(7)==true);
	assert(s.add(1)==false);
	assert(s.add(10)==false);
	assert(s.add(-3)==true);
	assert(s.size() == 5);
	assert(s.search(10) == true);
	assert(s.search(16) == false);
	assert(s.remove(1) == true);
	assert(s.remove(6) == false);
	assert(s.size() == 4);


	SetIterator it = s.iterator();
	it.first();
	int sum = 0;
	while (it.valid()) {
		TElem e = it.getCurrent();
		sum += e;
		it.next();
	}
	assert(sum == 19);

}

void testUnion() {
	std::cout << "Test union" << std::endl;
	Set s1;
	Set s2;
	for (int i = 0; i < 3; i++) {
		s1.add(i);
	}
	//0 1 2
	for (int i = 2; i < 5; i++) {
		s2.add(i * 2);
	}
	//4 6 8
	s1.Union(s2);
	assert(s1.size() == 6);
	SetIterator it = s1.iterator();
	it.first();
	int sum = 0;
	while (it.valid()) {
		TElem e = it.getCurrent();
		sum += e;
		it.next();
	}
	assert(sum == 21);
}


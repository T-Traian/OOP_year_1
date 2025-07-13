#include "LotteryTicket.h"
#include <exception>
#include <cstdlib>

unsigned short LotteryTicket::nr[6] = { 0 };
Date LotteryTicket::extraction;

LotteryTicket::~LotteryTicket() {
	delete[] numbers;
}

LotteryTicket::LotteryTicket(const LotteryTicket& L) {
	numbers = new unsigned short[L.capacity];
	d = L.d;
	extraction.setYear(d.getYear());
	extraction.setMonth(d.getMonth());
	extraction.setDay(d.getDay());
	capacity = L.capacity;
	current_size = L.current_size;
	for (int i = 0; i < current_size; i++) {
		numbers[i] = L.numbers[i];
		nr[i] = L.numbers[i];
	}
}

LotteryTicket& LotteryTicket::operator =(const LotteryTicket& L) {
	if (this != &L){
		capacity = L.capacity;
		current_size = L.current_size;
		d = L.d;
		delete[] numbers;
		numbers = new unsigned short[capacity];
		for (int i = 0; i < current_size; i++)
			numbers[i] = L.numbers[i];
		return *this;
	}
	else {
		throw exception();
	}
}

LotteryTicket::LotteryTicket() {
	d.setYear(2024);
	d.setMonth(3);
	d.setDay(25);
	extraction.setYear(2024);
	extraction.setMonth(3);
	extraction.setDay(25);
	int random_number;
	numbers = new unsigned short[10];
	capacity = 10;
	current_size = 0;
	while (current_size < 6) {
		random_number = 1 + rand() % (49 - 1 + 1);
		numbers[current_size] = random_number;
		nr[current_size] = random_number;
		current_size++;
	}
}

LotteryTicket::LotteryTicket(unsigned short ar[], Date d){
	this->d = d;
	numbers = new unsigned short[6];
	for (int i = 0; i < 6; i++)
		this->numbers[i] = ar[i];
	this->capacity = 6;
	this->current_size = 6;
	extraction.setYear(d.getYear());
	extraction.setMonth(d.getMonth());
	extraction.setDay(d.getDay());
}

void LotteryTicket::setNr(unsigned short arr[6]) {
	int ok = 1;
	for (int i = 0; i<6; i++)
		for (int j = 0; j<6; j++)
			if (arr[i] == arr[j] and arr[i]!=0) {
				ok = 0;
				i = j = 100;
			}
	if (ok == 1)
		for (int i = 0; i < 6; i++)
			nr[i] = arr[i];
}

void LotteryTicket::setNr0() {
	for (int i = 0; i < 6; i++)
		nr[i] = 0;
}

int LotteryTicket::match() {
	int count = 0, sum = 0;
	for (int i = 0; i < current_size; i++) {
		if (numbers[i] == nr[i])
			count++;
		sum += numbers[i];
	}
	if (sum == 0)
		return -1;
	else
		return count;
}

unsigned short* LotteryTicket::getNumbers() {
	return numbers;
}
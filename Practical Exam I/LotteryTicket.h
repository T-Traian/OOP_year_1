#pragma once
#include "Date.h"

class LotteryTicket {
private:
	unsigned short* numbers;
	Date d;
	int capacity;
	int current_size;
	static unsigned short nr[6];
	static Date extraction;

public:
	LotteryTicket();
	LotteryTicket(unsigned short ar[], Date d);

	LotteryTicket& operator = (const LotteryTicket& L);
	LotteryTicket(const LotteryTicket& L);
	~LotteryTicket();

	unsigned short* getNumbers();

	int match();

	static void setNr(unsigned short arr[6]);
	static void setNr0();
};
#include "LotteryTicket.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main() {
	Date d;
	unsigned short ar[] = { 7, 11, 28, 33, 44 ,43 };
	LotteryTicket t1(ar,d);
	LotteryTicket* t2 = new LotteryTicket;
	LotteryTicket tickets[5];
	unsigned short extracted_numbers[6] = { 7, 11, 28, 33, 44, 49 };
	tickets[0] = t1;
	tickets[1] = *t2;
	t1.setNr(extracted_numbers);
	t2->setNr(extracted_numbers);
	for (int i = 2; i < 5; i++) {
		tickets[i];
		tickets[i].setNr(extracted_numbers);
	}

	unsigned short* num;
	int count, count_4=0, count_5=0, count_6=0;
	for (int i = 0; i < 5; i++) {
		count = 0;

		num = tickets[i].getNumbers();
		for (int j = 0; j < 6; j++)
			for (int k = 0; k < 6; k++)
				if (num[j] == extracted_numbers[k])
					count++;
		if (count == 4)
			count_4++;
		else
			if (count == 5)
				count_5++;
			else
				if (count == 6)
					count_6++;
					
	}

	cout << count_4 << endl;
	cout << count_5 << endl;
	cout << count_6 << endl;
}
#include <cstdio>
#include <iostream>
#include <cstdlib>

using namespace std;

char months[12][20] = {
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December",
};

int days[12] = {
	31,
	28,
	31,
	30,
	31,
	30,
	31,
	31,
	30,
	31,
	30,
	31,
};

bool is_leap_year(int y) {
	if (y % 400 == 0) return true;
	if (y % 100 == 0) return false;
	if (y % 4 == 0) return true;
	return false;
}

int get_rand_day(int y, int m) {
	int to_add = 0;
	if (is_leap_year(y) && m == 1) {
		to_add = 1;
	}
	int d = rand() % days[m] + 1;
	return d;
}

int main (void) {
	int T = 500;
	printf("%d\n", T);
	printf("February 29, 1800000000\n");
	printf("February 29, 1800000000\n");
	T--;
	printf("February 29, 1800000184\n");
	printf("February 29, 1800000184\n");
	T--;
	printf("February 29, 1800000000\n");
	printf("February 29, 1800000004\n");
	T--;
	printf("February 29, 1800000184\n");
	printf("February 29, 1800000188\n");
	T--;
	printf("January 11, 2000\n");
	printf("March 12, 2000\n");
	T--;
	printf("January 11, 2004\n");
	printf("March 12, 2004\n");
	T--;
	printf("January 11, 2100\n");
	printf("March 12, 2100\n");
	T--;
	printf("January 11, 2000\n");
	printf("February 29, 2000\n");
	T--;
	printf("January 11, 2004\n");
	printf("February 29, 2004\n");
	T--;
	printf("February 29, 2000\n");
	printf("August 31, 2000\n");
	T--;
	printf("February 29, 2004\n");
	printf("August 31, 2004\n");
	T--;
	printf("February 28, 2100\n");
	printf("August 31, 2100\n");
	T--;
	printf("April 29, 2000\n");
	printf("August 31, 2000\n");
	T--;
	printf("April 29, 2004\n");
	printf("August 31, 2004\n");
	T--;
	printf("April 29, 2100\n");
	printf("August 31, 2100\n");
	T--;
	printf("January 19, 2100\n");
	printf("February 28, 2100\n");
	T--;
	printf("January 19, 2104\n");
	printf("February 28, 2104\n");
	T--;

	printf("March 1, 2104\n");
	printf("December 11, 2104\n");
	T--;
	printf("March 1, 2104\n");
	printf("December 11, 2105\n");
	T--;
	printf("March 1, 2104\n");
	printf("December 11, 2108\n");
	T--;

	while (T--) {
		int y1 = rand() % 1300 + 2000;
		int y2 = rand() % 10000 + 2000000000 - 10000 + 1;

		int m1 = rand() % 12;
		int m2 = rand() % 12;

		int d1 = get_rand_day(y1, m1);
		int d2 = get_rand_day(y2, m2);
		
		printf("%s %d, %d\n", months[m1], d1, y1);
		printf("%s %d, %d\n", months[m2], d2, y2);
	}
	
	return 0;
}


#include "Algorithms.h"


int calculate_NOD(int num_1, int num_2) {

	int y_1;
	int y_2;
	int r_1;
	int r_2;
	int q;

	y_1 = 0;
	y_2 = 1;
	r_1 = num_1;
	r_2 = num_2;

	while (r_2 != 0) {
		q = r_1 / r_2;

		int y = y_1 - q * y_2;
		int r = r_1 % r_2;

		y_1 = y_2;
		y_2 = y;

		r_1 = r_2;
		r_2 = r;
	}

	return r_1;
}


int calculate_NOK(int num_1, int num_2) {
	return num_1 * num_2 / calculate_NOD(num_1, num_2);
}


int find_reverse_element(int a, int m) {

	int x_1;
	int y_1;
	int x_2;
	int y_2;
	int r_1;
	int r_2;
	int q;

	x_1 = 1;
	x_2 = 0;
	y_1 = 0;
	y_2 = 1;
	r_1 = m;
	r_2 = a % m;

	while (r_2 != 0) {
		q = r_1 / r_2;

		int x = x_1 - q * x_2;
		int y = y_1 - q * y_2;
		int r = r_1 % r_2;

		x_1 = x_2;
		y_1 = y_2;

		x_2 = x;
		y_2 = y;

		r_1 = r_2;
		r_2 = r;
	}

	if (r_1 == 1) {
		if (y_1 > 0) {
			return y_1;
		}
		else {
			y_1 += y_2;
			return y_1;
		}
	}
	else {
		return 0;
	}
}
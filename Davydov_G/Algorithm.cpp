#include <iostream>
#include <vector>

using namespace std;


int calculate_NOD(int num_1, int num_2) {
	while (num_1 != num_2) {
		if (num_1 > num_2) {
			num_1 = num_1 - num_2;
		}
		else {
			num_2 = num_2 - num_1;
		}
	}

	return num_1;
}


int calculate_NOK(int num_1, int num_2) {
	return num_1 * num_2 / calculate_NOD(num_1, num_2);
}


int main()
{
	vector<int> system_b = { 1, 1, 1, 1, 1, 0 };
	vector<int> system_m = { 2, 3, 4, 5, 6, 7 };

	while (system_b.size() != 1) {
		int b_1 = system_b[0];
		int b_2 = system_b[1];
		int m_1 = system_m[0];
		int m_2 = system_m[1];
		int i = 0;

		while (true) {
			if ((b_1 + m_1 * i - b_2) % m_2 == 0) {
				break;
			}

			i++;
		}

		system_b.erase(system_b.begin());
		system_m.erase(system_m.begin());
		system_b[0] = b_1 + m_1 * i;
		system_m[0] = m_1 * m_2 / calculate_NOD(m_1, m_2);
	}

	cout << "x = " << system_b[0] << " mod(" << system_m[0] << ")";
}
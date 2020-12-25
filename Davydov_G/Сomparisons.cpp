#include "Calculator.h"
#include "Comparisons.h"
#include "Algorithms.h"


void Сomparisons::Computer() {
	vector<System> systems;
	int error = 0;

	int Equation_number;

	Notation_Rules();

	cout << "Введите количество сравнений, которое используется в системе\n";

	cin >> Equation_number;

	for (int i = 0; i < Equation_number; i++) {
		string expression;

		if (i == 0) {
			cin.ignore();
		}

		cout << "Введите " << i + 1 << " уравнение\n";

		getline(cin, expression, '\n');

		remove_spaces(expression);

		if (validation(expression)) {
			transform(expression, systems, error);
		}
		else {
			error++;
			cout << "Некорректный ввод\n";
			break;
		}

		if (error == 1) {
			cout << "Система не имеет решений (у коэффициента перед x не обратного элемента)\n";
			break;
		}
	}

	if (compatibility_check(systems) and error == 0) {
		while (systems.size() != 1) {
			int b_1 = systems[0].b;
			int b_2 = systems[1].b;
			int m_1 = systems[0].m;
			int m_2 = systems[1].m;
			int i = 0;

			while (true) {
				if ((b_1 + m_1 * i - b_2) % m_2 == 0) {
					break;
				}

				i++;
			}

			systems.erase(systems.begin());
			systems[0].b = b_1 + m_1 * i;
			systems[0].m = calculate_NOK(m_1, m_2);
		}

		cout << "x = " << systems[0].b << " mod(" << systems[0].m << ")" << endl;
	}
	else if (error == 1) {
		cout << error;
		cout << "Система несовместима\n";
	}
}


void Сomparisons::Notation_Rules() {
	cout << "\t\t::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
	cout << "\t\t:::: Введите выражение :::::::::::::::::::::::::::::::::::::::\n";
	cout << "\t\t:::: Выражение может содержать следующие операции: :::::::::::\n";
	cout << "\t\t:::: + - сложение; :::::::::::::::::::::::::::::::::::::::::::\n";
	cout << "\t\t:::: - - вычетание/унарный минус; ::::::::::::::::::::::::::::\n";
	cout << "\t\t:::: * - умножение; ::::::::::::::::::::::::::::::::::::::::::\n";
	cout << "\t\t:::: () - взятие выражение в скобки; :::::::::::::::::::::::::\n";
	cout << "\t\t:::: (mod(x)) - сравнение по модулю; :::::::::::::::::::::::::\n";
	cout << "\t\t:::: Обозначение переменных: :::::::::::::::::::::::::::::::::\n";
	cout << "\t\t:::: x; ::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
}


void Сomparisons::remove_spaces(string& expression) {

	for (int i = 0; i < expression.size(); i++) {
		if (expression[i] == ' ') {
			expression.erase(i, 1);
			i--;
		}
	}
}


bool Сomparisons::validation(string expression) {
	

	if (expression.size() == 0) {
		return false;
	}

	if (expression[0] != 'x' and expression[0] != '(' and expression[0] != '-' and (int(expression[0]) >= 58 or int(expression[0]) <= 47)) {
		return false;
	}

	int brackets = 0;
	int equally = 0;
	int mod = 0;
	int x = 0;

	while (expression != "") {
		if (int(expression[0]) >= 48 and int(expression[0]) <= 57) {

			expression.erase(0, 1);

			if (mod == 1 and expression[0] != ')' and (int(expression[0]) >= 58 or int(expression[0]) <= 47)) {
				return false;
			}

			if (expression[0] != '+' and expression[0] != '-' and expression[0] != '*' and expression[0] != ')'
				and expression[0] != '=' and (int(expression[0]) >= 58 or int(expression[0]) <= 47) and expression != ""
				and expression[0] != '(' and expression[1] != 'm') {
				return false;
			}
		}

		else if (expression[0] == '+' or expression[0] == '-' or expression[0] == '*') {

			expression.erase(0, 1);

			if ( expression[0] != 'x' and expression[0] != '(' and (int(expression[0]) >= 58 or int(expression[0]) <= 47)) {
				return false;
			}
		}

		else if (expression[0] == '(') {

			brackets++;

			expression.erase(0, 1);

			if (expression[0] != 'x' and expression[0] != '(' and expression[0] != '-' and expression[0] != 'm' and (int(expression[0]) >= 58 or int(expression[0]) <= 47)) {
				return false;
			}
		}

		else if (expression[0] == ')') {
			brackets--;

			expression.erase(0, 1);

			if (brackets < 0) {
				return false;
			}

			if (mod == 1 and expression.size() != 0 and expression[0] != ')') {
				return false;
			}

			if (expression[0] != '+' and expression[0] != '-' and expression[0] != '*' and expression[0] != ')'
				and expression[0] != '=' and expression.size() != 0 and expression[0] != '(' and expression[1] != 'm') {
				return false;
			}
		}

		else if (expression[0] == '=') {

			equally++;

			expression.erase(0, 1);

			if (equally != 1 or brackets != 0) {
				return false;
			}

			if (expression[0] != '(' and expression[0] != '-' and (int(expression[0]) >= 58 or int(expression[0]) <= 47)) {
				return false;
			}
		}

		else if (expression[0] == 'x') {
			x++;

			if (x != 1) {
				return false;
			}

			if (equally == 1) {
				return false;
			}

			expression.erase(0, 1);

			if (expression[0] != '+' and expression[0] != '-' and expression[0] != '*' and expression[0] != ')' and expression[0] != '=') {
				return false;
			}
		}

		else if (expression[0] == 'm' and expression[1] == 'o' and expression[2] == 'd') {

			expression.erase(0, 3);

			mod++;

			if (mod != 1) {
				return false;
			}

			if (expression[0] != '(') {
				return false;
			}
		}

		else {
			return false;
		}
	}

	if (brackets != 0) {
		return false;
	}

	if (mod != 1 or equally != 1 or x != 1) {
		return false;
	}

	return true;
}


void Сomparisons::transform(string expression, vector<System>& systems, int& error) {
	Coefficients coefficients_to_equality;
	Coefficients coefficients_after_equality;

	string to_equality = "";
	string after_equality = "";

	int mod;
	int divider;

	while (expression[0] != '=') {
		to_equality += expression[0];
		expression.erase(0, 1);
	}

	expression.erase(0, 1);

	while (expression != "") {
		after_equality += expression[0];
		expression.erase(0, 1);
	}

	calculate_to_equality(to_equality, coefficients_to_equality);
	calculate_after_equality(after_equality, coefficients_after_equality, mod);

	coefficients_after_equality.b -= coefficients_to_equality.b;

	while (coefficients_after_equality.b < 0) {
		coefficients_after_equality.b += mod;
	}
	coefficients_after_equality.b = coefficients_after_equality.b % mod;

	divider = calculate_NOD(calculate_NOD(coefficients_after_equality.b, coefficients_to_equality.k), mod);

	coefficients_to_equality.k = coefficients_to_equality.k / divider;
	coefficients_after_equality.b = coefficients_after_equality.b / divider;
	mod = mod / divider;

	if (find_reverse_element(coefficients_to_equality.k, mod)) {
		coefficients_after_equality.b = (coefficients_after_equality.b * find_reverse_element(coefficients_to_equality.k, mod)) % mod;
	}
	else {
		error++;
	}

	System system_;
	system_.b = coefficients_after_equality.b;
	system_.m = mod;

	systems.push_back(system_);
}



bool Сomparisons::compatibility_check(vector<System> systems) {
	if (systems.size() > 1) {
		for (int i = 0; i < systems.size() - 1; i++) {
			for (int j = i; j < systems.size(); j++) {
				if ((systems[i].b - systems[j].b) % calculate_NOD(systems[i].m, systems[j].m) != 0) {
					return false;
				}
			}
		}
	}
	return true;
}

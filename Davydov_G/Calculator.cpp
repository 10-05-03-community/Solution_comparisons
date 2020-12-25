#include "Calculator.h"

void balance(multimap<int, operation>& operations, multimap<int, operation>::iterator iter) {
    int order = iter->second.order;
    for (; iter != operations.end(); iter++) {
        if (iter->second.order > order) {
            iter->second.order -= 1;
        }
    }
}


void calculate_to_equality(string& expression, Coefficients& coefficient) {
    multimap<int, operation> operations;
    vector <Coefficients> values;

    int brackets = 0;
    int znak = 1;

    while (expression != "") {

        if (int(expression[0]) >= 48 and int(expression[0]) <= 57) {

            istringstream iss(expression, istringstream::in);
            int num;
            iss >> num;

            stringstream ss;
            ss << num;
            string str = ss.str();

            expression.erase(0, str.length());

            num = znak * num;
            znak = 1;
            Coefficients value;
            value.b = num * znak;
            value.k = 0;
            values.push_back(value);
        }

        else if (expression[0] == '(') {
            brackets -= 100;
            expression.erase(0, 1);
        }

        else if (expression[0] == ')') {
            brackets += 100;
            expression.erase(0, 1);
        }

        else if (expression[0] == '+') {
            operation Plus;
            Plus.operation = '+';
            Plus.order = operations.size();
            operations.insert({ 3 + brackets, Plus });
            expression.erase(0, 1);
        }

        else if (expression[0] == '-') {
            if (operations.size() - values.size() == 0) {
                znak = -1;
                expression.erase(0, 1);
            }
            else {
                operation Minus;
                Minus.operation = '-';
                Minus.order = operations.size();
                operations.insert({ 3 + brackets, Minus });
                expression.erase(0, 1);
            }
        }

        else if (expression[0] == '*') {
            operation Multiplication;
            Multiplication.operation = '*';
            Multiplication.order = operations.size();
            operations.insert({ 2 + brackets, Multiplication });
            expression.erase(0, 1);
        }

        else if (expression[0] == 'x') {
            Coefficients value_x;
            value_x.b = 0;
            value_x.k = znak;
            znak = 1;
            values.push_back(value_x);
            expression.erase(0, 1);
        }
    }


    for (auto iter = operations.begin(); iter != operations.end(); iter++) {
        if (iter->second.operation == '+') {
            values[iter->second.order].b += values[iter->second.order + 1].b;
            values[iter->second.order].k += values[iter->second.order + 1].k;
            values.erase(values.begin() + iter->second.order + 1);
        }
        else if (iter->second.operation == '-') {
            values[iter->second.order].b -= values[iter->second.order + 1].b;
            values[iter->second.order].k -= values[iter->second.order + 1].k;
            values.erase(values.begin() + iter->second.order + 1);
        }
        else if (iter->second.operation == '*') {
            values[iter->second.order + 1].k *= values[iter->second.order].b;
            values[iter->second.order].k *= values[iter->second.order + 1].b;
            values[iter->second.order].k += values[iter->second.order + 1].k;
            values[iter->second.order].b *= values[iter->second.order + 1].b;
            values.erase(values.begin() + iter->second.order + 1);
        }

        balance(operations, iter);
    }

    coefficient.b = values[0].b;
    coefficient.k = values[0].k;
}


void calculate_after_equality(string& expression, Coefficients& coefficient, int& mod) {
    multimap<int, operation> operations;
    vector <int> values;

    int brackets = 0;
    int znak = 1;

    while (expression != "") {

        if (int(expression[0]) >= 48 and int(expression[0]) <= 57) {

            istringstream iss(expression, istringstream::in);
            int num;
            iss >> num;

            stringstream ss;
            ss << num;
            string str = ss.str();

            expression.erase(0, str.length());

            num = znak * num;
            znak = 1;
            values.push_back(num);
        }

        else if (expression[0] == '(') {
            brackets -= 100;
            expression.erase(0, 1);
        }

        else if (expression[0] == ')') {
            brackets += 100;
            expression.erase(0, 1);
        }

        else if (expression[0] == '+') {
            operation Plus;
            Plus.operation = '+';
            Plus.order = operations.size();
            operations.insert({ 3 + brackets, Plus });
            expression.erase(0, 1);
        }

        else if (expression[0] == '-') {
            if (operations.size() - values.size() == 0) {
                znak = -1;
                expression.erase(0, 1);
            }
            else {
                operation Minus;
                Minus.operation = '-';
                Minus.order = operations.size();
                operations.insert({ 3 + brackets, Minus });
                expression.erase(0, 1);
            }
        }

        else if (expression[0] == '*') {
            operation Multiplication;
            Multiplication.operation = '*';
            Multiplication.order = operations.size();
            operations.insert({ 2 + brackets, Multiplication });
            expression.erase(0, 1);
        }

        else if (expression[0] == 'm' and expression[1] == 'o' and expression[2] == 'd') {
            expression.erase(0, 4);
            istringstream iss(expression, istringstream::in);
            int num;
            iss >> num;

            stringstream ss;
            ss << num;
            string str = ss.str();

            expression.erase(0, str.length());

            mod = num;
        }
    }


    for (auto iter = operations.begin(); iter != operations.end(); iter++) {
        if (iter->second.operation == '+') {
            values[iter->second.order] += values[iter->second.order + 1];
            values.erase(values.begin() + iter->second.order + 1);
        }
        else if (iter->second.operation == '-') {
            values[iter->second.order] -= values[iter->second.order + 1];
            values.erase(values.begin() + iter->second.order + 1);
        }
        else if (iter->second.operation == '*') {
            values[iter->second.order] *= values[iter->second.order + 1];
            values.erase(values.begin() + iter->second.order + 1);
        }

        balance(operations, iter);
    }

    coefficient.b = values[0];
    coefficient.k = 0;
}

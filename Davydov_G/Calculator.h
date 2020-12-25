#ifndef Calculator_HPP
#define Calculator_HPP

#include <string>
#include <sstream>
#include <map>
#include<vector>

using namespace std;


struct operation {
    int order;
    char operation;
};


struct Coefficients {
    int k;
    int b;
};


void balance(multimap<int, operation>& operations, multimap<int, operation>::iterator iter);


void calculate_to_equality(string& expression, Coefficients& coefficient);


void calculate_after_equality(string& expression, Coefficients& coefficient, int& mod);

#endif

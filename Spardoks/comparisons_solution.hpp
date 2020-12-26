// Copyright 2020 Spardoks

#ifndef COMPARISONS_SOLUTION_HPP
#define COMPARISONS_SOLUTION_HPP

#include <iostream>
#include <string>
#include <vector>
#include <utility> // for std::pair
#include <limits> // for good input

// НОД
int GCD(int a, int b);

// Коэффициенты Безу, первый перед большим числом, второй перед меньшим
std::pair<int, int> get_Bezu_coefficients(int a, int b);

// НОК
int LCM(int a, int b);

/// do ai = 1 and check existing of solution
bool have_comparisons_solution(std::vector<int>& v_a, std::vector<int>& v_b, std::vector<int>& v_m);

// solve system aix = bi (mod mi)
// if pair.second == 0, no solution
std::pair<int, int> get_comparisons_solution(std::vector<int> v_a, std::vector<int> v_b, std::vector<int> v_m);

// correct input of answer
void print_answer(std::pair<int, int> b_m);

// show all system
void print_system(const std::vector<int>& v_a, const std::vector<int>& v_b, const std::vector<int>& v_m);

// get coefficients of system
void get_comparisons_coefficients(std::vector<int>& v_a, std::vector<int>& v_b, std::vector<int>& v_m);

// input var with name "name"
int get_number(std::string name);


#endif // COMPARISONS_SOLUTION_HPP

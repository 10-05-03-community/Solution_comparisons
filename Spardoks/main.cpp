#include <iostream>
#include <vector>
#include "comparisons_solution.hpp"

// uncomment to test
//#define TEST

int main() {
#ifndef TEST
    std::cout << "Comparisons_system_first_degree_solution" << std::endl;

    // get size_of_system > 0
    int n = 0;
    while (n <= 0) {
        std::cout << "system_size > 0" << std::endl;
        n = get_number("size_of_system");
    }

    // get coefficients of system
    std::vector<int> v_a(n, 0);
    std::vector<int> v_b(n, 0);
    std::vector<int> v_m(n, 0);
    get_comparisons_coefficients(v_a, v_b, v_m);

    // show system
    print_system(v_a, v_b, v_m);

    // try to solve
    std::pair<int, int> solution_b_m;
    solution_b_m = get_comparisons_solution(v_a, v_b, v_m);
    print_answer(solution_b_m);
#else
    std::vector<int> a0{ 7, 3, 1, 7};
    std::vector<int> b0{ 1, 12, 1, 12};
    std::vector<int> m0{ 9, 14, 15, 20};
    print_system(a0, b0, m0);
    std::pair<int, int> solution_b_m0;
    solution_b_m0 = get_comparisons_solution(a0, b0, m0);
    print_answer(solution_b_m0);

    std::vector<int> a1{ 1};
    std::vector<int> b1{ 2};
    std::vector<int> m1{ 16};
    print_system(a1, b1, m1);
    std::pair<int, int> solution_b_m1;
    solution_b_m1 = get_comparisons_solution(a1, b1, m1);
    print_answer(solution_b_m1);

    std::vector<int> a2{ 1, 1};
    std::vector<int> b2{ 2, 2};
    std::vector<int> m2{ 16, 16};
    print_system(a2, b2, m2);
    std::pair<int, int> solution_b_m2;
    solution_b_m2 = get_comparisons_solution(a2, b2, m2);
    print_answer(solution_b_m2);

    std::vector<int> a3{ 1, 1};
    std::vector<int> b3{ 2, 4};
    std::vector<int> m3{ 6, 9};
    print_system(a3, b3, m3);
    std::pair<int, int> solution_b_m3;
    solution_b_m3 = get_comparisons_solution(a3, b3, m3);
    print_answer(solution_b_m3);
#endif // TEST

    return 0;
}

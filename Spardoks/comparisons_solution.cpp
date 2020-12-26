// Copyright 2020 Spardoks

#include "comparisons_solution.hpp"

int GCD(int a, int b) {

    if (a * b == 0) {
        return a + b;
    } else {
        return GCD(b, a % b);
    }
}

std::pair<int, int> get_Bezu_coefficients(int a, int b) {

    if (a < b) {
        int tmp = b;
        b = a;
        a = tmp;
    }

    if (b == 0) {
        return std::make_pair(1, 0);
    }

    int step = 2;
    int last_x = 1;
    int last_y = 0;
    int x = 0;
    int y = 1;
    int q = a / b;
    int r = b;

    do {

        int new_x = last_x - q * x;
        int new_y = last_y - q * y;
        r = a % b; // a - q * b
        if (r != 0) {
            q = b / r;
            ++step;
            last_x = x;
            last_y = y;
            x = new_x;
            y = new_y;
            a = b;
            b = r;
        } else {
            break; // r == 0
        }
    } while (true);

    return std::make_pair(x, y);
}

int LCM(int a, int b) {
    if (a * b == 0) {
        return a + b;
    }  else {
        return (a * b) / GCD(a, b);
    }
}

bool have_comparisons_solution(std::vector<int> &v_a, std::vector<int> &v_b, std::vector<int> &v_m) {

    // do ai = 1
    for (size_t i = 0; i < v_a.size(); ++i) {

        // прверим, не кратно ли ai mi
        if(v_a[i] % v_m[i] == 0) {
            // если bi не 0, то решений у этой системы нет
            if (v_b[i] != 0) {
                return false;
            }
            v_a[i] = 1;
            v_b[i] = 0;
            v_m[i] = 1;
            continue;
        }

        // здесь ai не кратно mi
        // сделаем 0 < ai < mi
        if (v_a[i] < 0) {
            // v_a[i] = v_a[i] % v_m[i] - для отрицательных так нельзя
            v_a[i] = v_a[i] + (std::abs(v_a[i]) / v_m[i]) * (v_m[i] + 1);
            // if abs(v_ap[i]) was less then v_m[i]
            if (v_a[i] < 0) {
                v_a[i] += v_m[i];
            }
        } else {
            v_a[i] %= v_m[i];
        }

        // проверим кратность bi НОД(ai, mi)
        int gcd_mi_ai = GCD(v_m[i], v_a[i]);
        if (v_b[i] % gcd_mi_ai != 0) {
            // решений нет
            return false;
        }

        // здесь bi точно делится на НОД(ai, mi)
        v_a[i] /= gcd_mi_ai;
        v_b[i] /= gcd_mi_ai;
        v_m[i] /= gcd_mi_ai;

        // делаем ai = 1
        if (v_a[i] != 1) {
            std::pair<int, int> x_y_Bezu = get_Bezu_coefficients(v_m[i], v_a[i]);
            v_a[i] = 1;
            v_b[i] *= x_y_Bezu.second;
        }
    }

    // проверим условие (bi - bj) кратно НОД(mi, mj)
    for (size_t i = 0; i < v_m.size() - 1; ++i) {
        for (size_t j = i + 1; j < v_m.size(); ++j) {
            if((v_b[i] - v_b[j]) % GCD(v_m[i], v_m[j]) != 0) {
                // решений нет
                return false;
            }
        }
    }
    return true;
}

std::pair<int, int> get_comparisons_solution(std::vector<int> v_a, std::vector<int> v_b, std::vector<int> v_m) {

    if (!have_comparisons_solution(v_a, v_b, v_m)) {
        return std::make_pair(0, 0);
    }

    /*  x = bi1 + mi1 * i1                                          */
    /*  mi1 * i1 = (bi2 - bi1) (mod mi2)                            */
    /*  i1 = bi2_new + mi2_new * k                                  */
    /*  x = bi1 + mi1 * (bi2_new + mi2_new * k)                     */
    /*  x = bi1 + mi1 * bi2_new +  mi1 * mi2_new * k                */
    /*  mi1 * mi2_new  = НОК(mi1, mi2)                              */
    /*  bi2_new  = (bi2 - bi1)/НОД(mi1, mi2) * (m1/НОД(m1, m2))^-1  */

    int b1 = v_b[0];
    int m1 = v_m[0];

    for (size_t i = 1; i < v_b.size(); ++i) {

        int b2_new = v_b[i] - b1;
        int m2 = v_m[i];

        int gcd_m1_m2 = GCD(m1, m2);
        int m1_tmp = m1 / gcd_m1_m2;
        int m2_tmp = m2 / gcd_m1_m2;
        // такое можно смело сделать, так как система имеет решение, проверено выше
        b2_new = b2_new / gcd_m1_m2;

        if (m1_tmp > m2_tmp) {
            // mi always > 0
            m1_tmp %= m2_tmp;
        }

        std::pair<int, int> bezu_x_y = get_Bezu_coefficients(m2_tmp, m1_tmp);
        b2_new *= bezu_x_y.second;
        b1 = b1 + m1 * b2_new;
        m1 = LCM(m1, m2);
    }

    // сделаем ответ неотрицательным и в пределах m
    if (b1 < 0) {
        b1 = b1 + (std::abs(b1) / m1) * (m1 + 1);
        // if abs(b1) was less then m1
        if (b1 < 0) {
            b1 += m1;
        }
    } else {
        b1 %= m1;
    }

    return  std::make_pair(b1, m1);
}

void print_answer(std::pair<int, int> b_m) {

    if (b_m.second > 0) {
       std::cout << "Solved:" << std::endl;
       std::cout << ("x = " + std::to_string(b_m.first) + " ( mod " + std::to_string(b_m.second) + " )");
    } else {
        std::cout <<  "No_solution" << std::endl;
    }
    std::cout << std::endl;
}

void print_system(const std::vector<int> &v_a, const std::vector<int> &v_b, const std::vector<int> &v_m) {

    std::cout << std::endl;
    std::cout << "Your system is:" << std::endl;
    for (size_t i = 0; i < v_a.size(); ++i) {
        std::cout << v_a[i] << " * x = " << v_b[i] << " ( mod " << v_m[i] << " )" << std::endl;
    }
}

int get_number(std::string name) {

    int number = 0;
    bool good_input = false;

    while (!good_input) {
        std::cout << "Input " << name << ": ";
        std::cin >> number;
        if (std::cin.fail() || (std::cin.peek() != '\n')) {
            std::cin.clear();
            good_input = false;
            std::cout << "Bad_value. It should be integer. Try again!" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            good_input = true;
        }
    }
    return number;
}

void get_comparisons_coefficients(std::vector<int>& v_a, std::vector<int>& v_b, std::vector<int>& v_m) {

    std::cout << "Input coefficients" << std::endl;
    std::cout << "mi > 0" << std::endl;
    for (size_t i = 0; i < v_a.size(); ++i) {
        std::string i_str = std::to_string(i + 1);
        v_a[i] = get_number("a_" + i_str);
        v_b[i] = get_number("b_" + i_str);
        while (v_m[i] <= 0) {
            v_m[i] = get_number("m_" + i_str);
        }
        std::cout << std::endl;
    }
}

#include "tvector.h"
#include <iostream>
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>  
#include <stdexcept> 
#include <cstdio>
#include <Windows.h>
#include <chrono>
#include <fcntl.h>
#include <io.h>

#define STEP_OF_CAPACITY 15

void set_color(int text_color, int bg_color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bg_color << 4) | text_color);
}

namespace TestSystem {
    int count_success = 0, count_failed = 0;

    void start_test(bool(*test)(), const char* name_of_test) {
        set_color(2, 0); 
        std::cout << "[ RUN      ]"; 
        set_color(7, 0); 
        std::cout << name_of_test << std::endl; 

        try { 
            test(); 
            set_color(2, 0); 
            std::cout << "[       OK ]" << std::endl; 
            count_success++;
        }
        catch (const std::exception& e) { 
            set_color(4, 0); 
            std::cout << "[  FAILED  ] " << e.what() << std::endl; 
            count_failed++;
        }
        set_color(7, 0); 
    }

    template <class T>
    bool check(const T& expected, const T& actual) {
        if (expected == actual) {
            return true;
        }
        std::stringstream ss;
        ss << "ќжидаемый результат: " << expected << ", фактический результат: " << actual << ".";
        throw std::runtime_error(ss.str());
    }

    void print_init_info() {
        set_color(2, 0);
        std::cout << "[==========] " << std::endl;
        set_color(7, 0);
    }

    void print_final_info() {
        set_color(2, 0);
        std::cout << "[==========] ";
        set_color(7, 0);
        std::cout << count_success + count_failed << " test" << (count_success + count_failed > 1 ? "s" : "") << " ran." << std::endl;
        set_color(2, 0);
        std::cout << "[  PASSED  ] ";
        set_color(7, 0);
        std::cout << count_success << " test" << (count_success > 1 ? "s" : "") << std::endl;
        if (count_failed > 0) {
            set_color(4, 0);
            std::cout << "[  FAILED  ] ";
            set_color(7, 0);
            std::cout << count_failed << " test" << (count_failed > 1 ? "." : ".") << std::endl;
        }
    }
};

bool test_default_constructor() {
    try {
        TVector<int> vec;
        return TestSystem::check(true, vec.size() == 0 && vec.capacity() == 0);
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_1_default_constructor failed: ") + e.what());
    }
}

bool test_size_constructor() {
    const size_t test_size = 5;
    TVector<int> vec(test_size);

    if (vec.size() != test_size) {
        throw std::runtime_error("Size mismatch");
    }

    for (size_t i = 0; i < test_size; ++i) {
        vec[i] = int(i); 
    }

    return true;
}
bool test_copy_constructor() {
    try {
        TVector<int> original;
        original.push_back(1);
        original.push_back(2);
        original.push_back(3);

        TVector<int> copy(original);
        bool result = (copy.size() == original.size() &&
            copy.capacity() == original.capacity() &&
            copy[0] == original[0] &&
            copy[1] == original[1] &&
            copy[2] == original[2]);
        return TestSystem::check(true, result);
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_3_copy_constructor failed: ") + e.what());
    }
}

bool test_assignment_operator() {
    try {
        TVector<int> original;
        original.push_back(1);
        original.push_back(2);
        original.push_back(3);

        TVector<int> copy;
        copy = original;
        bool result = (copy.size() == original.size() &&
            copy.capacity() == original.capacity() &&
            copy[0] == original[0] &&
            copy[1] == original[1] &&
            copy[2] == original[2]);
        return TestSystem::check(true, result);
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_4_assignment_operator failed: ") + e.what());
    }
}

bool test_push_back() {
    try {
        TVector<int> v;
        v.push_back(42);

        TestSystem::check(static_cast<size_t>(1), v.size());
        TestSystem::check(42, v[0]);

        return true;
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_push_back failed: ") + e.what());
    }
}

bool test_push_front() {
    try {
        TVector<int> v;
        v.push_back(1);
        v.push_front(2);

        TestSystem::check(static_cast<size_t>(2), v.size());
        TestSystem::check(2, v[0]);
        TestSystem::check(1, v[1]);

        return true;
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_push_front failed: ") + e.what());
    }
}

bool test_insert() {
    try {
        TVector<int> v;
        v.push_back(1);
        v.push_back(3);
        v.insert(2, 1); 

        TestSystem::check(static_cast<size_t>(3), v.size());
        TestSystem::check(1, v[0]);
        TestSystem::check(2, v[1]);
        TestSystem::check(3, v[2]);

        return true;
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_insert failed: ") + e.what());
    }
}

bool test_pop_back() {
    try {
        TVector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.pop_back();
        TestSystem::check(static_cast<size_t>(1), v.size());
        TestSystem::check(1, v[0]);

        return true;
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_pop_back passed") + e.what());
    }
}

bool test_pop_front() {
    try {
        TVector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.pop_front();
        TestSystem::check(static_cast<size_t>(1), v.size());
        TestSystem::check(2, v[0]);
        return true;
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_pop_front passed") + e.what());
    }
}

bool test_erase() {
    try{
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.erase(1); 

    TestSystem::check(static_cast<size_t>(2), v.size());
    TestSystem::check(1, v[0]);
    TestSystem::check(3, v[1]);
    return true;
}
    catch (const std::exception& e) {

        throw std::runtime_error(std::string("test_erase passed") + e.what());
    }
}

bool test_erase_front() {
    try {
        TVector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        v.erase_front(2);
        TestSystem::check(static_cast<size_t>(1), v.size());
        TestSystem::check(3, v[0]);
        return true;
    }
    catch (const std::exception& e) {

        throw std::runtime_error(std::string("test_erase_front passed") + e.what());
    }
}

bool test_erase_back() {
    try{
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.erase_back(2);
    TestSystem::check(static_cast<size_t>(1), v.size());
    TestSystem::check(1, v[0]);
    return true;
    }
    catch (const std::exception& e) {

        throw std::runtime_error(std::string("test_erase_back passed") + e.what());
    }
}

bool test_erase_range() {
    try{
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    v.erase_range(1, 2); 

    TestSystem::check(static_cast<size_t>(2), v.size());
    TestSystem::check(1, v[0]);
    TestSystem::check(4, v[1]);
    return true;
    }catch (const std::exception& e) {

    throw std::runtime_error(std::string("test_erase_range passed") + e.what());
    }
}

bool test_assign() {
    try {
        TVector<int> v;
        v.assign(3, 7);

        TestSystem::check(static_cast<size_t>(3), v.size());
        TestSystem::check(7, v[0]);
        TestSystem::check(7, v[1]);
        TestSystem::check(7, v[2]);

        return true;
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_assign failed: ") + e.what());
    }
}

bool test_at() {
    try {
        TVector<int> v;
        v.push_back(5);

        TestSystem::check(5, v.at(0));

        return true;
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_at failed: ") + e.what());
    }
}

bool test_shrink_to_fit() {
    try {
        TVector<int> v;
        for (int i = 0; i < 10; ++i) v.push_back(i);
        v.shrink_to_fit();

        TestSystem::check(v.size(), v.capacity());

        return true;
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_shrink_to_fit failed: ") + e.what());
    }
}

bool test_resize() {
    try {
        TVector<int> v;
        v.push_back(1);
        v.resize(5, 9);

        TestSystem::check(static_cast<size_t>(5), v.size());
        TestSystem::check(9, v[4]);

        v.resize(2);
        TestSystem::check(static_cast<size_t>(2), v.size());

        return true;
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_resize failed: ") + e.what());
    }
}

bool test_clear() {
    try {
        TVector<int> v;
        v.push_back(1);
        v.clear();

        TestSystem::check(static_cast<size_t>(0), v.size());

        return true;
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_clear failed: ") + e.what());
    }
}

bool test_operator_eq() {
    try {
        TVector<int> v1, v2;
        v1.push_back(1);
        v2.push_back(1);

        if (!(v1 == v2)) {
            throw std::runtime_error("Vectors should be equal");
        }

        v2.push_back(2);

        if (v1 == v2) {
            throw std::runtime_error("Vectors should not be equal");
        }

        return true;
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_operator_eq failed: ") + e.what());
    }
}

bool test_operator_neq() {
    try {
        TVector<int> v1, v2;
        v1.push_back(1);
        v2.push_back(2);

        if (!(v1 != v2)) {
            throw std::runtime_error("Vectors should not be equal");
        }

        return true;
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_operator_neq failed: ") + e.what());
    }
}

bool test_find_first() {
    try {
        TVector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(1);

        
        TestSystem::check<int>(0, find_first(v, 1));
        TestSystem::check<int>(1, find_first(v, 2));

        return true;
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_find_first failed: ") + e.what());
    }
}

bool test_find_last() {
    try {
        TVector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(1);

        
        TestSystem::check<int>(2, find_last(v, 1));
        TestSystem::check<int>(1, find_last(v, 2));

        return true;
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_find_last failed: ") + e.what());
    }
}

bool test_find_elems() {
    try {
        TVector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(1);

        int* idxs = find_elems(v, 1);
        TestSystem::check(0, idxs[0]);
        TestSystem::check(2, idxs[1]);
        delete[] idxs;

        return true;
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_find_elems failed: ") + e.what());
    }
}

bool test_swap() {
    try {
        int a = 1, b = 2;
        swap(&a, &b);

        TestSystem::check(2, a);
        TestSystem::check(1, b);

        return true;
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_swap failed: ") + e.what());
    }
}

bool test_randomize() {
    try {
        TVector<int> v;
        for (int i = 0; i < 10; ++i) v.push_back(i);
        randomize(v);

        int sum = 0;
        for (size_t i = 0; i < v.size(); ++i) sum += v[i];

        TestSystem::check(static_cast<size_t>(10), v.size());
        TestSystem::check(45, sum);

        return true;
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_randomize failed: ") + e.what());
    }
}

bool test_hoara_sort() {
    try {
        TVector<int> v;
        v.push_back(3);
        v.push_back(1);
        v.push_back(2);
        hoara_sort(v);

        TestSystem::check(1, v[0]);
        TestSystem::check(2, v[1]);
        TestSystem::check(3, v[2]);

        return true;
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("test_hoara_sort failed: ") + e.what());
    }
}


int main() {
    setlocale(LC_ALL, "Russian");
    TestSystem::print_init_info();
    TestSystem::start_test(test_default_constructor, "TVector.test_1_default_constructor");
    TestSystem::start_test(test_size_constructor, "TVector.test_2_size_constructor");
    TestSystem::start_test(test_copy_constructor, "TVector.test_3_copy_constructor");
    TestSystem::start_test(test_assignment_operator, "TVector.test_4_assignment_operator");
    TestSystem::start_test(test_push_back, "test_push_back");
    TestSystem::start_test(test_push_front, "test_push_front");
    TestSystem::start_test(test_insert, "test_insert");
    TestSystem::start_test(test_pop_back,"test_pop_back");
    TestSystem::start_test(test_pop_front, "test_pop_front");
    TestSystem::start_test(test_erase, "test_erase");
    TestSystem::start_test(test_erase_front, "test_erase_front");
    TestSystem::start_test(test_erase_back, "test_erase_back");
    TestSystem::start_test(test_erase_range, "test_erase_range");
    TestSystem::start_test(test_assign, "test_assign");
    TestSystem::start_test(test_at, "test_at");
    TestSystem::start_test(test_shrink_to_fit, "test_shrink_to_fit");
    TestSystem::start_test(test_resize, "test_resize");
    TestSystem::start_test(test_clear, "test_clear");
    TestSystem::start_test(test_operator_eq, "test_operator_eq");
    TestSystem::start_test(test_operator_neq, "test_operator_neq");
    TestSystem::start_test(test_find_first, "test_find_first");
    TestSystem::start_test(test_find_last, "test_find_last");
    TestSystem::start_test(test_find_elems, "test_find_elems");
    TestSystem::start_test(test_swap, "test_swap");
    TestSystem::start_test(test_randomize, "test_randomize");
    TestSystem::start_test(test_hoara_sort, "test_hoara_sort");

    TestSystem::print_final_info();
    system("pause");
    return 0;
}
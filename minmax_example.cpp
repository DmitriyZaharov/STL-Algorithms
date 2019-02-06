//
// Created by claorisel on 2/6/19.
//

#include <iostream>
#include <thread>
#include <string>
#include <algorithm>
#include <iomanip>

template <class T> class TD;

using namespace std;

int main()
{


    std::cout << "==========================" << std::endl;
    std::cout << std::setprecision(20);
    {
        auto mx = std::minmax(587746.8399999999674, 587841.7700000000186);
        std::cout << mx.first << ",\t" << mx.second << std::endl;
    }
    std::cout << "==========================" << std::endl;
    {
        auto mx = std::minmax(587746.8399999999674, 587841.7700000000186);
        auto my = std::minmax(6610695.009999999776, 6610665.679999999702);

        std::cout << mx.first << ",\t" << mx.second << std::endl;
        std::cout << my.first << ",\t" << my.second << std::endl;
    }
    std::cout << " ^^^^^ WTF? ^^^^^ " << std::endl;
    std::cout << "==========================" << std::endl;

    return 1;
}

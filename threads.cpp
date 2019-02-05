#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <future>
#include <chrono>

using namespace std;
using namespace std::chrono;

//double sumVectors(const vector<double > &first, const vector<double> &second)
//{
//    return accumulate(first.begin(), first.end(), 0) + accumulate(second.begin(), second.end(), 0);
//
//}

double sumVectors(const vector<double> &first, const vector<double> &second)
{

    future<double> f1 = async(std::launch::async, [&first]{ return accumulate(first.begin(), first.end(), 0.0);});
    future<double> f2 = async(std::launch::async, [&second]{ return accumulate(second.begin(), second.end(), 0.0);});

    double r1 = f1.get();
    double r2 = f2.get();

    return r1 + r2;

}


int main() {

    vector<double > v1;
    vector<double > v2;

//    auto start = steady_clock::now();

    for (int i = 0; i < 10000000; i++)
    {
        v1.push_back(i);
        v1.push_back(i);
    }


    auto start = steady_clock::now();

    cout << sumVectors(v1, v2) << endl;


    auto finish = steady_clock::now();
    auto ms = duration_cast<microseconds>(finish - start).count();
    cout << ms << " ms" << endl;


    return 0;
}

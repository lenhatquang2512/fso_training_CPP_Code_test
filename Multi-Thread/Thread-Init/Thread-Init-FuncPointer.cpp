#include <iostream>
#include <thread>
#include <algorithm>
#include <chrono>

using namespace std;
typedef unsigned long long ull;
//Thêm cờ -std=c++11 -pthread  

ull OddSum = 0;
ull EvenSum = 0;

void findEven(ull start, ull end){
    for (ull i = start; i <= end; ++i){
        if ((i & 1) == 0){
            EvenSum += i;
        }
    }
}

void findOdd(ull start, ull end){
    for (ull i = start; i <= end; ++i){
        if ((i & 1) == 1){
            OddSum += i;
        }
    }
}

int main(){
    ull start = 0, end = 1900000000;


    /* Initialize the thread via function pointer */
    std::thread t1(findEven, start, end);
    std::thread t2(findOdd, start, end);

    /* Joining the thread */
    t1.join();
    t2.join();

    cout << "Odd sum: " << OddSum << endl;
    cout << "Even sum: " << EvenSum << endl;  

    return 0;
}
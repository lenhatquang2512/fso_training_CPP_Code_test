/**
 * C++11 Thread: Lock_guard (std::lock_guard<mutex> lock(m1))
 * 
 * 1. It is very light weight wrapper for owning mutex on scoped basis
 * 2. It acquire mutex lock the moment you create the object of lock_guard
 * 3. It automatically removes the lock while goes out of scope
 * 4. You can noy explicitly unlock the lock_guard
 * 5. You can not copy lock_guard()
*/

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

std::mutex m1;
int buffer = 0;

void task(const char* threadNumber, int loopFor){
    std::lock_guard<mutex> lock(m1);
    for (int i = 0; i < loopFor; i++){
        buffer++;
        cout << threadNumber << buffer << endl;
    }
}

int main(){
    thread t1(task, "T0", 10);
    thread t2(task, "T1", 10);

    t1.join();
    t2.join();
    return 0;
}
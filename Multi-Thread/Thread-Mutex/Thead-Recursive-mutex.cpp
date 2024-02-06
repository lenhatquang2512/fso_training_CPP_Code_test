/**
 * C++11 Thread: Recursive Mutex
 * 1. It is same as mutex but, Same thread can lock one mutex mutiple times using recursive_mutex
 * 2. If thread T1 first lock/try_lock on recursive mutex m1, them m1 is locked by T1, now as
 *    T1 is running in recursion T1 can all lock/try_lock on the mutex m1 then T1 will have to unlock
 * 3. But if T1 have acquired 10 times lock/try_lock() on mutex m1 then thread m1 will have to unlock
 *    it 10 times otherwise no other thread will be able to lock mutex m1.
 *    It means recursive_mute4x keeps count how many times it was locked so that many times it should be unlocked
 * 4. How many time we can lock recursive_mutex is not defined but when that number reaches and if we were calling lock()
 *    it will return std::system_error 
 *    OR if we were calling try_lock() then it will return false.
 * 
 * BOTTOM LINE
 * 1. It is similar to mutex but have extra facility that it can be locked multiple time by same thread
 * 2. If we can avoid recursive_mutex then we should because it brings overhead to the system
 * 3. It can be used in loops also
*/

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

/* Example 1: With recursion */
std::recursive_mutex m1;
int buffer = 0;

void recursion(char c, int loopFor){
    if (loopFor < 0)
        return;
    m1.lock();
    cout << c << " " << buffer++ << endl;
    recursion(c, --loopFor);
    m1.unlock();
    cout << "Unlock mutex by thread" << c;
}

// int main(){
//     thread t1(recursion, '0', 10);
//     thread t2(recursion, '1', 10);
//     t1.join();
//     t2.join();
//     return 0;
// }

/* Example 2: With loop*/
std::recursive_mutex m2;
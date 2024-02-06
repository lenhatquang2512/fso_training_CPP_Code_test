/**
 * C++11 Thread: unique_lock (std::unique_lock<mutex> lock(m1)) 
 * 
 * 1. The class unique_lock is a mutex ownership wrapper
 * 2. It allows
 *      a. Can have different locking strategies
 *      b. time-constrained attempts at locking (try_lock_for, try_lock_until)
 *      c. resursive locking
 *      d. Transfer or lock ownership (move not copy)
 *      e. Condition variables. (upcoming topic)
 * 
 * 3. Locking strategies
 *      a. defer_lock: do not acquire ownership of the mutex
 *      b. try_to_lock: try to acquire ownership of the mutex without blocking
 *      c. adopt_lock: assume the calling thread already has ownership of the mutex
*/

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

std::mutex m1;
int buffer = 0;

#define EXAMPLE 2

#if (EXAMPLE == 1)
void task(const char* threadNumber, int loopFor){
    std::unique_lock<mutex> lock(m1);
    for (int i = 0; i < loopFor; i++){
        buffer++;
        cout << threadNumber << buffer << endl;
    }
}
#elif (EXAMPLE == 2)
void task(const char* threadNumber, int loopFor){\
    /* Does not call lock on mutex m1, because used defer_lock */
    std::unique_lock<mutex> lock(m1, std::defer_lock);
    /* But then we will have to explicitly tell to lock whenever we want to lock mutex m1 */
    lock.lock();
    for (int i = 0; i < loopFor; i++){
        buffer++;
        cout << threadNumber << buffer << endl;
    }
    /* lock.unlock() is not needed as it will be unlocked in destructor of unique_lock()*/
    // lock.unlock();
}
#endif

int main(){
    thread t1(task, "T1", 10);
    thread t2(task, "T2", 10);
    t1.join();
    t2.join();
    return 0;
}

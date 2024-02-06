/**
 * Timed Mutex In C++11 threading (std::timed_mutex)
 * (Pre: Race Condition, Critical Section)
 * 
 * 1. std::timed_mutex is blocked till timeout_time or the lock is acquired and returns true if success
 *    , otherwise false
 * 2. Member function
 * a. Lock
 * b. try_lock
 * c. try_lock_for
 * d. try_lock_until (c. and d. make it different from mutex)
 * e. unlock
 * 
 * Example: try_lock_for()
 * Waits until specified timeout_duration has elapsed or the lock is acquired, whichever comes first.
 * On successful lock acquisition returns true, otherwise returns false
*/ 

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

int myAmount = 0;
std::timed_mutex m;

/* Implement of try_lock_for() */
void increment(int i){
    /* If change the time to 2, thread 2 also gets the mutex */
    if (m.try_lock_for(std::chrono::seconds(1))){
        ++myAmount;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        cout << "Thread " << i << " Entered" << endl;
        m.unlock();
    }
    else{
        cout << "Thread " << i << " couldn't Enter" << endl;
    }
}

/* Implement of try_lock_until() */
void incrementAnother(int i){
    /* If change the time to 2, thread 2 also gets the mutex */
    auto now = std::chrono::steady_clock::now();
    if (m.try_lock_until(now + std::chrono::seconds(1))){
        ++myAmount;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        cout << "Thread " << i << " Entered" << endl;
        m.unlock();
    }
    else{
        cout << "Thread " << i << " couldn't Enter" << endl;
    }
}

int main(){
    std::thread t1(increment, 1);
    std::thread t2(increment, 2);

    t1.join();
    t2.join();

    cout << myAmount << endl;

    return 0;
}
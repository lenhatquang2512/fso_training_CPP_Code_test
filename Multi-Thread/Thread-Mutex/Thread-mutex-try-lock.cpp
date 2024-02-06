#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int counter = 0;
std::mutex mtx;

/**Some of try_lock() function
 * 1. std::try_lock()
 * 2. std::mutex::try_lock();
 * 3. std::shared_lock::try_lock()
 * 4. std::timed_mutex::try_lock()
 * 5. std::unique_lock::try_lock()
 * 6. std::shared_lock::try_lock()
 * 7. std::recursive_mutex::try_lock()
 * 8. std::shared_timed_mutex::try_lock()
 * 9. std::recursive_timed_mutex::try_lock()
 */


/**
 * std::mutex::trylock()
 * 
 * try_lock() tries to lock the mutex. return immediately. On successfull lock acquisition returns true otherwise returns false
 * - If try_lock() is not able to lock muten, then it doesn't got blocked that's why it is called non-blocking
 * - If try_lock is called again by the same thread with owns the mutex (double try_lock is not allowed on the same mutex by same thread), the behavior is undefined
 *   it's a dead lock situation with undefined behaviour. (if you want to be able to lock the same mutex by the same thread
 *   more than one time the gor for recursive_mutex() )
*/
void increaseTheCounterFor100000Times(){
    for (int i = 0; i < 100000; i++){
        if (mtx.try_lock()){
            ++counter;
            mtx.unlock();
        }
    }
}

int main(){
    std::thread t1(increaseTheCounterFor100000Times);
    std::thread t2(increaseTheCounterFor100000Times);

    t1.join();
    t2.joinable();

    cout << "Counter could increase upto: " << counter << endl;
    return 0;
}
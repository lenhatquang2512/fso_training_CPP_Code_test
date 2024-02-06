/**
 * std::try_lock() in C++11
 * 1. std::try_lock() tries to lock all the lockable objects passed in it one by one in given order
 *      std::try_lock(m1, m2, m3, m4)
 * 2. On success this function return -1, otherwise it will return 0-based mutex number which it could not lock
 * 3. If it fails to lock any of the mutex then it will release all the mutex it locked before
 * 4. If a call to try_lock() results in an exception, unlock is clled for any locked objects before rethrowing
 * 
 * Actual use: try to lock mutiple mutex objects at the same time
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

int x = 0, y = 0;
std::mutex m1, m2;

void doSomeWorkForSeconds(int second){
    std::this_thread::sleep_for(std::chrono::seconds(second));
}

void incrementXY(int& XorY, std::mutex& m, const char* desc){
    for (int i = 0; i < 5; ++i){
        m.lock();
            ++XorY;
        cout << desc << XorY << endl;
        m.unlock();
        doSomeWorkForSeconds(1);
    }
}

void consumeXY(){
    int useCount = 5;
    int XplusY = 0;
    while(1){
        int lockResult = std::try_lock(m1, m2);
        if(lockResult == -1 ){
            if (x != 0 && y != 0){
                --useCount;
                XplusY += x + y;
                x = 0;
                y = 0;
                cout << "XplusY" << XplusY << endl;
            }
            m1.unlock();
            m2.unlock();
            if (useCount == 0 ) break;
        }
    }
}

int main(){
    
    std::thread t1(incrementXY, std::ref(x),std::ref(m1), "X ");
    std::thread t2(incrementXY, std::ref(y),std::ref(m2), "X ");
    std::thread t3(consumeXY);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
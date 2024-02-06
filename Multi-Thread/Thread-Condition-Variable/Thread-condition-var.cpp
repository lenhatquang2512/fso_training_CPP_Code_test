/**
 * C++11 Thread: Condition Variable
 * 
 * IMPORTANT: Used for two purpose
 * A. Notify other threads
 * B. Waiting for some conditions
 * 
 * 1. Condition variable allows running threads to wait on some conditions and once those conditions are met the waiting thread
 *    is notified using
 *    a. notify_one();
 *    b. notify_all();
 * 2. You need mutex to use conditon variable
 * 3. If some thread want to wait on some condition then it has to do these things:
 *    a. Acquire the mutex lock using std::unique_lock<std::mutex> lock(m)
 *    b. Execute wait, wait_for, or wait_until. The wait operations atomically release the mutex
 *       and suspend the execution of the thread
 *    c. When the condition variable is notified, the thread is awakened, and the mutex is atomiucally reacquired.
 *       The thread should then check the condition and resume waiting if the wake up was spurious
 * 
 * NOTE:
 * 1. Condition variables are used to synchronize two or more threads
 * 2. Best use case of condition variable is Producer/Consumer Problem
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

std::condition_variable cv;
std::mutex m;
long balance = 0;

void addMoney(int money){
    std::lock_guard<mutex> lg(m);
    balance += money;
    cout << "Amount Added current Balance: " << balance << endl;
    cv.notify_one(); 
}

void withdrawMoney(int money){
    std::unique_lock<mutex> ul(m);
    cv.wait(ul,[]{return (balance != 0) ? true : false; });
    if (balance >= money){
        balance -= money;
        cout << "Amount deducted: " << money << endl;
    }
    else{
        cout << "Amount can't be deducted, Current Balance is less than " << money << endl;
    }
    cout << "Current balance is: " << balance << endl;
}

int main(){
    std::thread t1(withdrawMoney, 100);
    std::thread t2(addMoney, 100);

    t1.join();
    t2.join();

    return 0;
}
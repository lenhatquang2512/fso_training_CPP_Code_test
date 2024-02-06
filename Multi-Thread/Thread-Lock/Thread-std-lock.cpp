/**
 * C++11 thread: std::lock()
 * 
 * Used to lock multiple mutex at the same time
 * 
 * IMPORTANT: 
 * Syntax: std::lock(m1, m2, m3, m4)
 * 1. All arguments are locked via a sequence of calls to lock(), try_lock(), or unlock() on each arg
 * 2. Order of locking is not defined (it will try to lock provied mutex in any order and ensure that
 *    there is no deadlock)
 * 3. It is a blocking call
 * 
 * [Example: 0] -> No deadlock
 * Thread 1                         Thread 2
 * std::lock(m1, m2);               std::lock(m1, m2)
 * 
 * [Example: 1] -> No deadlock
 * Thread 1                         Thread 2
 * std::lock(m1, m2);               std::lock(m2, m1)
 * 
 * [Example: 2] -> No deadlock
 * Thread 1                         Thread 2
 * std::lock(m1, m2, m3, m4);       std::lock(m1, m2)
 *                                  std::lock(m3, m4)
 * 
 * [Example: 3] -> Can make deadlock
 * Thread 1                         Thread 2
 * std::lock(m1, m2);               std::lock(m3, m4)
 * std::locl(m3,  m4);              std::lock(m1, m2)
*/

#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1, m2;

void task_a(){
    while (1)
    {
        std::lock(m1, m2);
        std::cout << "Task a" << std::endl;
        m1.unlock();
        m2.unlock();
    }   
}

void task_b(){
    while (1)
    {
        std::lock(m2, m1);
        std::cout << "Task b" << std::endl;
        m2.unlock();
        m1.unlock();
    }   
}

int main(){
    std::thread th1(task_a);
    std::thread th2(task_b);

    th1.join();
    th2.join();

    return 0;
}
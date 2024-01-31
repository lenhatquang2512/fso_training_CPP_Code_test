/**
 * @file Naive_Singleton.cpp
 * @author QuynhDT13
 * @brief 
 * @version 0.1
 * @date 2024-01-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <mutex>

using namespace std;

class Base
{
private:
    static mutex mMutex;
    static Base* instance;
    int x;
    Base(/* args */){cout << "Base constructor" << endl;}
    Base(int x) {cout << "Base parameter constructor" << endl;}   ;
public:
    static Base* getintance(){
        /**
         * @brief if not have mutex -> naive singleton
         * not to only single instance
         * 
         */
        // lock_guard<mutex> lock(mMutex);
        if(instance == nullptr){
            instance = new Base();
        }
        // mLocker.unlock();
        return instance;
    }
    ~Base();
};
Base *Base::instance = nullptr;
mutex Base::mMutex;

Base::~Base()
{
}
int main(){
    Base *singleton1 = Base::getintance();
    Base *singleton2 = Base::getintance();
    cout << &singleton1 << "  " << &singleton2 << endl;
    /**
     * @brief Base constructor
            0xff0f7ffaa8  0xff0f7ffaa0
     * --> so not is 1 instance :)))
     */
}
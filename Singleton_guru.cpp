/**
 * @file Singleton_guru.cpp
 * @author QuangLN6, KhanhND52
 * @brief Thread safe Eager Initialization Singleton Design Pattern with 2 Templates
 * @version 0.1
 * @date 2024-01-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <mutex>
#include <thread>
#include <algorithm>  

#define PRINT_CMD(x) (std::cout << x << std::endl)

namespace DesignPattern{

class IllegalLogicException
{
public:
    IllegalLogicException() = default;
    ~IllegalLogicException() = default;
};

template <typename T,typename S>
class SingletonSample{
private:
    T stopVal;
    S myVec;
    static SingletonSample* myInstance;
    static std::mutex myLocker;
    SingletonSample(const T stopVal_, const S vec_):
        stopVal(stopVal_),myVec(vec_){
            auto it = *(std::min_element(myVec.begin(), myVec.end())); 
            if(stopVal <static_cast<T>(it)){
                throw IllegalLogicException();
            }   
            PRINT_CMD("Constructor called");
        }

public:
    //no copy constructor
    SingletonSample(SingletonSample &otherCopy) = delete;
    //no overloading assignment operator (Not assignable)
    SingletonSample& operator=(const SingletonSample &rhs) = delete;

    ~SingletonSample(void){
        PRINT_CMD("Destructor called");
    }

    static void destroy(void){
        if(nullptr != myInstance){
            delete myInstance;
            myInstance = nullptr;
        }
    }

    // static method that controls the access to the singleton
    static SingletonSample* getMyInstance(const T stopVal_,const S vec_);
    void someBusinessLogic(void) const ;

    //Encapsulation
    inline T getStopVal(void) const {return stopVal;};
    inline S getVec(void) const {return myVec;};
    inline void setStopVal(T stopVal_) { stopVal = stopVal_;};
    inline void setmyVec(S myVec_) { myVec = myVec_;};
};
}

//global init to instacne
template <typename T,typename S>
DesignPattern::SingletonSample<T,S>* 
  DesignPattern::SingletonSample<T,S>::myInstance = nullptr;

//global declare to locker
template <typename T,typename S>
std::mutex DesignPattern::SingletonSample<T,S>::myLocker;

//outside namespace implementation
template <typename T,typename S>
DesignPattern::SingletonSample<T,S>* 
 DesignPattern::SingletonSample<T,S>::getMyInstance(const T stopVal_,const S vec_){
    std::lock_guard<std::mutex> lock(myLocker);
    if(myInstance == nullptr){
        myInstance = new DesignPattern::SingletonSample<T,S>(stopVal_,vec_);
    }
    return myInstance;
}

template <typename T,typename S>
void DesignPattern::SingletonSample<T,S>::someBusinessLogic(void) const {
    for(const auto &v : myVec){
        if(static_cast<T>(v) < stopVal){
            PRINT_CMD(v);
        }
    }
}

void ThreadMain(void){
    // Following code emulates slow initialization
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::vector<int> vect{ 5,10,15,20,25,30,35,40 };

    try{
        DesignPattern::SingletonSample<int,std::vector<int>>* singleObj = 
            DesignPattern::SingletonSample<int,std::vector<int>>::getMyInstance(28,vect);
        PRINT_CMD("Thread one said: ");
        singleObj->someBusinessLogic();
    }
    catch(const DesignPattern::IllegalLogicException &ex){
        PRINT_CMD("Could not create single object");
    }
    // singleObj->destroy();
}

void ThreadOther(void){
    // Following code emulates slow initialization
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::vector<int> vect{ 2,4,6,8,10,12,14,16,18,20,24,26,28 };

    try{
        DesignPattern::SingletonSample<int,std::vector<int>>* singleObj = 
            DesignPattern::SingletonSample<int,std::vector<int>>::getMyInstance(25,vect);
        PRINT_CMD("Thread two said: ");
        singleObj->someBusinessLogic();
    }
    catch(const DesignPattern::IllegalLogicException &ex){
        PRINT_CMD("Could not create single object");
    }
    // singleObj->destroy();
}

//Main driver code
int main(int argc, char const *argv[]){
    PRINT_CMD("If you see the same value, then singleton was reused (yay!\n" <<
            "If you see different values, then 2 singletons were created (booo!!)\n\n" <<
            "RESULT:");   
    std::thread t1(ThreadMain);
    std::thread t2(ThreadOther);
    t1.join();
    t2.join();
    DesignPattern::SingletonSample<int,std::vector<int>>::destroy();
    return 0;
}

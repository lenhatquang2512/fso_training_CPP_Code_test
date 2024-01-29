/**
 * @file InhePolySingletonTest.cpp
 * @author Quang N Le
 * @brief Full test code to illustrate Inheritance and Polymorphism in C++
 *         also combining namespace, template and many keywords
 *          Using Eager/Lazy Singleton Design Pattern
 * @version 0.1
 * @date 2024-01-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <memory>
#include <mutex>

#define PRINT_CMD(x) (std::cout << x << std::endl)

/**
 * @brief Inheritance and polymorphism sample
 * 
 */
// Singleton design pattern is typically used when you want to ensure a class has 
// only one instance and a global point of access to it. 
namespace PolySample{

template <typename T>
class Base  {
private:
    static Base* instance;
    static std::mutex mLocker;
protected:
    T a;
    // explicit Base(void) :
    // Base(static_cast<T>(200)){ std::cout << "Base constructor no args called" << std::endl;};
    explicit Base() = default;
    explicit Base(T a_):
        a{a_}{ std::cout << "Base constructor with args called" << std::endl;};
public:
    // Base(const Base &source) = delete; //delete copy constructor

    static Base* getInstance(T a_ = static_cast<T>(200)){
        mLocker.lock();
        if(instance == nullptr){
            instance = new Base<T>(a_);
        }
        mLocker.unlock();
        return instance;
    }
    virtual ~Base() {std::cout << "Base destructor called" << std::endl;};
    virtual inline T getData(void) const { std::cout << "Get base data " << this->a << std::endl; return this->a;};
    virtual inline void setData(T a_des) {a = a_des;};
    virtual inline void display(void) const = 0; // Pure virtual function
};

template<typename T>
Base<T>* Base<T>::instance = nullptr;

template<typename T>
std::mutex Base<T>::mLocker;

template <typename T>
class Derived final : public Base<T>{
private:
    static Derived* instance;
    static std::mutex mLocker;
    explicit Derived() = default;
    // explicit Derived(void): // explicit mark constructors to not implicitly convert types
    //     Derived{static_cast<T>(25),static_cast<T>(12)}{std::cout << "Derived constructor no args called" << std::endl;};
    explicit Derived(T a_, T b_ = static_cast<T>(1)):
        Base<T>{a_}, b{b_}{
            std::cout << "Derived constructor with args called" << std::endl;
        };
protected:
    T b;
public:
    
    // Derived(const Derived &source) = delete; //delete copy constructor
    static Derived* getInstance(T a_, T b_){
        mLocker.lock();
        if(instance == nullptr){
            instance = new Derived<T>(a_,b_);
        }
        // static Database mInstance(name);  //Lazy
        // return &mInstance;
        mLocker.unlock();
        return instance;
    }
    virtual ~Derived() {std::cout << "Derived destructor called" << std::endl;}
    virtual inline T getData(void) const override final {std::cout << "Get derived data: " << this->a <<std::endl; return this->b;}
    virtual inline void setData(T b_des) override final {b = b_des;};
    virtual inline void display(void) const override final { std::cout << this->a << " " << b << std::endl;}

};

template<typename T>
Derived<T>* Derived<T>::instance = nullptr;

template<typename T>
std::mutex Derived<T>::mLocker;

template <typename T>
void use(Base<T>* base) {
    base->display();
}
}

int main(int argc, char const *argv[])
{
    //Base class pointer
    PRINT_CMD("-------------USING BASE CLASS POINTER:---------------------");
    // PolySample::Base<int> *p =  PolySample::Derived<int>::getInstance(20,24);
    // int result = p->getData();
    // std::cout << "The result is " << result << std::endl;
    // p->display();
    // delete p; 
    
    // // Base class reference
    PRINT_CMD("-------------USING BASE CLASS REFERENCE--------------------:");
    // PolySample::Derived<int> *deriv = PolySample::Derived<int>::getInstance(15,8);
    // auto deriv = PolySample::Derived<int>::getInstance(15,8);
    // PolySample::Base<int> &ref = *deriv;
    // ref.display();

    //Using with vector (ONLY 1 INSTANCE)
    PRINT_CMD("---------------USING WITH VECTOR OF RAW POINTERS:--------------");
    // std::vector<PolySample::Derived<int>*> deriveds { PolySample::Derived<int>::getInstance(12,34)}; //Only one instance
    // for (const auto item : deriveds) {
    //     use(item);
    // }
    // //TODO: Remember to delete the allocated memory to avoid memory leaks!
    // for (auto item : deriveds) {
    //     delete item;
    // }

    // //Using with smart pointer
    PRINT_CMD("---------------USING WITH SMART POINTER:-------------------------");
    // std::unique_ptr<PolySample::Base<int>> pSmart = 
    // std::make_unique<PolySample::Derived<int>>(*deriv);
    // pSmart->display(); 

    std::vector<std::unique_ptr<PolySample::Base<int>>> vecSmarts;
    vecSmarts.push_back(std::make_unique<PolySample::Derived<int>>(
        *(PolySample::Derived<int>::getInstance(15,8)))); // comment out delete copy constructor

    for(const auto &v: vecSmarts){
        v->display();
        v->getData();
    }

    // Test explicit
    // PolySample::Base<int> obj;
    // obj = 10;
    // obj.getData();

    return 0;
}

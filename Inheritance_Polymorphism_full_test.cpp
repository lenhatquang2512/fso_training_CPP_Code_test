/**
 * @file polymorphism_test.cpp
 * @author Quang Le (quangle@umich.edu)
 * @brief Full test code to illustrate Inheritance and Polymorphism in C++
 *         also combining namespace, template and many keywords
 * @version 0.1
 * @date 2024-01-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <memory>

#define PRINT_CMD(x) (std::cout << x << std::endl)

/**
 * @brief Inheritance and polymorphism sample
 * 
 */
namespace PolySample{

template <typename T>
class Base  {
protected:
    T a;
public:
    explicit Base(void) :
        Base(static_cast<T>(200)){ std::cout << "Base constructor no args called" << std::endl;};
    explicit Base(T a_):
        a{a_}{ std::cout << "Base constructor with args called" << std::endl;};
    virtual ~Base() {std::cout << "Base destructor called" << std::endl;};
    virtual inline T getData(void) const { std::cout << "Get base data " << this->a << std::endl; return this->a;};
    virtual inline void setData(T a_des) {a = a_des;};
    virtual inline void display(void) const = 0; // Pure virtual function
    // virtual inline void display(void) const { std::cout << this->a << " "  << std::endl;}; // Pure virtual function
};

template <typename T>
class Derived final : public Base<T>{
protected:
    T b;
public:
    explicit Derived(void): // explicit mark constructors to not implicitly convert types
        Derived{static_cast<T>(25),static_cast<T>(12)}{std::cout << "Derived constructor no args called" << std::endl;};
    explicit Derived(T a_, T b_ = 1):
        Base<T>{a_}, b{b_}{
            // a = 4; b = 5;
            std::cout << "Derived constructor with args called" << std::endl;
        };
    // virtual ~Derived() = default;
    virtual ~Derived() {std::cout << "Derived destructor called" << std::endl;}
    virtual inline T getData(void) const override final {std::cout << "Get derived data: " << this->a <<std::endl; return this->b;}
    virtual inline void setData(T b_des) override final {b = b_des;};
    virtual inline void display(void) const override final { std::cout << this->a << " " << b << std::endl;}

};

template <typename T>
void use(Base<T>* base) {
    base->display();
}
}

int main(int argc, char const *argv[])
{
    //Base class pointer
    PRINT_CMD("-------------USING BASE CLASS POINTER:---------------------");
    // Base *p = new Derived();
    PolySample::Base<int> *p = new PolySample::Derived<int>{20,24}; //Created Derived object on the Heap
    int result = p->getData();
    // std::cout << "The result is " << result << std::endl;
    p->display();
    delete p; 
    
    // Base class reference
    PRINT_CMD("-------------USING BASE CLASS REFERENCE--------------------:");
    PolySample::Derived<int> deriv{25,12};
    PolySample::Base<int> &ref = deriv;
    ref.display();

    //Using with vector
    PRINT_CMD("---------------USING WITH VECTOR OF RAW POINTERS:--------------");
    std::vector<PolySample::Derived<int>*> deriveds { new PolySample::Derived<int>, new PolySample::Derived<int> };
    for (const auto item : deriveds) {
        use(item);
    }
    //TODO: Remember to delete the allocated memory to avoid memory leaks!
    for (auto item : deriveds) {
        delete item;
    }

    //Using with smart pointer
    PRINT_CMD("---------------USING WITH SMART POINTER:-------------------------");
    std::shared_ptr<PolySample::Base<int>> pSmart = std::make_shared<PolySample::Derived<int>>(deriv);
    pSmart->display(); 

    std::vector<std::shared_ptr<PolySample::Base<int>>> vecSmarts;
    vecSmarts.push_back(std::make_shared<PolySample::Derived<int>>(deriv));
    vecSmarts.push_back(std::make_shared<PolySample::Derived<int>>(deriv));
    vecSmarts.push_back(std::make_shared<PolySample::Derived<int>>(deriv));

    for(const auto &v: vecSmarts){
        // v->display();
        v->getData();
    }


    // Test explicit
    // PolySample::Base<int> obj;
    // obj = 10;
    // obj.getData();

    return 0;
}

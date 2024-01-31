/**
 * @file Prototype_guru_Khanh.cpp
 * @author NgDKhanh
 * @brief 
 * @version 0.1
 * @date 2024-01-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>

#define PRINT_CMD(x) (std::cout << x << std::endl)

/**
 * @brief Inheritance and polymorphism sample
 * 
 */
namespace PolySample{

enum CloneType
{
    PROTOTYPE_1 = 0,
    PROTOTYPE_2
};

template <typename T>
class Base  {
protected:
    T a;
public:
    explicit Base(void) :
        Base(static_cast<T>(200)){ std::cout << "Base constructor no args called" << std::endl;};
    explicit Base(T a_):
        a{a_}{ std::cout << "Base constructor with args called" << std::endl;};
    Base(const Base<T> &d): a{d.a} { std::cout << "Base copy constructor called" << std::endl; }
    virtual ~Base() {std::cout << "Base destructor called" << std::endl;};
    virtual inline T getData(void) const { std::cout << "Get base data " << this->a << std::endl; return this->a;};
    virtual inline void setData(T a_des) {a = a_des;};
    virtual inline void display(void) const = 0; // Pure virtual function
    // virtual inline void display(void) const { std::cout << this->a << " "  << std::endl;}; // Pure virtual function
    virtual inline std::shared_ptr<Base> Clone() const = 0;
};

template <typename T>
class DerivedType1: public Base<T>{
protected:
    T b;
public:
    explicit DerivedType1(void): // explicit mark constructors to not implicitly convert types
        DerivedType1{static_cast<T>(25),static_cast<T>(12)}{std::cout << "DerivedType1 constructor no args called" << std::endl;};
    explicit DerivedType1(T a_, T b_ = 1):
        Base<T>{a_}, b{b_}{
            // a = 4; b = 5;
            std::cout << "DerivedType1 constructor with args called" << std::endl;
        };
    DerivedType1(const DerivedType1<T> &d): Base<T>{d}, b{d.b} { std::cout << "DerivedType1 copy constructor called" << std::endl; }
    // virtual ~DerivedType1() = default;
    virtual ~DerivedType1() {std::cout << "DerivedType1 destructor called" << std::endl;}
    virtual inline T getData(void) const override {std::cout << "Get DerivedType1 data: " << this->a <<std::endl; return this->b;}
    virtual inline void setData(T b_des) override {b = b_des;};
    virtual inline void display(void) const override final { std::cout << this->a << " " << b << std::endl;}
    virtual inline std::shared_ptr<Base<T>> Clone() const override { return std::make_shared<DerivedType1<T>>(*this); }
};

template <typename T>
class DerivedType2: public Base<T>{
protected:
    T b;
    T c;
public:
    explicit DerivedType2(void): // explicit mark constructors to not implicitly convert types
        DerivedType2{static_cast<T>(25),static_cast<T>(12)}{std::cout << "DerivedType2 constructor no args called" << std::endl;};
    explicit DerivedType2(T a_, T b_ = 1, T c_ = 2):
        Base<T>{a_}, b{b_}, c{c_}{
            // a = 4; b = 5;
            std::cout << "DerivedType2 constructor with args called" << std::endl;
        };
    DerivedType2(const DerivedType2<T> &d): Base<T>{d}, b{d.b}, c{d.c} { std::cout << "DerivedType2 copy constructor called" << std::endl; }
    // virtual ~DerivedType1() = default;
    virtual ~DerivedType2() {std::cout << "DerivedType2 destructor called" << std::endl;}
    virtual inline T getData(void) const override final {std::cout << "Get DerivedType2 data: " << this->a <<std::endl; return this->b;}
    virtual inline void setData(T b_des) override {b = b_des;};
    virtual inline void display(void) const override { std::cout << this->a << " " << b << " " << c << std::endl;}
    virtual inline std::shared_ptr<Base<T>> Clone() const override { return std::make_shared<DerivedType2<T>>(*this); }
};

template<typename T>
class PrototypeFactory 
{
private:
    std::unordered_map<CloneType, std::shared_ptr<Base<T>>, std::hash<int>> prototypes;
public:
    PrototypeFactory()
    {
        prototypes[CloneType::PROTOTYPE_1] = std::make_shared<DerivedType1<T>>();
        prototypes[CloneType::PROTOTYPE_2] = std::make_shared<DerivedType2<T>>(); 
    }

    ~PrototypeFactory()
    {
        std::cout << "Deleting Prototype Factory" << std::endl;
    }

    std::shared_ptr<Base<T>> CreatePrototype(CloneType type)
    {
        return prototypes[type]->Clone();
    }
};

template <typename T>
void use(std::shared_ptr<Base<T>> base) {
    base->display();
}
}

int main(int argc, char const *argv[])
{
    /*
    //Base class pointer
    PRINT_CMD("-------------USING BASE CLASS POINTER:---------------------");
    // Base *p = new DerivedType1();
    PolySample::Base<int> *p = new PolySample::DerivedType1<int>{20,24}; //Created DerivedType1 object on the Heap
    int result = p->getData();
    // std::cout << "The result is " << result << std::endl;
    p->display();
    delete p; 
    
    // Base class reference
    PRINT_CMD("-------------USING BASE CLASS REFERENCE--------------------:");
    PolySample::DerivedType1<int> deriv{25,12};
    PolySample::Base<int> &ref = deriv;
    ref.display();

    //Using with vector
    PRINT_CMD("---------------USING WITH VECTOR OF RAW POINTERS:--------------");
    std::vector<PolySample::DerivedType1<int>*> DerivedType1s { new PolySample::DerivedType1<int>, new PolySample::DerivedType1<int> };
    for (const auto item : DerivedType1s) {
        use(item);
    }
    //TODO: Remember to delete the allocated memory to avoid memory leaks!
    for (auto item : DerivedType1s) {
        delete item;
    }

    //Using with smart pointer
    PRINT_CMD("---------------USING WITH SMART POINTER:-------------------------");
    std::shared_ptr<PolySample::Base<int>> pSmart = std::make_shared<PolySample::DerivedType1<int>>(deriv);
    pSmart->display(); 

    std::vector<std::shared_ptr<PolySample::Base<int>>> vecSmarts;
    vecSmarts.push_back(std::make_shared<PolySample::DerivedType1<int>>(deriv));
    vecSmarts.push_back(std::make_shared<PolySample::DerivedType1<int>>(deriv));
    vecSmarts.push_back(std::make_shared<PolySample::DerivedType1<int>>(deriv));

    for(const auto &v: vecSmarts){
        // v->display();
        v->getData();
    }
    */

    PRINT_CMD("---------------: USING PROTOTYPE DESIGN PATTERN :---------------");
    std::unique_ptr<PolySample::PrototypeFactory<int>> Factory = std::make_unique<PolySample::PrototypeFactory<int>>();
    std::shared_ptr<PolySample::Base<int>> Clone1 = Factory->CreatePrototype(PolySample::CloneType::PROTOTYPE_1);
    std::shared_ptr<PolySample::Base<int>> Clone2 = Factory->CreatePrototype(PolySample::CloneType::PROTOTYPE_2);
    PolySample::use(Clone1);
    PolySample::use(Clone2);
    Clone1->setData(100);
    Clone2->setData(200);
    PolySample::use(Clone1);
    PolySample::use(Clone2);
    return 0;
}

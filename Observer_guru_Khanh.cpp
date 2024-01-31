/**
 * @file Observer_guru_Khanh.cpp
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
#include <list>

#define PRINT_CMD(x) (std::cout << x << std::endl)

/**
 * @brief Inheritance and polymorphism sample
 * 
 */
namespace PolySample{

enum Status
{
    SAVED = 0,
    CHANGE,
    UNSAVED
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
    virtual inline void update(std::string message, Status status, T number) const = 0;
    // virtual inline void display(void) const { std::cout << this->a << " "  << std::endl;}; // Pure virtual function
};

template <typename T>
class Derived_listener1 final : public Base<T>{
protected:
    T b;
public:
    explicit Derived_listener1(void): // explicit mark constructors to not implicitly convert types
        Derived_listener1{static_cast<T>(25),static_cast<T>(12)}{std::cout << "Derived_listener1 constructor no args called" << std::endl;};
    explicit Derived_listener1(T a_, T b_ = 1):
        Base<T>{a_}, b{b_}{
            // a = 4; b = 5;
            std::cout << "Derived_listener1 constructor with args called" << std::endl;
        };
    Derived_listener1(const Derived_listener1<T> &d): Base<T>{d}, b{d.b} { std::cout << "Derived_listener1 copy constructor called" << std::endl; }
    // virtual ~Derived_listener1() = default;
    virtual ~Derived_listener1() {std::cout << "Derived_listener1 destructor called" << std::endl;}
    virtual inline T getData(void) const override final {std::cout << "Get Derived_listener1 data: " << this->a <<std::endl; return this->b;}
    virtual inline void setData(T b_des) override final {b = b_des;};
    virtual inline void display(void) const override final { std::cout << this->a << " " << b << std::endl;}
    virtual inline void update(std::string message, Status status, T number) const 
    {
        std::cout << "Listener1:" << message << " " << status << " " << number << std::endl;
    }
};

template <typename T>
class Derived_listener2 final : public Base<T>{
protected:
    T b;
public:
    explicit Derived_listener2(void): // explicit mark constructors to not implicitly convert types
        Derived_listener2{static_cast<T>(25),static_cast<T>(12)}{std::cout << "Derived_listener2 constructor no args called" << std::endl;};
    explicit Derived_listener2(T a_, T b_ = 1):
        Base<T>{a_}, b{b_}{
            // a = 4; b = 5;
            std::cout << "Derived_listener2 constructor with args called" << std::endl;
        };
    Derived_listener2(const Derived_listener1<T> &d): Base<T>{d}, b{d.b} { std::cout << "Derived_listener2 copy constructor called" << std::endl; }
    // virtual ~Derived_listener1() = default;
    virtual ~Derived_listener2() {std::cout << "Derived_listener2 destructor called" << std::endl;}
    virtual inline T getData(void) const override final {std::cout << "Get Derived_listener2 data: " << this->a <<std::endl; return this->b;}
    virtual inline void setData(T b_des) override final {b = b_des;};
    virtual inline void display(void) const override final { std::cout << this->a << " " << b << std::endl;}
    virtual inline void update(std::string message, Status status, T number) const 
    {
        std::cout << "Listener2:" << message << " " << status << " " << number << std::endl;
    }
};

template<typename T>
class EventManager
{
    std::list<Base<T>*> listBase;
public:
    EventManager<T>() = default;
    void notify(std::string message, Status status, T number)
    {
        for (auto i : listBase)
        {
            i->update(message, status, number);
        }
    }
    void subcribe(Base<T>* base)
    {
        listBase.push_back(base);
    }
    void unsubcribe(Base<T>* base)
    {
        listBase.remove(base);
    }
};

template<typename T>
class EventCreator
{
    std::string message;
    Status status;
    T number;
public:
    EventManager<T> event_manager;
    EventCreator()
    {
        std::cout << "Construct event creator" << std::endl;
        message = "";
        status = Status::UNSAVED;
        number = 0;
    }
    void changeMessage(std::string message_)
    {
        message = message_;
        status = Status::CHANGE;
        number = 101;
        event_manager.notify(message, status, number);
    }
    void saveMessage()
    {
        message = "Save";
        status = Status::SAVED;
        number = 102;
        event_manager.notify(message, status, number);
    }
    void unsaveMessage()
    {
        message = "Unsave";
        status = Status::UNSAVED;
        number = 103;
        event_manager.notify(message, status, number);
    }
    ~EventCreator()
    {
        std::cout << "Destruct event creator" << std::endl;
    }
};


template <typename T>
void use(Base<T>* base) {
    base->display();
}
}

int main(int argc, char const *argv[])
{
    /*
    //Base class pointer
    PRINT_CMD("-------------USING BASE CLASS POINTER:---------------------");
    // Base *p = new Derived_listener1();
    PolySample::Base<int> *p = new PolySample::Derived_listener1<int>{20,24}; //Created Derived_listener1 object on the Heap
    int result = p->getData();
    // std::cout << "The result is " << result << std::endl;
    p->display();
    delete p; 
    
    // Base class reference
    PRINT_CMD("-------------USING BASE CLASS REFERENCE--------------------:");
    PolySample::Derived_listener1<int> deriv{25,12};
    PolySample::Base<int> &ref = deriv;
    ref.display();

    //Using with vector
    PRINT_CMD("---------------USING WITH VECTOR OF RAW POINTERS:--------------");
    std::vector<PolySample::Derived_listener1<int>*> Derived_listener1s { new PolySample::Derived_listener1<int>, new PolySample::Derived_listener1<int> };
    for (const auto item : Derived_listener1s) {
        use(item);
    }
    //TODO: Remember to delete the allocated memory to avoid memory leaks!
    for (auto item : Derived_listener1s) {
        delete item;
    }

    //Using with smart pointer
    PRINT_CMD("---------------USING WITH SMART POINTER:-------------------------");
    std::shared_ptr<PolySample::Base<int>> pSmart = std::make_shared<PolySample::Derived_listener1<int>>(deriv);
    pSmart->display(); 

    std::vector<std::shared_ptr<PolySample::Base<int>>> vecSmarts;
    vecSmarts.push_back(std::make_shared<PolySample::Derived_listener1<int>>(deriv));
    vecSmarts.push_back(std::make_shared<PolySample::Derived_listener1<int>>(deriv));
    vecSmarts.push_back(std::make_shared<PolySample::Derived_listener1<int>>(deriv));

    for(const auto &v: vecSmarts){
        // v->display();
        v->getData();
    }
    */

    // Make event creator
    PolySample::EventCreator<int> *evenCreator = new PolySample::EventCreator<int>();
    
    // Make two listeners
    PolySample::Base<int> *deriv1 = new PolySample::Derived_listener1<int>();
    PolySample::Base<int> *deriv2 = new PolySample::Derived_listener2<int>();
    
    // event manager add two subcribers
    evenCreator->event_manager.subcribe(deriv1);
    evenCreator->event_manager.subcribe(deriv2);

    // event creator change message
    evenCreator->changeMessage("Hi, I'm event creator");

    // event manager unsubcribe deriv2
    evenCreator->event_manager.unsubcribe(deriv2);

    // event creator save and unsaved message (some dummy activities that I wrote for fun)
    evenCreator->saveMessage();
    evenCreator->unsaveMessage();

    delete deriv1;
    delete deriv2;
    delete evenCreator;

    // Test explicit
    // PolySample::Base<int> obj;
    // obj = 10;
    // obj.getData();

    

    return 0;
}

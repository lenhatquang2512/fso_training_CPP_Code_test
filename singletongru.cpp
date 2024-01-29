#include <iostream>
#include <mutex>
using namespace std;

template <typename T>
class Base
{
private:
    // static mutex mMutex;
    T value;
    static Base* instance;
    Base(const T val) : value{val} {}

public:
    Base(Base &obj) = delete;
    void operator=(const Base &) = delete;

    static Base* GetInstance(const T &val);
    void SomeBusinessLogic()
    {
        cout << "Some Business Logic" << endl;
    }
    T getvalue() const
    {
        return value;
    }
    ~Base()
    {
        cout << "Destructor of Base" << endl;
    }
};

// template <typename T>
// mutex Base<T>::mMutex;

template <typename T>
Base<T>* Base<T>::instance = nullptr;

template <typename T>
Base<T>* Base<T>::GetInstance(const T &value)
{
    // lock_guard<mutex> lock(mMutex);

    if (instance == nullptr)
    {
        instance = new Base(value);
    }
    return instance;
}

template <typename T>
void ThreadFoo()
{
    Base<T>* singleton = Base<T>::GetInstance("Foo");
    cout << singleton->getvalue() << endl;
}

template <typename T>
void ThreadBar()
{
    Base<T>* singleton = Base<T>::GetInstance("Bar");
    cout << singleton->getvalue() << endl;
}

int main()
{
    ThreadFoo<string>();
    ThreadBar<string>();

    return 0;
}

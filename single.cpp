#include <iostream>
#include <string>
#include <mutex>
using namespace  std;
namespace Poly{
template <typename T>
class single2
{
private:
    /* data */
    static mutex mLocker;
    static single2 *instance;
    T a;
    single2(/* args */){ cout << "Singleton constructor" << endl;}
    single2(T a_):a{a_} { cout << "Parameter constructor" << endl;}
public:
    static single2 *getinstance(){
        mLocker.lock();
        if (instance == nullptr){
            instance = new single2;
        }
        mLocker.unlock();
        return instance;
    }
    
    static single2 *getinstance(T a_){
        mLocker.lock();
        if (instance == nullptr){
            instance = new single2<T>(a_);
        }
        mLocker.unlock();
        return instance;
    }
    
    ~single2(){
        cout << "Destructor singleton" << endl;
    }
};
template <typename T>
single2<T> *single2<T>::instance = nullptr;
template <typename T>
mutex single2<T>::mLocker; 
}

int main(){
    // single2 *single = single2::getinstance();
    Poly::single2<int> *single = Poly::single2<int>::getinstance(1);
    
    // cin.getline(str);
    // getline(cin, str);
}


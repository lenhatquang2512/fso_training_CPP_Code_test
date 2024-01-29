#include <iostream>

using namespace std;
// template <T class>
class Base
{
private:
    /* data */
    static Base *instance;
    Base(/* args */){cout << "Call constructor ";}

    int x;
public:
    static Base*getInstance(){
        if(instance == nullptr){
            instance = new Base();
        }
        return instance;
    }
    ~Base(){}
};
Base *Base::instance = nullptr;
int main(){
    Base *p = Base::getInstance();
}
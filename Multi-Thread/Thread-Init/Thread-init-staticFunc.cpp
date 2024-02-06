#include <iostream>
#include <thread>

using namespace std;

class Base{
public:
    static void run(int x){
        while (x-- > 0){
            cout << x << endl;
        }
    }
};

int main(){
    Base b;
    std::thread t(&Base::run, 10);
    t.join();
    return 0;
}
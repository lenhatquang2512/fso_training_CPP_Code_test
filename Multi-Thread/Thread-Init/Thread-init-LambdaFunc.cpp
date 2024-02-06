#include <iostream>
#include <thread>

using namespace std;

int main()
{
    auto fun = [](int x){
        while (x-- > 0){
            cout << x << endl;
        }
    };
    std::thread t(fun, 10);
    t.join();
    return 0;
}
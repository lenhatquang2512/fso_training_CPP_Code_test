#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void run(int count){
    while(count-- > 0){
        cout << count << endl;
    }
}    

int main(){
    std::thread t(run, 10);

    cout << "main()" << endl;
    t.detach();
    cout << "main() after" << endl;
    std::this_thread::sleep_for(chrono::seconds(5));
    return 0;
}
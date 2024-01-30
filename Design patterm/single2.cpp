#include <iostream>
#include <string>

using namespace  std;

class single2
{
private:
    /* data */
    static single2 *instance;
    single2(/* args */){ cout << "Singleton constructor" << endl;}
public:
    static single2 *getinstance(){
        if (instance == nullptr){
            instance = new single2;
        }
        else return instance;
    }
    ~single2(){
        cout << "Destructor singleton" << endl;
    }
};

int main(){
    single2 *single = single2::getinstance();
    string str {"Frank is so handsome"};
    size_t position = str.find("Quynh");
    if(position != string::npos){
        cout << "found";
    }
    else cout << "not found";
    
    // cin.getline(str);
    // getline(cin, str);
}

single2 *single2::instance = nullptr;

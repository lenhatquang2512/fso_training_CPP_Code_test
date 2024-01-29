#include <memory>
#include <iostream>


// class Singleton{
// private:
//     static Singleton* m_singleton; 
//     Singleton(){
//         std::cout<<"Create";
//     }
//     ~Singleton(){
//         std::cout<<"\nDestroy";
//     }
    
// public:

//     static Singleton* create_instance(){
//         if(m_singleton==nullptr){
//             m_singleton = new Singleton;
//         }
//         return m_singleton;
//     }
//     static void destroy(){
//         if(m_singleton!=nullptr){
//             delete m_singleton;
//             m_singleton=nullptr;
//         }
//     }
// };

// Singleton* Singleton::m_singleton = nullptr;
        
// int main(){
//     Singleton::create_instance();
//     Singleton::create_instance();
//     Singleton::create_instance();
//     Singleton::destroy();
//     Singleton::destroy();
//     Singleton::destroy();

//     return 0;
// }



class Singleton{
private:
    static Singleton* m_singleton;
    Singleton(){};
    
    ~Singleton()
    {
        std::cout << "Destructor" << std::endl;
    }
public:
    static Singleton* get_instance(){
        if(m_singleton==nullptr){
            m_singleton=new Singleton;
        }
        return m_singleton;
    }

    static void destroy()
    {
        delete m_singleton;
        m_singleton = nullptr;
    }

};

Singleton* Singleton::m_singleton = nullptr;

int main(){
    Singleton* ptr1=Singleton::get_instance();
    Singleton* ptr2=Singleton::get_instance();
    std::cout<<ptr1<<std::endl;
    std::cout<<ptr2<<std::endl;
    Singleton::destroy();

    return 0;
}
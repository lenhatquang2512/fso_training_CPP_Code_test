#include<iostream> 
using namespace std; 

class Base 
{ 
public: 
	void show() 
	{ 
		cout<<" In Base "; 
	} 
}; 

class Derived: public Base 
{ 
public: 
	int x; 
	void show() 
	{ 
		cout<<"In Derived "; 
	} 
	Derived() 
	{ 
		x = 10; 
	} 
}; 

int main(void) 
{ 
	Base *bp, b; 
	Derived d; 
	bp = &d; 
	bp->show(); 
	// cout << bp->x;	 
    
	return 0; 
} 

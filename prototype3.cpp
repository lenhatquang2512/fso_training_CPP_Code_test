#include <iostream>

using namespace std;

class Shape
{
private:
    /* data */
public:
    Shape(/* args */);
    virtual Shape* clone() =0;
    virtual void draw() = 0;
    virtual ~Shape();
};

Shape::Shape(/* args */)
{
}

Shape::~Shape()
{
}

class Rectangle : public Shape
{
private:
    double height;
    double width;
public:
    Rectangle (double h, double w): height{h}, width{w} {}
    Shape* clone(){
        return new Rectangle(*this);
    }
    void draw(){
        cout << "Draw Rectangle" << endl;
    }
    ~Rectangle ();
};


Rectangle ::~Rectangle ()
{
}

class  Circle : public Shape
{
private:
    double radius;
public:
     Circle(double r) : radius{r} {}
     Shape* clone(){
        return  new Circle(*this);
     }
     void draw(){
        cout << "draw circle" << endl;
     }
    ~ Circle(){}
};





int main(){
    Circle circleprototype{5.0};
    Rectangle rectangleprototype{10.0,6.0};
    Shape* shape1 ;
    Shape* shape2;
    shape1 = circleprototype.clone();
    shape2 = rectangleprototype.clone();
    shape1->draw();
    shape2->draw();
}
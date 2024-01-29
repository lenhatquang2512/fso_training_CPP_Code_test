/**
 * @file prototype.cpp
 * @author your name (you@domain.com)
 * @brief Geeksforgeeks
 * @version 0.1
 * @date 2024-01-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>

using namespace std;

class Shape
{
private:
    
public:
    Shape();
    virtual Shape* clone() const = 0; // Clone method for creating copies
    virtual void draw() const = 0; // Draw method for redering the shape.

    virtual ~Shape();
};

Shape::Shape(){}

Shape::~Shape(){}
/*
Now, we define concrete classes (classes that can be instantiated, meaning you can create objects (instances) of those classes) that inherit from our abstract base class Circle and Rectangle. These classes implement the clone() and draw() methods for their respective shapes.


*/

class Circle : public Shape
{
private:
    double radius;
public:
    Circle(double r) : radius{r} {};
    Shape* clone() const override {
        return new Circle(*this);
    }
    void draw() const override{
        cout << "Drawing a circle with radius" << radius << endl;

    }
    ~Circle();
};


Circle::~Circle(){}

class Rectangle : public Shape
{
private:
    double width;
    double height;
public:
    Rectangle(double w, double h) : width{w}, height{h} {}
    Shape* clone() const override {
        return new Rectangle(*this);
    }
    void draw() const override {
        cout << "Drawing a rectangle with width" << width << "and height" << height << endl;
    }
    ~Rectangle();
};

int main(){
    Circle circlePrototype(5.0);
    Rectangle rectanglePrototype(4.0,6.0);

    Shape* shape1 = circlePrototype.clone();
    Shape* shape2 = rectanglePrototype.clone();

    shape1->draw();
    shape2->draw();
}

Rectangle::~Rectangle()
{
}

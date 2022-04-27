#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

//#define M_PI 3.14159265358979323846264338327950288

class Point{

private:
    double x, y;

public:
    Point(){
        x = 0;
        y = 0;
    }
    Point(double a, double b){
        x = a;
        y = b;
    }

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    void setX(double X) {
        Point::x = X;
    }

    void setY(double Y) {
        Point::y = Y;
    }

    Point operator - (const Point& other) const {

        Point res;
        res.x = abs(this->x - other.x);
        res.y = abs(this->y - other.y);

        return res;

    }


};

class Shape {

protected:

    Point mFirst;
    Point mSecond;
    string mName;

public:
    Shape(){


        this->mFirst.setX(0);
        this->mFirst.setY(0);
        this->mSecond.setX(0);
        this->mSecond.setY(0);
    }
    Shape(Point p1, Point p2){


        this->mFirst.setX(p1.getX());
        this->mFirst.setY(p1.getY());
        this->mSecond.setX(p2.getX());
        this->mSecond.setY(p2.getY());

    }

    Point getFirst() const {
        return mFirst;
    }

    Point getSecond() const {
        return mSecond;
    }

    string getName() const {
        return mName;
    }

    void setFirst(const Point first) {
        Shape::mFirst = first;
    }

    void setSecond(const Point second) {
        Shape::mSecond = second;
    }

    void setName(const string name) {
        Shape::mName = name;
    }
    virtual double getPerimeter() const = 0;
    virtual double getArea() const = 0;


};

class Quadrilateral : public Shape{

public:

    Quadrilateral(){

        this->mFirst.setX(0);
        this->mFirst.setY(0);
        this->mSecond.setX(0);
        this->mSecond.setY(0);
        this->mName = "Unknown";

    }
    Quadrilateral(Point p1, Point p2, string name)
    {

        this->mFirst.setX(p1.getX());
        this->mFirst.setY(p1.getY());
        this->mSecond.setX(p2.getX());
        this->mSecond.setY(p2.getY());
        this->mName = name;
    }
    double getLength()const {

        Point t;
        t=this->mFirst-this->mSecond;
        return (t.getX());

    }
    double getWidth() const {

        Point t;
        t=this->mFirst-this->mSecond;
        return (t.getY());
    }

    double getPerimeter()const{

        return (2* this->getLength() + 2*this->getWidth());

    }
    double getArea()const{
        return (this->getLength() * this->getWidth());

    }



};

class Circle : public Shape{

private:
    double mRadius;

public:
    Circle(){
        this->mFirst.setX(0);
        this->mFirst.setY(0);
        this->mSecond.setX(0);
        this->mSecond.setY(0);
        this->mName = "Unknown";
        this->mRadius = 0;

    }
    Circle(Point circleCenter, double radius){


        this->mFirst.setX(circleCenter.getX());
        this->mFirst.setY(circleCenter.getY());
        this->mSecond.setX(0);
        this->mSecond.setY(0);
        this->mName = "cerc";
        this->mRadius = radius;

    }

    double getPerimeter()const{

        return (this->mRadius*2*M_PI);


    }
    double getArea()const{
        return (this->mRadius*this->mRadius*M_PI);
    }


    void setRadius(double r) {
        this->mRadius = r;
    }

    double getRadius() const {
        return this->mRadius;
    }

};

int main() {

    int n;
    double minim, maxim;

    cin>>n>>minim>>maxim;
    if(n<1 || n > 500)
    {
        cout<<"Valoare de intrare invalida";
        return 0;
    }
    if(minim>maxim){
        cout<<"Valoare de intrare invalida";
        return 0;
    }
    vector <Shape*> v;
    for(int i=0; i < n; i++)
    {
        string name;
        cin>>name;
        Point a, b;
        if(name=="cerc")
        {   double x, y;
            cin>>x>>y;
            if(x<-1000 || x > 1000 || y <-1000 ||y > 1000)
            {
                cout<<"Valoare de intrare invalida";
                return 0;
            }
            a.setX(x);
            a.setY(y);
            cin>>x;
            if(x <= 0 || x > 1000)
            {
                cout<<"Valoare de intrare invalida";
                return 0;
            }
            v.push_back(new Circle (a, x));
        }
        else
        {
            double n1, n2, n3, n4;
            cin>>n1>>n2>>n3>>n4;
            if(n1<-1000 || n1 > 1000 || n2 <-1000 ||n2 > 1000 || n3 < -1000|| n3 > 1000 || n4 <-1000 || n4 > 1000)
            {
                cout<<"Valoare de intrare invalida";
                return 0;
            }
            a.setX(n1);
            a.setY(n2);
            b.setX(n3);
            b.setY(n4);
            v.push_back(new Quadrilateral (a,b, name));
        }
    }
    for(int i = 0; i < n - 1; i++){
        for(int j = i; j < n; j++)
        {
            if(v.at(i)->getArea() == v.at(j)->getArea())
            {
                if(v.at(i)->getPerimeter() > v.at(j)->getPerimeter())
                {
                    swap(v.at(i), v.at(j));
                }
            }
            else if (v.at(i)->getArea() > v.at(j)->getArea())
                swap(v.at(i), v.at(j));
        }
    }
    for(int i = 0; i < n; i++)
    {
        cout<<fixed<<setprecision(6);
        cout<<v.at(i)->getName()<<" "<<v.at(i)->getArea()<<" "<<v.at(i)->getPerimeter()<<"\n";
    }


    return 0;
}

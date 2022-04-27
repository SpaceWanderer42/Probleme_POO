#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

#define M_PI 3.14159265358979323846264338327950288f

class Shape
{
protected:
    string mShape;
    float mArea;
public:
    virtual void print() = 0;
    virtual void calculateArea() = 0;
    float getArea()
    {
        return mArea;
    }
};

class Square : public Shape
{
    float mLength;
public:
    Square(float length)
    {
        mLength = length;
        mShape = "patrat";
    }

    void print()
    {
        cout << fixed << showpoint;
        cout << setprecision(2);
        cout << mShape << ' ' << mLength << endl;
    }

    void calculateArea()
    {
        mArea = mLength * mLength;
    }

    Square(){
        mLength = 0;
        mShape = "nedefinit";
    }
};

class Rectangle : public Shape
{
    float mLength, mWidth;
public:
    Rectangle(float length, float width)
    {
        mLength = length;
        mWidth = width;
        mShape = "dreptunghi";
    }
    void print()
    {
        cout << fixed << showpoint;
        cout << setprecision(2);
        cout << mShape << ' ' << setprecision(2) << mLength << ' ' << mWidth << endl;
    }

    void calculateArea()
    {
        mArea = mLength * mWidth;
    }

    Rectangle(){

        mLength = 0;
        mWidth = 0;
        mShape = "nedefinit";
    }
};

class Circle : public Shape
{
    float mRadius;
public:
    Circle(float radius)
    {
        mRadius = radius;
        mShape = "cerc";
    }
    void print()
    {
        cout << fixed << showpoint;
        cout << setprecision(2);
        cout << mShape << ' ' << mRadius << endl;
    }

    void calculateArea()
    {
        mArea = M_PI * mRadius * mRadius;
    }

    Circle(){
        mRadius = 0;
        mShape = "nedefinit";
    }
};

int main()
{
    typedef unsigned short ushort;
    ushort n;
    vector<Shape*> shapes;

    cin >> n;
    string shapeData;
    getline(cin, shapeData);

    for (ushort i = 0; i < n; ++i)
    {
        getline(cin, shapeData);

        char *p = strtok(const_cast<char*>(shapeData.c_str()), " ");
        if (strstr(p, "patrat"))
        {
            float length = (float)atof(strtok(0, " "));
            shapes.emplace_back(new Square(length));
        }
        if (strstr(p, "dreptunghi"))
        {
            float length = (float)atof(strtok(0, " "));
            float width = (float)atof(strtok(0, " "));
            shapes.push_back(new Rectangle(length, width));
        }
        if (strstr(p, "cerc"))
        {
            float radius = (float)atof(strtok(0, " "));
            shapes.push_back(new Circle(radius));
        }
    }

    for (ushort i = 0; i < n; ++i)
    {
        shapes.at(i)->calculateArea();
    }

    sort(shapes.begin(), shapes.end(), [](Shape* lhs, Shape* rhs)
    {
        return lhs->getArea() > rhs->getArea();
    });

    for (ushort i = 0; i < n; ++i)
    {
        shapes.at(i)->print();
    }

    return 0;
}

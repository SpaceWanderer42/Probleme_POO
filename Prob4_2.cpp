#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#include <iomanip>
 
using namespace std;
 
class Point
{
    friend class Point2D;
    friend class Point3D;
    friend class Point4D;
protected:
    vector<double> mCoordinates;
    double mDistance;
public:
    virtual void print() = 0;
    virtual void calculateDistance() = 0;
    virtual Point* multiply(Point*) = 0;
 
    double getDistance()
    {
        return mDistance;
    }
};
 
class Point2D : public Point
{
public:
    Point2D()
    {
        mCoordinates.push_back(0);
        mCoordinates.push_back(0);
        mDistance = 0;
    }
 
    Point2D(double val1, double val2)
    {
        mCoordinates.push_back(val1);
        mCoordinates.push_back(val2);
        calculateDistance();
    }
   
    void print()
    {
        cout << setprecision(3) << fixed;
        cout << mCoordinates.at(0) << (mCoordinates.at(1) < 0 ? "" : "+") << mCoordinates.at(1) << 'i';
        cout << " -> ";
        cout << mDistance;
        cout << endl;
    }
    
     
    void calculateDistance() override {
        
        mDistance = sqrt(mCoordinates[0] * mCoordinates[0] + mCoordinates[1] * mCoordinates[1]);
        
    }
 
   // void calculateDistance()
    //{
      //  for (size_t i = 0; i < mCoordinates.size(); ++i)
    //    {
      //      mDistance += mCoordinates.at(i) * mCoordinates.at(i);
    //    }
      //  mDistance = sqrt(mDistance);
    //}
 
    //Point2D* multiply(Point * other) override
    //{
    //    return new Point2D(
      //          mCoordinates.at(0) * other->mCoordinates.at(0) - mCoordinates.at(1) * other->mCoordinates.at(1),
    //            mCoordinates.at(0) * other->mCoordinates.at(1) + mCoordinates.at(1) * other->mCoordinates.at(0));
    //}
    
     Point *multiply (Point *other) {
         
        double a1 = mCoordinates[0];
        double b1 = mCoordinates[1];
        double a2, b2;
        
        if (other->mCoordinates.size() >= 1) {
            
            a2 = other->mCoordinates[0];
            
        } else a2 = 0;
        
        if (other->mCoordinates.size() >= 2) {
            
            b2 = other->mCoordinates[1];
            
        } else b2 = 0;
        
        double a3 = a1 * a2 - b1 * b2;
        double b3 = a1 * b2 + a2 * b1;
        
        Point2D *result = new Point2D(a3, b3);
        return result;
    }
    
};
 
class Point3D : public Point
{
public:
    Point3D()
    {
        mCoordinates.push_back(0);
        mCoordinates.push_back(0);
        mCoordinates.push_back(0);
        mDistance = 0;
    }
 
    Point3D(double val1, double val2, double val3)
    {
        mCoordinates.push_back(val1);
        mCoordinates.push_back(val2);
        mCoordinates.push_back(val3);
        calculateDistance();
    }
    void print()
    {
        cout << setprecision(3) << fixed;
        cout << mCoordinates.at(0) << (mCoordinates.at(1) < 0 ? "" : "+") << mCoordinates.at(1) << 'i' << (mCoordinates.at(2) < 0 ? "" : "+") << mCoordinates.at(2) << 'j';
        cout << " -> ";
        cout << mDistance;
        cout << endl;
    }
 
    //void calculateDistance()
    //{
        //for (size_t i = 0; i < mCoordinates.size(); ++i)
        //{
           // mDistance += pow(mCoordinates.at(i), 3);
        //}
        //mDistance = cbrt(mDistance);
    //}
    
    void calculateDistance() {
        
        double n = pow (mCoordinates[0], 3) + pow(mCoordinates[1], 3) + pow(mCoordinates[2], 3);
        
        mDistance = std::cbrt(n);
        
    }
 
    //Point3D* multiply(Point * other) override
    //{
        //bool condition = other->mCoordinates.size() < mCoordinates.size();
        //return new Point3D(
                //mCoordinates.at(0) * other->mCoordinates.at(0) - mCoordinates.at(2) * (condition ? 0 : other->mCoordinates.at(2)) - mCoordinates.at(1) * other->mCoordinates.at(1),
                //mCoordinates.at(1) * other->mCoordinates.at(0) + mCoordinates.at(0) * other->mCoordinates.at(1),
                //mCoordinates.at(2) * other->mCoordinates.at(0) + mCoordinates.at(0) * (condition ? 0 : other->mCoordinates.at(2)));
    //}
    
    Point *multiply(Point *other) {
        
        double a1 = mCoordinates[0];
        double b1 = mCoordinates[1];
        double c1 = mCoordinates[2];
        double a2, b2, c2;
        
        if (other->mCoordinates.size() >= 1) {
            
            a2 = other->mCoordinates[0];
            
        } else a2 = 0;
        
        if (other->mCoordinates.size() >= 2) {
            
            b2 = other->mCoordinates[1];
            
        } else b2 = 0;
        
        if (other->mCoordinates.size() >= 3) {
            
            c2 = other->mCoordinates[2];
            
        } else c2 = 0;
        
        double a3 = a1 * a2 - b1 * b2 - c1 * c2;
        double b3 = a1 * b2 + a2 * b1;
        double c3 = a1 * c2 + a2 * c1;
        Point3D *result = new Point3D(a3, b3, c3);
        return result;
    }
    
};
 
class Point4D : public Point
{
public:
    Point4D()
    {
        mCoordinates.push_back(0);
        mCoordinates.push_back(0);
        mCoordinates.push_back(0);
        mCoordinates.push_back(0);
        mDistance = 0;
    }
 
    Point4D(double val1, double val2, double val3, double val4)
    {
        mCoordinates.push_back(val1);
        mCoordinates.push_back(val2);
        mCoordinates.push_back(val3);
        mCoordinates.push_back(val4);
        calculateDistance();
    }
    void print()
    {
        cout << setprecision(3) << fixed;
        cout << mCoordinates.at(0) << (mCoordinates.at(1) < 0 ? "" : "+") << mCoordinates.at(1) << 'i' << (mCoordinates.at(2) < 0 ? "" : "+") << mCoordinates.at(2) << 'j' << (mCoordinates.at(3) < 0 ? "" : "+") << mCoordinates.at(3) << 'k';
        cout << " -> ";
        cout << mDistance;
        cout << endl;
    }
 
    // void calculateDistance()
    // {
    //     for (size_t i = 0; i < mCoordinates.size(); ++i)
    //     {
    //         mDistance += pow(mCoordinates.at(i), 4);
    //     }
    //     mDistance = pow(mDistance, 1. / 4.);
    // }
    
    void calculateDistance() {
        
        double n = pow(mCoordinates[0], 4) + pow(mCoordinates[1], 4) + pow(mCoordinates[2], 4) + pow(mCoordinates[3], 4);
        
        mDistance = pow(n, 1 / 4.);
    }
    
 
    //Point4D* multiply(Point * other) override
    //{
        //size_t diff = mCoordinates.size() - other->mCoordinates.size();
        //return new Point4D(
               // mCoordinates.at(0) * other->mCoordinates.at(0) - mCoordinates.at(1) * other->mCoordinates.at(1) - (diff < 2 ? mCoordinates.at(2) * other->mCoordinates.at(2) : 0) - (diff < 1 ? mCoordinates.at(3) * other->mCoordinates.at(3) : 0),
                //(mCoordinates.at(0) * other->mCoordinates.at(1)) + mCoordinates.at(1) * other->mCoordinates.at(0),
                //(diff < 2 ? mCoordinates.at(0) * other->mCoordinates.at(2) : 0) + mCoordinates.at(2) * other->mCoordinates.at(0),
                //(diff < 1 ? mCoordinates.at(0) * other->mCoordinates.at(3) : 0) + mCoordinates.at(3) * other->mCoordinates.at(0));
    //}
    
    Point *multiply(Point *other) {
        
        double a1 = mCoordinates[0];
        double b1 = mCoordinates[1];
        double c1 = mCoordinates[2];
        double d1 = mCoordinates[3];
        double a2, b2, c2, d2;
        
        if (other->mCoordinates.size() >= 1) {
            
            a2 = other->mCoordinates[0];
            
        } else a2 = 0;
        
        if (other->mCoordinates.size() >= 2) {
            
            b2 = other->mCoordinates[1];
            
        } else b2 = 0;
        
        if (other->mCoordinates.size() >= 3) {
            
            c2 = other->mCoordinates[2];
            
        } else c2 = 0;
        
        if (other->mCoordinates.size() >= 4) {
            
            d2 = other->mCoordinates[2];
            
        } else d2 = 0;
        
        double a3 = a1 * a2 - b1 * b2 - c1 * c2 - d1 * d2;
        double b3 = a1 * b2 + a2 * b1;
        double c3 = a1 * c2 + a2 * c1;
        double d3 = a1 * d2 + d1 * a2;
        Point4D *result = new Point4D(a3, b3, c3, d3);
        return result;
    }
    
};
 
int main()
{
 
    string numbers;
    vector<Point*> points;
    while (1)
    {
 
        getline(cin, numbers);
 
        char * re;
        char *p = strtok_r(const_cast<char*>(numbers.c_str()), " ", &re);
        while (p)
        {
            vector<double> values;
            char * re2;
            char * p2 = strtok_r(p, ";", &re2);
            while (p2)
            {
                values.push_back(atof(p2));
                p2 = strtok_r(0, ";", &re2);
            }
            switch (values.size())
            {
                case 2:
                {
                    points.push_back(new Point2D(values.at(0), values.at(1)));
                    break;
                }
 
                case 3:
                {
                    points.push_back(new Point3D(values.at(0), values.at(1), values.at(2)));
                    break;
                }
 
                case 4:
                {
                    points.push_back(new Point4D(values.at(0), values.at(1), values.at(2), values.at(3)));
                    break;
                }
 
                default: break;
            }
 
            p = strtok_r(0, " ", &re);
        }
 
        if (cin.eof())break;
    }
 
    vector<Point*> newPoints;
    size_t size = points.size();
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
        {
            if (i != j)
            {
                newPoints.push_back(points.at(i)->multiply(points.at(j)));
            }
        }
    }
 
    size = newPoints.size();
    for (size_t i = 0; i < size; ++i)
    {
        newPoints.at(i)->calculateDistance();
    }
 
    sort(newPoints.begin(), newPoints.end(), [](Point* lhs, Point* rhs)
    {
        return lhs->getDistance() > rhs->getDistance();
    });
 
    newPoints.at(0)->print();
 
return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <climits>

using namespace std;


class Point
{
    double x, y, z;
    bool containsAzimuth = true;

public:
    Point()
    {
        x = y = z = 0.0;
    }
    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
        z = 0.0;
        containsAzimuth = false;
    }
    Point(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double radToDeg(double val)
    {
       val=val*180/M_PI;
        
        if(val < 0)
        {
            val = val + 360;
            return val;
            
        }
        else return val ;
        
    }

    double getX()
    {
        return x;
    }

    double getY()
    {
        return y;
    }

    double getZ()
    {
        return z;
    }

    double getRadius()
    {
        return sqrt(x * x + y * y + z * z);
    }

    double getPhi()
    {
        return radToDeg(atan2(y, x));
    }

    double getTheta()
    {
                if (containsAzimuth)
            return radToDeg((atan2(sqrt(x * x + y * y), z)));
        return 0;

    }
};

int main()
{
    vector<Point> v;
    double x, y, z = INT_MIN, prev_z = INT_MIN;
    int i=scanf("%lf;%lf;%lf;",&x,&y,&z);
    while(i!=EOF){
         if(i==2){
         v.push_back(Point(x,y));
        //printf("%.0lf:%.0lf",x,y);
         }
         if(i==3){
         v.push_back(Point(x,y,z));
         //cout<<x<<":"<<y<<":"<<z<<endl;
         }
          i=scanf("%lf;%lf;%lf;",&x,&y,&z);
     }
   

    for (auto it = v.rbegin(); it != v.rend(); ++it)
    {
        std::cout << std::fixed;
        std::cout << std::setprecision(3);
        cout << "(r=" << it->getRadius() << "; phi=" << it->getPhi() << "";
        double th = it->getTheta();
        if (th!=0) cout << "; th=" << th << ")";
        else cout << ")";
        cout << endl;
    }
    //cin.ignore();
    //cin.get();
    
    return 0;
}

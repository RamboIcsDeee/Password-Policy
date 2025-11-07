#include<iostream>
#include<vector>
#include<cstdio>
#include<cmath>
#include<sstream>
#include<string>
#include<algorithm>

using namespace std;

class Point
{
private:
    double x;
    double y;
public:
    Point()
    {
        x = 0;
        y = 0;
    }
    Point(double arg_x, double arg_y)
    {
        x = arg_x;
        y = arg_y;
    }

    double getX() const
    {
        return x;
    }
    double getY() const
    {
        return y;
    }

    void setX(double arg_x)
    {
        x = arg_x;
    }
    void setY(double arg_y)
    {
        y = arg_y;
    }

    Point operator - (const Point& arg_point) const
    {
        Point rezultat;

        rezultat.x = abs(x - arg_point.x);
        rezultat.y = abs(y - arg_point.y);

        return rezultat;
    }
};

class Shape
{
protected:
    Point mFirst;
    Point mSecond;
    string mName;
public:
    Shape()
    {
        mFirst.setX(0);
        mFirst.setY(0);
        mSecond.setX(0);
        mSecond.setY(0);

    }
    Shape(Point arg_mFirst, Point arg_mSecond)
    {
        mFirst = arg_mFirst;
        mSecond = arg_mSecond;
    }

    Point getFirst() const
    {
        return mFirst;
    }
    Point getSecond() const
    {
        return mSecond;
    }
    string getName() const
    {
        return mName;
    }

    void setFirst(Point arg_mFirst)
    {
        mFirst = arg_mFirst;
    }
    void setSecond(Point arg_mSecond)
    {
        mSecond = arg_mSecond;
    }
    void setName(string arg_mName)
    {
        mName = arg_mName;
    }

    virtual double getPerimeter() const = 0;
    virtual double getArea() const = 0;
    virtual void print() const = 0;
};

class Quadrilateral :public Shape
{
public:
    Quadrilateral()
    {
        mFirst.setX(0);
        mFirst.setY(0);
        mSecond.setX(0);
        mSecond.setY(0);
        mName = "Unknown";
    }
    Quadrilateral(Point arg_mFirst, Point arg_mSecond, string arg_mName)
    {
        mFirst = arg_mFirst;
        mSecond = arg_mSecond;
        mName = arg_mName;
    }

    double getLength() const
    {
        return abs(mFirst.getX() - mSecond.getX());
    }
    double getWidth() const
    {
        return abs(mFirst.getY() - mSecond.getY());
    }

    double getPerimeter() const
    {
        return 2 * (getLength() + getWidth());
    }
    double getArea() const
    {
        return getLength() * getWidth();
    }
    virtual void print() const
    {
        cout << mName;
        printf(" %.6lf %.6lf\n", getArea(), getPerimeter());
    }
};

class Circle : public Shape
{
private:
    double mRadius;
public:
    Circle()
    {
        mFirst.setX(0);
        mFirst.setY(0);
        mSecond.setX(0);
        mSecond.setY(0);
        mRadius = 0;
        mName = "Unknown";
    }
    Circle(Point arg_point, double arg_mRadius)
    {
        mFirst = arg_point;
        mRadius = arg_mRadius;
        mName = "cerc";
    }

    double getPerimeter() const
    {
        return 2 * M_PI * mRadius;
    }
    double getArea() const
    {
        return  M_PI * mRadius * mRadius;
    }

    void setRadius(double arg_mRadius)
    {
        mRadius = arg_mRadius;
    }
    double getRadius() const
    {
        return mRadius;
    }
    virtual void print() const
    {
        cout << mName;
        printf(" %.6lf %.6lf\n", getArea(), getPerimeter());
    }
};

bool comparat(Shape* s1, Shape* s2)
{
    if (s1->getArea() == s2->getArea())
    {
        return s1->getPerimeter() < s2->getPerimeter();
    }
    else return s1->getArea() < s2->getArea();
}
int main() {

    int n;
    double min, max;
    bool crash = false;
    cin >> n;
    cin >> min >> max;
    if (n < 0)
    {
        cout << "Valoare de intrare invalida" << endl;
        return 0;
    }
    if (min > max)
    {
        cout << "Valoare de intrare invalida" << endl;
        return 0;
    }

    vector<Shape*> figuri;

    for (int i = 0; i < n; i++)
    {
        string figura;
        cin >> figura;

        if (figura == "cerc")
        {
            double x, y, r;
            cin >> x >> y >> r;

            if (-1000 <= x <= 1000 && -1000 <= y <= 1000 && 0<=r<=1000)
            {
                figuri.push_back(new Circle(Point(x, y), r));
            }
            else
            {
                cout << "Valoare de intrare invalida" << endl;
                crash = true;
                break;

            }
        }
        else if (figura == "patrat" || figura == "dreptunghi")
        {
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;

            if (abs(x1)<=1000 && abs(x2)<=1000 && abs(y1)<=1000 && abs(y2)<=1000)
            {
                figuri.push_back(new Quadrilateral(Point(x1, y1), Point(x2, y2), figura));
            }
            else
            {
                cout << "Valoare de intrare invalida" << endl;
                crash = true;
                break;
            }
        }
    }

    if (crash == false)
    {
        sort(figuri.begin(), figuri.end(), comparat);

        for (Shape* figura : figuri)
        {
            figura->print();
        }
    }
}

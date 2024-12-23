#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};


class FunctionAnalyzer {
private:
    // Function: f(x, y) = x^3 - 3xy^2
    static double f(const Point& p) {
        return p.x * p.x * p.x - 3 * p.x * p.y * p.y;
    }
   
    static double dF_dx(const Point& p) {
        return 3 * p.x * p.x - 3 * p.y * p.y;
    }
   
    static double dF_dy(const Point& p) {
        return -6 * p.x * p.y;
    }
   
    static double d2F_dx2(const Point& p) {
        return 6 * p.x;
    }
   
    static double d2F_dy2(const Point& p) {
        return -6 * p.x;
    }
   
    static double d2F_dxdy(const Point& p) {
        return -6 * p.y;
    }


public:
    static bool isSaddlePoint(const Point& p, double epsilon = 1e-10) {
        if (abs(dF_dx(p)) < epsilon && abs(dF_dy(p)) < epsilon) {
            if (abs(p.x) < epsilon && abs(p.y) < epsilon) {
                return true;
            }
           
            double detHessian = d2F_dx2(p) * d2F_dy2(p) - d2F_dxdy(p) * d2F_dxdy(p);
            return detHessian < 0;
        }
        return false;
    }


    static void analyzeSaddlePoints(const vector<Point>& points) {
        cout << "\nAnalyzing points for function f(x,y) = x^3 - 3xy^2:\n";
        cout << "----------------------------------------\n";
       
        for (size_t i = 0; i < points.size(); i++) {
            const Point& p = points[i];
            cout << "Point " << i + 1 << " (" << p.x << ", " << p.y << "):\n";
            cout << "Function value: " << f(p) << "\n";
            cout << "Partial dx: " << dF_dx(p) << "\n";
            cout << "Partial dy: " << dF_dy(p) << "\n";
           
            if (isSaddlePoint(p)) {
                cout << "Result: This is a saddle point!\n";
            } else {
                cout << "Result: Not a saddle point.\n";
            }
            cout << "----------------------------------------\n";
        }
    }
};


Point inputPoint(int pointNum) {
    Point p;
    cout << "Enter point " << pointNum << " (x y): ";
    cin >> p.x >> p.y;
    return p;
}


int main() {
    cout << "Saddle Point Analyzer\n";
    cout << "====================\n";
   
    vector<Point> points;
    int numPoints;
   
    cout << "How many points do you want to analyze? ";
    cin >> numPoints;
   
    while (numPoints < 1) {
        cout << "Please enter a positive number: ";
        cin >> numPoints;
    }
    for (int i = 0; i < numPoints; i++) {
        points.push_back(inputPoint(i + 1));
    }
   
    FunctionAnalyzer::analyzeSaddlePoints(points);
   
    return 0;
}

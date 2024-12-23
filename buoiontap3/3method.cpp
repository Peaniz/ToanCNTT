#include <iostream>
#include <cmath>
using namespace std;


const int N = 10000;
const double tolerance = 1e-7;
const double e = 2.71828182846;


double x, x1, d, gama, anpha;


void init() {
    x = -1;
    gama = 0.01;
    anpha = 0.5;
    d = 0;
}


double f(double x) {
    return pow(exp(4 * x) - 2 * pow(x, 2) - 5 * pow(x, 3), 2) + 2 * pow(x, 4);
}


double df(double x) {
    return 2 * (4 * exp(4 * x) - 4 * x - 15 * pow(x, 2))
           * (exp(4 * x) - 2 * pow(x, 2) - 5 * pow(x, 3))
           + 8 * pow(x, 3);
}


double ddf(double x) {
    return 2 * pow(4 * exp(4 * x) - 4 * x - 15 * pow(x, 2), 2)
           + 2 * (exp(4 * x) - 2 * pow(x, 2) - 5 * pow(x, 3))
              * (16 * exp(4 * x) - 4 - 30 * x)
           + 24 * pow(x, 2);
}


void solveGradientDescent() {
    init();
    int i = 0;
    double grapd;
    while (i < N) {
        grapd = df(x);
        x1 = x - gama * grapd;
        d = x1 - x;
        x = x1;
        if (fabs(grapd) < tolerance) {
            break;
        }
        i++;
    }
    cout << "Gradient Descent:              x = " << x << ", f(x) = " << f(x) << endl;
}


void solveGradientDescentMomentTum() {
    init();
    int i = 0;
    double grapd;
    while (i < N) {
        grapd = df(x);
        x1 = x - gama * grapd + anpha * d;
        d = x1 - x;
        x = x1;
        if (fabs(grapd) < tolerance) {
            break;
        }
        i++;
    }
    cout << "Gradient Descent (Moment Tum): x = " << x << ", f(x) = " << f(x) << endl;
}


void solveNewton() {
    init();
    int i = 0;
    double grapd, grapdd;
    while (i < N) {
        grapd = df(x);
        grapdd = ddf(x);
        if (grapdd == 0) {
            break;
        }
        x1 = x - grapd / grapdd;
        if (fabs(grapdd) < tolerance || fabs(grapd) < tolerance)
            break;
        d = x1 - x;
        x = x1;
        i++;
    }
    cout << "Newton Raphson:                x = " << x << ", f(x) = " << f(x) << endl;


}


int main() {
    solveGradientDescent();
    solveGradientDescentMomentTum();
    solveNewton();
}



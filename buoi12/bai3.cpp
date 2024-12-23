#include<iostream>
#include <iomanip>
using namespace std;

const double eps = 1e-5;
const int MAX_N = 100;

double f(double x1, double x2)
{
    return 6 * x1 * x1 + 4 * x1 * x2 + 3 * x2 * x2;
}

double h(double x1, double x2)
{
    return x1 + x2 - 5;
}

double compute_x1(double r, double lambda) {
    double numerator = -90 * r * r + 9 * r * lambda - 6 * lambda + 60 * r;
    double denominator = (14 - 5 * r) * (12 + 2 * r);
    return numerator / denominator;
}

double compute_x2(double r, double lambda) {
    return (20 * r - 2 * lambda) / (14 - 5 * r);
}

void augmentedLagrange(double &x1, double &x2, double lambda = 0, double r = 1)
{
    cout << setprecision(5) << fixed
         << setw(5) << "No"
         << setw(10) << "Lambda"
         << setw(10) << "rk"
         << setw(10) << "x1"
         << setw(10) << "x2"
         << setw(10) << "h(x)" << endl;

    double hValue = h(x1, x2);
    for (int i = 0; i < MAX_N; i++)
    {
    	
    	x1 = compute_x1(r, lambda);
		x2 = compute_x2(r, lambda);
		hValue = h(x1, x2);
        cout << setprecision(5) << fixed
             << setw(5) << i + 1
             << setw(10) << lambda
             << setw(10) << r
             << setw(10) << x1
             << setw(10) << x2
             << setw(10) << hValue << endl;

        if (abs(hValue) < eps)
        {
            break;
        }

        lambda += 2 * r * hValue;
    }
}

int main()
{
    double lambda = 0, r = 1;
    double x1 = compute_x1(r, lambda);
	double x2 = compute_x2(r, lambda);

    augmentedLagrange(x1, x2, lambda, r);

    cout << "Solution: " << endl;
    cout << "x1 = " << x1 << endl;
    cout << "x2 = " << x2 << endl;
    cout << "Minimize f(x) = " << f(x1, x2) << endl;

    return 0;
}

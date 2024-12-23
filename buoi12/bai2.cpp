#include <iostream>
#include <cmath>
#include <iomanip>


using namespace std;


// Constants for optimization
constexpr int MAX_ITERATIONS = 100;  // Reduced from 10000
constexpr double EPSILON = 1e-8;     // Increased precision
constexpr double LEARNING_RATE = 0.5; // Increased from 0.1 for faster convergence


class Matrix3x3 {
private:
    double data[3][6];  // Extended matrix for inverse calculation
   
public:
    // Initialize matrix with given values
    void set(const double values[3][3]) {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                data[i][j] = values[i][j];
            }
            // Set identity matrix in the right half
            for(int j = 3; j < 6; j++) {
                data[i][j] = (j - 3 == i) ? 1.0 : 0.0;
            }
        }
    }
   
    void inverse(double result[3][3]) {
        // Gauss-Jordan elimination with pivoting
        for(int i = 0; i < 3; i++) {
            // Find pivot
            int pivot = i;
            for(int j = i + 1; j < 3; j++) {
                if(abs(data[j][i]) > abs(data[pivot][i])) {
                    pivot = j;
                }
            }
           
            // Swap rows if necessary
            if(pivot != i) {
                for(int j = 0; j < 6; j++) {
                    std::swap(data[i][j], data[pivot][j]);
                }
            }
           
            // Scale row
            double scale = data[i][i];
            if(abs(scale) < EPSILON) continue;
           
            for(int j = 0; j < 6; j++) {
                data[i][j] /= scale;
            }
           
            // Eliminate column
            for(int j = 0; j < 3; j++) {
                if(j != i) {
                    double factor = data[j][i];
                    for(int k = 0; k < 6; k++) {
                        data[j][k] -= factor * data[i][k];
                    }
                }
            }
        }
       
        // Extract inverse
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                result[i][j] = data[i][j + 3];
            }
        }
    }
};


// Objective functions
struct Functions {
    static double f(double x1, double x2) {
        return 2*x1 + x2 + 10;
    }
   
    static double g(double x1, double x2) {
        return x1*x1 + 2*x2*x2 - 3;
    }
   
    // Lagrangian derivatives
    static double dL_dx1(double x1, double x2, double lambda) {
        return 2 - 2 * lambda * x1;
    }
   
    static double dL_dx2(double x1, double x2, double lambda) {
        return 1 - 4 * lambda * x2;
    }
   
    static double dL_dlambda(double x1, double x2, double lambda) {
        return 3 - x1*x1 - 2*x2*x2;
    }
};


// Newton-Raphson optimization
class NewtonOptimizer {
private:
    struct State {
        double x1, x2, lambda;
        State(double x1, double x2, double lambda) : x1(x1), x2(x2), lambda(lambda) {}
    };
   
    static bool hasConverged(const State& s) {
        double F1 = Functions::dL_dx1(s.x1, s.x2, s.lambda);
        double F2 = Functions::dL_dx2(s.x1, s.x2, s.lambda);
        double FL = Functions::dL_dlambda(s.x1, s.x2, s.lambda);
       
        return abs(F1) < EPSILON && abs(F2) < EPSILON &&
               abs(FL) < EPSILON && abs(Functions::g(s.x1, s.x2)) < EPSILON;
    }


public:
    static State optimize(State initial) {
        State current = initial;
        Matrix3x3 matrix;
       
        for(int iter = 0; iter < MAX_ITERATIONS; iter++) {
            if(hasConverged(current)) break;
           
            // Compute Jacobian
            double J[3][3] = {
                {-2 * current.lambda, 0, -2 * current.x1},
                {0, -4 * current.lambda, -4 * current.x2},
                {-2 * current.x1, -4 * current.x2, 0}
            };
           
            // Compute F vector
            double F1 = Functions::dL_dx1(current.x1, current.x2, current.lambda);
            double F2 = Functions::dL_dx2(current.x1, current.x2, current.lambda);
            double FL = Functions::dL_dlambda(current.x1, current.x2, current.lambda);
           
            // Solve system
            double invJ[3][3];
            matrix.set(J);
            matrix.inverse(invJ);
           
            // Update state
            double dx1 = -(invJ[0][0]*F1 + invJ[0][1]*F2 + invJ[0][2]*FL);
            double dx2 = -(invJ[1][0]*F1 + invJ[1][1]*F2 + invJ[1][2]*FL);
            double dl = -(invJ[2][0]*F1 + invJ[2][1]*F2 + invJ[2][2]*FL);
           
            current.x1 += LEARNING_RATE * dx1;
            current.x2 += LEARNING_RATE * dx2;
            current.lambda += LEARNING_RATE * dl;
           
            if(iter % 5 == 0) {
                cout << "Iteration " << iter
                     << ": x1=" << current.x1
                     << ", x2=" << current.x2
                     << ", λ=" << current.lambda
                     << ", g=" << Functions::g(current.x1, current.x2) << endl;
            }
        }
        return current;
    }
};


int main() {
    cout << fixed << setprecision(6);
    cout << "Optimization using Newton-Raphson Method\n";
    cout << "=======================================\n\n";
   
    // Optimize with positive lambda
    cout << "Solution with positive lambda:\n";
    auto pos_result = NewtonOptimizer::optimize({1.0, 1.0, 5.0});
    double f_pos = Functions::f(pos_result.x1, pos_result.x2);
   
    cout << "\nFinal result:\n"
         << "x1 = " << pos_result.x1
         << ", x2 = " << pos_result.x2
         << ", λ = " << pos_result.lambda
         << "\nf = " << f_pos << "\n\n";
   
    // Optimize with negative lambda
    cout << "Solution with negative lambda:\n";
    auto neg_result = NewtonOptimizer::optimize({-1.0, -1.0, -5.0});
    double f_neg = Functions::f(neg_result.x1, neg_result.x2);
   
    cout << "\nFinal result:\n"
         << "x1 = " << neg_result.x1
         << ", x2 = " << neg_result.x2
         << ", λ = " << neg_result.lambda
         << "\nf = " << f_neg << "\n\n";
   
    cout << "Maximum value of f: " << max(f_pos, f_neg) << "\n";
   
    return 0;
}

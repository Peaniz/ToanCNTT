    #include <iostream>
    #include <string>
    #include <cmath>
    #include <iomanip>
    #include <fstream>
    using namespace std;

    #define MAX 100

    void Solve(double a, double b, double c, double d, double output[]) {
        b /= a;
        c /= a;
        d /= a;

        double disc, q, r, dum1, s, t, term1, r13;
        q = (3.0 * c - (b * b)) / 9.0;
        r = -(27.0 * d) + b * (9.0 * c - 2.0 * (b * b));
        r /= 54.0;
        disc = q * q * q + r * r;
        term1 = (b / 3.0);

        double x1_real, x2_real, x3_real;
        double x2_imag, x3_imag;
        string x2_imag_s, x3_imag_s;

        if (disc > 0) { // Một nghiệm thực, hai nghiệm phức
            s = r + sqrt(disc);
            s = s < 0 ? -cbrt(-s) : cbrt(s);
            t = r - sqrt(disc);
            t = t < 0 ? -cbrt(-t) : cbrt(t);
            x1_real = -term1 + s + t;
            term1 += (s + t) / 2.0;
            x3_real = x2_real = -term1;
            term1 = sqrt(3.0) * (-t + s) / 2;
            x2_imag = term1;
            x3_imag = -term1;
            x2_imag_s = " + " + to_string(x2_imag) + "i";
            x3_imag_s = " - " + to_string(x2_imag) + "i";
        } else if (disc == 0) { // Các nghiệm thực, ít nhất hai nghiệm bằng nhau
            r13 = r < 0 ? -cbrt(-r) : cbrt(r);
            x1_real = -term1 + 2.0 * r13;
            x3_real = x2_real = -(r13 + term1);
        } else { // Ba nghiệm thực không bằng nhau
            q = -q;
            dum1 = q * q * q;
            dum1 = acos(r / sqrt(dum1));
            r13 = 2.0 * sqrt(q);
            x1_real = -term1 + r13 * cos(dum1 / 3.0);
            x2_real = -term1 + r13 * cos((dum1 + 2.0 * M_PI) / 3.0);
            x3_real = -term1 + r13 * cos((dum1 + 4.0 * M_PI) / 3.0);
        }

        output[0] = x1_real;
        output[1] = x2_real;
        output[2] = x3_real;
    }

    void sort(double arr[], int n) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] < arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    void Identify(double a[][MAX], int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = (i == j) ? 1.0 : 0.0;
            }
        }
    }

    void Zerotify(double a[][MAX], int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = 0.0;
            }
        }
    }

    void Assign(double a[][MAX], double b[][MAX], int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = b[i][j];
            }
        }
    }

    void print(double a[][MAX], int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (fabs(a[i][j]) < 1e-5) {
                    cout << fixed << setprecision(5) << 0.0 << "\t";
                } else {
                    cout << fixed << setprecision(5) << a[i][j] << "\t";
                }
            }
            cout << "\n";
        }
    }

    void multiple(double a[][MAX], double b[][MAX], int n, double result[][MAX]) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[i][j] = 0;
                for (int k = 0; k < n; k++) {
                    result[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }

    void FormMatrix(double numb, double M[][MAX], double output[][MAX], int row, int column) {
        double temp[MAX][MAX], temp1[MAX][MAX];
        Zerotify(temp, row);
        Zerotify(temp1, row);

        for (int i = 0; i < row; i++) {
            temp[i][0] = pow(numb, (double)((row - 1) - i));
        }
        multiple(M, temp, row, temp1);

        for (int i = 0; i < row; i++) {
            output[i][column] = temp1[i][0];
        }
    }

    void Eigendecomposite(double a[][MAX], int n) {
        double M[MAX][MAX], M1[MAX][MAX], temp[MAX][MAX], C[MAX][MAX], P[MAX][MAX];
        Identify(C, n);

        for (int k = n - 2; k >= 0; k--) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i != k) {
                        M[i][j] = (i == j) ? 1 : 0;
                        M1[i][j] = (i == j) ? 1 : 0;
                    } else {
                        M1[i][j] = a[k + 1][j];
                        M[i][j] = (j == k) ? 1 / a[k + 1][k] : -a[k + 1][j] / a[k + 1][k];
                    }
                }
            }
            multiple(a, M, n, temp);
            multiple(M1, temp, n, a);
            multiple(C, M, n, temp);
            Assign(C, temp, n);
        }

        double output[MAX];
        Solve(1, -a[0][0], -a[0][1], -a[0][2], output);
        sort(output, n);
        
        cout << "\nEigenvalues (Gia tri rieng):\n";
        for (int i = 0; i < n; i++) {
            cout << "λ" << i + 1 << " = " << fixed << setprecision(5) << output[i] << endl;
        }

        for (int i = 0; i < n; i++) {
            FormMatrix(output[i], C, P, n, i);
        }

        cout << "\nEigenvectors (Vector rieng):\n";
        print(P, n);
    }

    int main() {
        double matrix[MAX][MAX] = {{4,8,6}, {8,8,6}, {9,8,6}};
        int n = 3;

        Eigendecomposite(matrix, n);
        return 0;
    }

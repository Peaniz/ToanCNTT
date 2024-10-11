#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef vector<vector<double>> Matrix;

const double EPSILON = 1e-9;

// Hàm tạo ma trận 0
Matrix createMatrix(int rows, int cols) {
    return Matrix(rows, vector<double>(cols, 0));
}

// Hàm tính chuẩn của vectơ (để chuẩn hóa)
double norm(const vector<double>& vec) {
    double sum = 0;
    for (double val : vec) {
        sum += val * val;
    }
    return sqrt(sum);
}

// Hàm lặp Jacobi để tìm trị riêng và vectơ riêng cho ma trận đối xứng
void jacobiEigenvalue(Matrix& A, vector<double>& eigenvalues, Matrix& eigenvectors, int n) {
    // Khởi tạo ma trận eigenvectors là ma trận đơn vị
    eigenvectors = createMatrix(n, n);
    for (int i = 0; i < n; ++i) {
        eigenvectors[i][i] = 1;
    }

    for (int k = 0; k < 100; ++k) {  // Giới hạn số vòng lặp
        // Tìm phần tử không chéo lớn nhất của A
        double maxVal = 0;
        int p = 0, q = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (fabs(A[i][j]) > maxVal) {
                    maxVal = fabs(A[i][j]);
                    p = i;
                    q = j;
                }
            }
        }

        // Kiểm tra điều kiện dừng
        if (maxVal < EPSILON) {
            break;
        }

        // Tính góc xoay
        double theta = 0.5 * atan2(2 * A[p][q], A[p][p] - A[q][q]);

        // Tạo ma trận xoay Jacobi
        double cosTheta = cos(theta);
        double sinTheta = sin(theta);

        // Cập nhật ma trận A
        double app = A[p][p], aqq = A[q][q], apq = A[p][q];
        A[p][p] = cosTheta * cosTheta * app + sinTheta * sinTheta * aqq - 2 * sinTheta * cosTheta * apq;
        A[q][q] = sinTheta * sinTheta * app + cosTheta * cosTheta * aqq + 2 * sinTheta * cosTheta * apq;
        A[p][q] = A[q][p] = 0;

        for (int i = 0; i < n; ++i) {
            if (i != p && i != q) {
                double aip = A[i][p], aiq = A[i][q];
                A[i][p] = A[p][i] = cosTheta * aip - sinTheta * aiq;
                A[i][q] = A[q][i] = sinTheta * aip + cosTheta * aiq;
            }
        }

        // Cập nhật ma trận eigenvectors
        for (int i = 0; i < n; ++i) {
            double vip = eigenvectors[i][p], viq = eigenvectors[i][q];
            eigenvectors[i][p] = cosTheta * vip - sinTheta * viq;
            eigenvectors[i][q] = sinTheta * vip + cosTheta * viq;
        }
    }

    // Sao chép các phần tử trên đường chéo của A vào eigenvalues
    eigenvalues.resize(n);
    for (int i = 0; i < n; ++i) {
        eigenvalues[i] = A[i][i];
    }
}

// Hàm nhập ma trận từ bàn phím
Matrix inputMatrix(int rows, int cols) {
    Matrix mat = createMatrix(rows, cols);
    cout << "Nhập các phần tử của ma trận (" << rows << "x" << cols << "):" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << "A[" << i << "][" << j << "]: ";
            cin >> mat[i][j];
        }
    }
    return mat;
}

int main() {
    int n;
    cout << "Nhập kích thước ma trận vuông: ";
    cin >> n;

    Matrix A = inputMatrix(n, n);

    // Tính trị riêng và vectơ riêng bằng phương pháp Jacobi
    vector<double> eigenvalues;
    Matrix eigenvectors;

    jacobiEigenvalue(A, eigenvalues, eigenvectors, n);

    // In trị riêng
    cout << "Trị riêng:" << endl;
    for (double val : eigenvalues) {
        cout << val << " ";
    }
    cout << endl;

    // In vectơ riêng
    cout << "Vectơ riêng (ma trận eigenvectors):" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << eigenvectors[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

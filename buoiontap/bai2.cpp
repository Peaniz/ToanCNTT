#include <bits/stdc++.h>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

//g++ -I D:/BACH_KHOA_LAME/nam3/ToanCNTT/eigen-3.4.0/eigen-3.4.0 SVD.cpp -o SVD 

MatrixXf normalize(const MatrixXf& v) {
    float norm = 0.0;
    for (int i = 0; i < v.rows(); ++i) {
        for (int j = 0; j < v.cols(); ++j) {
            norm += v(i,j) * v(i,j);
        }
    }
    norm = sqrt(norm);
    
    MatrixXf result = v;
    if (norm > 1e-10) {  
        for (int i = 0; i < v.rows(); ++i) {
            for (int j = 0; j < v.cols(); ++j) {
                result(i,j) /= norm;
            }
        }
    }
    return result;
}
MatrixXf transpose(const MatrixXf& matrix) {
    MatrixXf result(matrix.cols(), matrix.rows());
    for (int i = 0; i < matrix.rows(); ++i) {
        for (int j = 0; j < matrix.cols(); ++j) {
            result(j,i) = matrix(i,j);
        }
    }
    return result;
}

MatrixXf Multiple(MatrixXf A, int A_row, int A_col, MatrixXf B,int B_row, int B_col)
{
     MatrixXf result(A_row, B_col);
     result.setZero();  
     for (int i =0 ; i< A_row; i++)
     {
        for (int j = 0; j < B_col; j++)
        {
            for (int k = 0; k < A_col; k++)  
            {
                result(i,j) += A(i,k)* B(k,j);
            }
        }
     }
     return result;
}

MatrixXf Multiple_SingleNumber(MatrixXf A, int A_row, int A_col, double a)
{
     MatrixXf result(A_row, A_col);
     for (int i =0 ; i< A_row; i++)
     {
        for (int j = 0; j < A_col; j++)
        {
            result(i, j) = A(i, j) * a;  
        }
     }
     return result;
}

MatrixXf MatrixDacTrung(MatrixXf A, int row, int column)
{
     MatrixXf At = transpose(A);
     MatrixXf mtdt = Multiple(At, column, row, A, row, column);  
     return mtdt;
}

MatrixXf vtCal(MatrixXf A, int row, int column)
{
    MatrixXf mtdt = MatrixDacTrung(A, row, column);
    SelfAdjointEigenSolver<MatrixXf> eigensolver(mtdt);
    if (eigensolver.info() != Success) abort();
    
    MatrixXf eigenvectors = eigensolver.eigenvectors().rowwise().reverse();
    for (int i = 0; i < column; ++i) {
        eigenvectors.col(i) = normalize(eigenvectors.col(i));
        if (eigenvectors.col(i)(0) < 0) {
            eigenvectors.col(i) *= -1;
        }
    }

    return eigenvectors;  // Remove the transpose here
}


MatrixXf sigmaCal(MatrixXf A, int row, int column)
{
    MatrixXf mtdt = MatrixDacTrung(A, row, column);
    SelfAdjointEigenSolver<MatrixXf> eigensolver(mtdt);
    if (eigensolver.info() != Success) abort();
    
    VectorXf eigenvalues = eigensolver.eigenvalues().reverse();

    MatrixXf sigma = MatrixXf::Zero(row, column);
    for (int i = 0; i < std::min(row, column); i++)
    {
        sigma(i,i) = sqrt(fabs(eigenvalues(i)));  
    }
    return sigma;
}

MatrixXf GetCol(MatrixXf A, int row, int column, int selected_column)
{
     MatrixXf Result(row, 1);
     for (int i = 0; i < row; i++)
     {
          Result(i,0) = A(i, selected_column);
     }
     return Result;
}

MatrixXf uCal(MatrixXf A, int row, int column) {
    MatrixXf U(row, row);
    MatrixXf Sigma = sigmaCal(A, row, column);
    MatrixXf V = vtCal(A, row, column);  
    U.setZero();

    for (int i = 0; i < std::min(row, column); i++) {
        if (Sigma(i, i) > 1e-6)  // Avoid division by zero
        {
            MatrixXf temp_V = V.col(i);
            MatrixXf temp = A * temp_V / Sigma(i, i); 
            U.col(i) = temp;
        }
    }

    for (int i = 0; i < row; i++) {
        U.col(i) = normalize(U.col(i)); 

        for (int j = 0; j < i; j++) {
            float proj = U.col(j).dot(U.col(i));
            U.col(i) -= proj * U.col(j); 
        }
        U.col(i) = normalize(U.col(i)); 
    }

    return U;
}



void Cholesky_Decomposition(const MatrixXf& matrix, MatrixXf& L, MatrixXf& Lt, int n) {
    L = MatrixXf::Zero(n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            float sum = 0;

            if (j == i) {
                for (int k = 0; k < j; k++) {
                    sum += pow(L(j, k), 2);
                }
                L(j, j) = sqrt(matrix(j, j) - sum);
            } else {
                for (int k = 0; k < j; k++) {
                    sum += L(i, k) * L(j, k);
                }
                L(i, j) = (matrix(i, j) - sum) / L(j, j);
            }
        }
    }

    Lt = transpose(L);
}

void LDLT_Decomposition(const MatrixXf& matrix, MatrixXf& L, MatrixXf& D, MatrixXf& Lt, int n) {
    L = MatrixXf::Identity(n, n);
    D = MatrixXf::Zero(n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            float sum = 0;

            if (i == j) {
                for (int k = 0; k < j; k++) {
                    sum += L(j, k) * L(j, k) * D(k, k);
                }
                D(j, j) = matrix(j, j) - sum;
            } else {
                for (int k = 0; k < j; k++) {
                    sum += L(i, k) * L(j, k) * D(k, k);
                }
                L(i, j) = (matrix(i, j) - sum) / D(j, j);
            }
        }
    }

    Lt = transpose(L);
}




struct SVDResult {
    MatrixXf U;
    MatrixXf Sigma;
    MatrixXf Vt;
};

SVDResult computeSVD(MatrixXf A, int row, int column)
{
    SVDResult result;
    result.U = uCal(A, row, column);
    result.Sigma = sigmaCal(A, row, column);
    result.Vt = transpose(vtCal(A, row, column));  
    return result;
}

MatrixXf roundMatrix(const MatrixXf& matrix) {
    return (matrix * 1000.0).unaryExpr([](float x) { return std::round(x); }) / 1000.0;
}

int main()
{


    MatrixXf A(3,3);
    A << 1, 2, 3,
         1, 2, 4,
         1, 2, 5;


     // Cholesky Decomposition
    MatrixXf L_cholesky(3, 3), Lt_cholesky(3, 3);
    Cholesky_Decomposition(A, L_cholesky, Lt_cholesky, 3);
    cout << "\nCholesky Decomposition - L:\n" << roundMatrix(L_cholesky) << "\n";
    cout << "Cholesky Decomposition - L^T:\n" << roundMatrix(Lt_cholesky) << "\n";

    // LDLT Decomposition
    MatrixXf L_ldlt(3, 3), D_ldlt(3, 3), Lt_ldlt(3, 3);
    LDLT_Decomposition(A, L_ldlt, D_ldlt, Lt_ldlt, 3);
    cout << "\nLDLT Decomposition - L:\n" << roundMatrix(L_ldlt) << "\n";
    cout << "LDLT Decomposition - D:\n" << roundMatrix(D_ldlt) << "\n";
    cout << "LDLT Decomposition - L^T:\n" << roundMatrix(Lt_ldlt) << "\n";

    // SVD Decomposition
    SVDResult svd = computeSVD(A, 3, 3);

    cout << "\nMatrix A:\n" << roundMatrix(A) << "\n\n";
    cout << "U:\n" << roundMatrix(svd.U) << "\n\n";
    cout << "Sigma:\n" << roundMatrix(svd.Sigma) << "\n\n";
    cout << "Vt:\n" << roundMatrix(svd.Vt) << "\n\n";

    // Verify the decomposition
    MatrixXf reconstructed = svd.U * svd.Sigma * svd.Vt;
    cout << "Reconstructed A:\n" << roundMatrix(reconstructed) << "\n\n";
    cout << "Reconstruction error: " << round((A - reconstructed).norm() * 1000.0) / 1000.0 << "\n";

    return 0;
}

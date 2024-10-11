#include <bits/stdc++.h>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

//g++ -I D:/BACH_KHOA_LAME/nam3/ToanCNTT/eigen-3.4.0/eigen-3.4.0 SVD.cpp -o SVD 

MatrixXf Transpose_1(MatrixXf A, int row, int column)
{
     MatrixXf A_trans(column,row);
     for (int i = 0; i< column; i++)
     {
          for (int j = 0; j< row; j++)
          {
               A_trans(j, i) = A(i, j);
          }
     }
     return A_trans;
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
     MatrixXf At = Transpose_1(A, row, column);
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
        eigenvectors.col(i).normalize();
        if (eigenvectors.col(i)(0) < 0) {
            eigenvectors.col(i) *= -1;
        }
    }

    return eigenvectors.transpose();  
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

MatrixXf uCal(MatrixXf A, int row, int column)
{
    MatrixXf U(row, row);
    MatrixXf Sigma = sigmaCal(A, row, column);
    MatrixXf Vt = vtCal(A, row, column);
    U.setZero();

    for (int i = 0; i < std::min(row, column); i++)
    {
        if (Sigma(i, i) > 1e-6)  
        {
            MatrixXf temp_V = GetCol(Vt, column, column, i);
            MatrixXf temp = A * temp_V / Sigma(i, i);
            U.col(i) = temp;
            if (U.col(i)(0) < 0) {
                U.col(i) *= -1;  
                Vt.row(i) *= -1;  
            }
        }
    }
    return U;
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
    result.Vt = vtCal(A, row, column);
    return result;
}

int main()
{
    int row, column;
    
    cout << "Enter the number of rows: ";
    cin >> row;
    cout << "Enter the number of columns: ";
    cin >> column;

    MatrixXf A(row, column);
    
    cout << "Enter the matrix elements row by row:\n";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cin >> A(i, j);
        }
    }

    SVDResult svd = computeSVD(A, row, column);

    cout << "\nMatrix A:\n" << A << "\n\n";
    cout << "U:\n" << svd.U << "\n\n";
    cout << "Sigma:\n" << svd.Sigma << "\n\n";
    cout << "Vt:\n" << svd.Vt << "\n\n";

    // Verify the decomposition
    MatrixXf reconstructed = svd.U * svd.Sigma * svd.Vt;
    cout << "Reconstructed A:\n" << reconstructed << "\n\n";
    cout << "Reconstruction error: " << (A - reconstructed).norm() << "\n";

    return 0;
}


#include <bits/stdc++.h>
using namespace std;

const int MAX = 100;

void Identify(float a[][MAX] ,int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j) a[i][j] = 1;
            else a[i][j] = 0;
        }
    }
}

void inputMatrix(float matrix[][MAX], int n)
{   
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> matrix[i][j];
}

void printMatrix(float matrix[][MAX], int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cout << setw(6) << matrix[i][j] << "\t";
        cout << setw(6) << endl;
    }
        
}

bool Is_Triangular(float matrix[][MAX], int n)
{
    for(int i = 0; i< n ; i++)
    {
        for(int j = 0; j < n; j++)
            if(matrix[i][j] != matrix[j][i])
                return false;
    }
    return true;
}

void mulMat(float mat1[][MAX], float mat2[][MAX], int n)
{
    int rslt[MAX][MAX];


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            rslt[i][j] = 0;

            for (int k = 0; k < n; k++) {
                rslt[i][j] += mat1[i][k] * mat2[k][j];
            }
            cout << rslt[i][j] << "\t";
        }
    }
}

void Cholesky_Decomposition(float matrix[][MAX], float output1[][MAX], float output2[][MAX], int n)
{   
    if(!Is_Triangular(matrix, n))
    {
        cout << "Ma tran khong doi xung.";
        return;
    }
	for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            output1[i][j] = 0;


	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			int sum = 0;

			if (j == i) 
			{
				for (int k = 0; k < j; k++)
					sum += pow(output1[j][k], 2);
				output1[j][j] = sqrt(matrix[j][j] - sum);
			} else {
				for (int k = 0; k < j; k++)
					sum += (output1[i][k] * output1[j][k]);
				output1[i][j] = (matrix[i][j] - sum) / output1[j][j];
			}
		}
	}

	for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            output2[i][j] = output1[j][i];
}

void LDLT_Decomposition(float matrix[][MAX], float output1[][MAX], float output2[][MAX], float output3[][MAX], int n)
{
    Identify(output1, n);
    Identify(output3, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            float sum = 0;
 
            if (j == i) 
            {
                for (int k = 0; k < j; k++)
                    sum += pow(output1[j][k], 2) * output2[k][k];
                output2[j][j] = matrix[j][j] - sum;
            } else {
                for (int k = 0; k < j; k++)
                    sum += (output1[i][k] * output1[j][k] * output2[k][k]);
                output1[i][j] = (matrix[i][j] - sum) / output2[j][j];
            }
        }
    }
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            output3[i][j] = output1[j][i];
    
    cout << setw(15) << " L " 
         << setw(31) << "D"
          << setw(32) << "LT" << endl;
    for (int i = 0; i < n; i++) {
         

        for (int j = 0; j < n; j++)
            cout << setw(6) << output1[i][j] << "\t";
        cout << "\t";
         
        for (int j = 0; j < n; j++)
            cout << setw(6) << output2[i][j] << "\t";
        cout << "\t";

        for (int j = 0; j < n; j++)
            cout << setw(6) << output3[i][j] << "\t";
        cout << endl;
    }

}

int main()
{
	int n;
	float matrix[MAX][MAX];
    cout << "Nhap n:";
    cin >> n;
    cout << "Nhap ma tran:"<< endl;
    inputMatrix(matrix,n);
    cout << "Ma tran da nhap:"<< endl;
    printMatrix(matrix, n);
    float output1[MAX][MAX], output2[MAX][MAX],output3[MAX][MAX];
    Cholesky_Decomposition(matrix, output1, output2,n);
    cout << setw(6) << " Lower Triangular" << endl;
    printMatrix(output1, n);
    cout << setw(6) << " Tranpose Lower Triangular" << endl;
    printMatrix(output2, n);
    cout << "LDLT DECOMPOSITION: \n";
    LDLT_Decomposition(matrix, output1, output2, output3, n);

	return 0;
}

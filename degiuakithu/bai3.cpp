#include <bits/stdc++.h>
using namespace std;
#define MAX 100

void Identify(float a[][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                a[i][j] = 1;
            else
                a[i][j] = 0;
        }
    }
}

void transpose(float a[][MAX], int row, int column, float b[][MAX])
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
        {
            b[i][j] = a[j][i];
        }
}

void multiple(float a[][MAX], float b[][MAX], int row_1, int column_1, int row_2, int column_2, float result[][MAX])
{
    if (column_1 != row_2)
        return;
    for (int i = 0; i < row_1; i++)
    {
        for (int j = 0; j < column_2; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < row_2; k++)
            {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void printMatrix(float matrix[][MAX], int n, const string &name)
{
    cout << "Matrix " << name << ":\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << left << setw(10) << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void LDLT_Decomposition(float matrix[][MAX], float output1[][MAX], float output2[][MAX], float output3[][MAX], int n)
{
    Identify(output1, n);
    Identify(output3, n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            float sum = 0;

            if (j == i)
            {
                for (int k = 0; k < j; k++)
                    sum += pow(output1[j][k], 2) * output2[k][k];
                output2[j][j] = matrix[j][j] - sum;
            }
            else
            {
                for (int k = 0; k < j; k++)
                    sum += (output1[i][k] * output1[j][k] * output2[k][k]);
                output1[i][j] = (matrix[i][j] - sum) / output2[j][j];
            }
        }
    }
    transpose(output1, n, n, output3);

    printMatrix(output1, n, "L");
    printMatrix(output2, n, "D");
    printMatrix(output3, n, "LT");
}

int main()
{
    int n = 3;
    float matrix[MAX][MAX] = {{4,8,6}, {8,8,6}, {9,8,6}};
    float L1[MAX][MAX], L2[MAX][MAX], L3[MAX][MAX];
    printMatrix(matrix, n, "Ma tran dau vao");
    cout << "LDLT Decomposition: \n";
    LDLT_Decomposition(matrix, L1, L2, L3, n);

    return 0;
}

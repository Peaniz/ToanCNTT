#include <bits/stdc++.h> 
using namespace std; 

int modInverse(int A, int M)
{
    for (int X = 1; X < M; X++)
        if (((A % M) * (X % M)) % M == 1)
            return X;
} 
//inverse modulo

int main()
{
    int A = 6, M = 17;
    cout << modInverse(A,M);
}
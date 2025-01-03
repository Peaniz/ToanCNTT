#include <bits/stdc++.h> 
using namespace std; 

int inv(int a, int m) 
{ 
    int m0 = m, t, q; 
    int x0 = 0, x1 = 1; 

    if (m == 1) 
        return 0; 

    while (a > 1) { 
        q = a / m; 

        t = m; 

        m = a % m, a = t; 

        t = x0; 

        x0 = x1 - q * x0; 

        x1 = t; 
    } 
    if (x1 < 0) 
        x1 += m0; 

    return x1; 
} 

int findMinX(int num[], int rem[], int k) 
{ 
    int prod = 1; 
    for (int i = 0; i < k; i++) 
        prod *= num[i]; 

    int result = 0; 

    for (int i = 0; i < k; i++) { 
        int pp = prod / num[i]; 
        result += rem[i] * inv(pp, num[i]) * pp; 
    } 
    cout << "Result before mod: " << result << endl;
    
    return result % prod; 
} 

int main(void) 
{ 
    int k;
    cout << "Nhap so phan tu cua mang: ";
    cin >> k;

    int num[k], rem[k]; 

    cout << "Nhap cac gia tri cua mang num[]: ";
    for (int i = 0; i < k; i++) {
        cin >> num[i];
    }

    cout << "Nhap cac gia tri cua mang rem[]: ";
    for (int i = 0; i < k; i++) {
        cin >> rem[i];
    }

    cout << "x is " << findMinX(num, rem, k); 
    return 0; 
}

#include <iostream>
#include <cmath>

using namespace std;

const int MAX_N = 500;  

void sieveOfEratosthenes(int n, bool isPrime[]) {
    for (int i = 0; i <= n; i++) {
        isPrime[i] = true;
    }
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

int countPrimesInRange(int m, int n, const bool isPrime[]) {
    int count = 0;
    for (int i = m; i <= n; i++) {
        if (isPrime[i]) count++;
    }
    return count;
}

int findClosestPrime(int k, int m, int n, const bool isPrime[]) {
    int closest = m;
    int minDiff = abs(k - m);
    
    for (int i = m; i <= n; i++) {
        if (isPrime[i]) {
            int diff = abs(k - i);
            if (diff < minDiff) {
                minDiff = diff;
                closest = i;
            }
        }
    }
    return closest;
}

int main() {
    int m = 300, n = 500, k = 436;
    
    bool isPrime[MAX_N + 1];
    sieveOfEratosthenes(n, isPrime);
    
    int primeCount = countPrimesInRange(m, n, isPrime);
    cout << "So luong so nguyen to trong khoang " << m << "-" << n << ": " << primeCount << endl;
    
    cout << "Cac so nguyen to trong khoang " << m << "-" << n << ": ";
    for (int i = m; i <= n; i++) {
        if (isPrime[i]) cout << i << " ";
    }
    cout << endl;
    
    int closestPrime = findClosestPrime(k, m, n, isPrime);
    cout << "So nguyen to gan " << k << " nhat trong khoang " << m << "-" << n << ": " << closestPrime << endl;
    
    return 0;
}

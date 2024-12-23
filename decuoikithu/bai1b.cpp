#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

// Find perfect numbers less than N
int findLargestPerfectNumber(int N) {
    int largest = 0;
    
    for (int i = 2; i < N; i++) {
        int sum = 1;
        for (int j = 2; j <= sqrt(i); j++) {
            if (i % j == 0) {
                sum += j;
                if (j != i/j) {
                    sum += i/j;
                }
            }
        }
        if (sum == i) {
            largest = i;
        }
    }
    return largest;
}

// Sieve of Eratosthenes implementation
vector<bool> sieveOfEratosthenes(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return isPrime;
}

// Find nearest prime number to M
int findNearestPrime(int M) {
    // Create sieve array with sufficient size
    int range = max(M + 1000, 10000); // Ensure we have enough range
    vector<bool> isPrime = sieveOfEratosthenes(range);
    
    // Initialize variables for finding nearest prime
    int nearestPrime = M;
    int minDiff = INT_MAX;
    
    // Search both below and above M
    for (int i = 0; i <= range; i++) {
        // Check numbers below M
        if (M - i >= 2 && isPrime[M - i]) {
            nearestPrime = M - i;
            break;
        }
        // Check numbers above M
        if (M + i <= range && isPrime[M + i]) {
            if (i < minDiff) {
                nearestPrime = M + i;
                break;
            }
        }
    }
    
    return nearestPrime;
}

int main() {
    const int N = 9000;
    
    int M = findLargestPerfectNumber(N);
    cout << "So hoan hao lon nhat nho hon " << N << " la: " << M << endl;
    
    int nearestPrime = findNearestPrime(M);
    cout << "So nguyen to gan " << M << " nhat la: " << nearestPrime << endl;
    cout << "Khoang cach: " << abs(M - nearestPrime) << endl;
    
    return 0;
}

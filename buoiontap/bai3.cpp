#include <iostream>
#include <cmath>

using namespace std;

const int MAX_N = 2000;

void sieveOfEratosthenes(bool isPrime[]) {
    for (int i = 0; i <= MAX_N; i++) {
        isPrime[i] = true;
    }
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i * i <= MAX_N; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= MAX_N; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

int findNearestPrime(int n, const bool isPrime[]) {
    if (isPrime[n]) return n;
    int lower = n - 1, upper = n + 1;
    while (true) {
        if (lower >= 2 && isPrime[lower]) return lower;
        if (upper <= MAX_N && isPrime[upper]) return upper;
        lower--;
        upper++;
    }
}

bool isPerfectNumber(int num) {
    if (num <= 1) return false;
    int sum = 1;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) {
            sum += i;
            if (i != num / i) {
                sum += num / i;
            }
        }
    }
    return sum == num;
}


int main() {
    int n = 301;
    bool isPrime[MAX_N + 1];
    sieveOfEratosthenes(isPrime);
    
    int nearestPrime = findNearestPrime(n, isPrime);
    cout << "a.So nguyen to gan " << n << " nhat la: " << nearestPrime << endl;
    int M_perfectCount = 0;
    int sum = 0;
    cout << "b. Cac so hoan hao trong M: ";
    for (int i = 2; i <= 2000; i++) {
        if (isPerfectNumber(i)) {  
            cout << i << " ";
            M_perfectCount++;
            sum += i;
        }
    }
    cout << endl;
    
    cout << "So phan tu hoan hao trong M: " << M_perfectCount << endl;
    cout << "Tong cac so hoan hao: " << sum << endl;
    return 0;
}

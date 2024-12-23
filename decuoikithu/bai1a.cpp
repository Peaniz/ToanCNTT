#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
bool isPerfectNumber(int n) {
    if (n <= 1) return false;
    
    int sum = 1;  
    
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n/i) {
                sum += n/i;
            }
        }
    }
    
    return sum == n;
}
void findPerfectNumbers(int N) {
    vector<int> perfectNumbers;
    for (int i = 2; i < N; i++) {
        if (isPerfectNumber(i)) {
            perfectNumbers.push_back(i);
        }
    }

    cout << "So luong so hoan hao nho hon " << N << " la: " 
         << perfectNumbers.size() << endl;
    
    cout << "Cac so hoan hao la: ";
    for (int num : perfectNumbers) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    const int N = 9000;
    
    findPerfectNumbers(N);
    
    return 0;
}

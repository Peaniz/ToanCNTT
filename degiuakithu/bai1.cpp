// Bài 2: Cho n nguyên dương nhập vào bàn phím, xác định số lượng các số nguyên tố cùng nhau với n, và liệt kê các số đấy (dùng Euler's totient function)
// + a và b là 2 số nguyên tố cùng nhau (coprime) khi UCLN của chúng = 1 (gcd = 1)
// + Kiểm tra số nguyên tố, đọc theo node màu đỏ slide 29
// + Note: thay vì từ 1->n, thay đổi thành a-> n với a nhập từ bàn phím

#include <iostream>
#include <cmath>
#include <string.h>
using namespace std;

int gcd(int a, int b)
{
    if(b==0) return a;
    return gcd(b, a%b);
}

void primefactor(long long n, int primes[], int counts[], int &size)
{
    size = 0;
    int count = 0;
    
    while(n % 2 == 0)
    {
        count++;
        n /= 2;
    }
    if(count)
    {
        primes[size] = 2;
        counts[size] = count;
        size++;
        count = 0;
    }

    for(int i = 3; i <= sqrt(n); i = i + 2)
    {
        while(n % i == 0)
        {
            count++;
            n /= i;
        }
        if(count)
        {
            primes[size] = i;
            counts[size] = count;
            size++;
            count = 0;
        }
    }

    if(n > 2)
    {
        primes[size] = n;
        counts[size] = 1;
        size++;
    }
}

bool Is_Prime(long long n)
{   
    if(n==1) return false;
    for(int i = 2; i <= sqrt(n); i++)
        if(n % i == 0)
            return false;
    return true;
}

int ETF(int primes[], int counts[], long long n, int size)
{   

    if(Is_Prime(n))
        return n-1;
    int result = 1;
    for(int i = 0; i < size; i++)
        result *= pow(primes[i], counts[i]-1)*(primes[i] - 1);
    return result;
}

void list_coprime(int n, int a)
{    
    int total = 0;
    for(int i = a; i < n; i++)
        if(gcd(n,i) == 1)
        {
            total += i;
            cout << i << " ";
        }
    cout << "\nTong cac so coprime la: " << total << endl;
}

int findNearestPrimeDivisibleBy3(int N) {
    int up = N, down = N;
    while (true) {
        if (up % 3 == 0 && Is_Prime(up)) return up;
        if (down % 3 == 0 && Is_Prime(down)) return down;
        up++;
        down--;
    }
}

int main()
{   
    const int MAX_SIZE = 100; 
    int primes[MAX_SIZE];
    int counts[MAX_SIZE];
    int a = 1;
    long long N = 403;
    int size;
    primefactor(N,primes,counts,size);
    cout << "So cac so coprime trong khoang tu " << a << " toi " << N <<" la: " << ETF(primes, counts, N, size)<< endl;
    list_coprime(N,a);
     cout << "So nguyen to gan " << N << " nhat va chia het cho 3 la: " << findNearestPrimeDivisibleBy3(N) << "\n";


}
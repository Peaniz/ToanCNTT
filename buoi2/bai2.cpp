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
    for(int i = 1; i <= sqrt(n); i++)
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
    for(int i = a; i < n; i++)
        if(gcd(n,i) == 1)
            cout << i << "   ";
}

int main()
{   
    const int MAX_SIZE = 100; 
    int primes[MAX_SIZE];
    int counts[MAX_SIZE];
    int a = 1;
    long long n;
    int size;
    cout << "Nhap n:";
    cin >> n;
    primefactor(n,primes,counts,size);
    cout << "So cac so coprime trong khoang tu " << a << " toi " << n <<" la: " << ETF(primes, counts, n, size)<< endl;
    list_coprime(a,n);


}
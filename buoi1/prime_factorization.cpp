#include <iostream>
#include <cmath>
#include <string.h>
using namespace std;

int total_factor(long long n, int counts[], int size)
{
    int total = 1;
    for(int i = 0; i < size; i++)
    {
        total*= (counts[i] + 1);
    }
    return total;
}

void list_all_factor(long long n)
{
    for(int i = 1; i <= n/2; i++)
        if(n%i == 0)
            cout << i << " ";
    cout << n << endl;

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

long long sum_of_factor(int primes[], int counts[], int size)
{   
    long long result = 1;
    for(int i = 0; i < size; i++)
    {
        int prime = primes[i];
        int count = counts[i];
        result *= (pow(prime, count + 1) - 1) / (prime - 1);
    }
    return result;
}

long long product_of_factor(long long n, int counts[], int size)
{
    return pow(n, total_factor(n, counts, size)/2);
}

bool Is_Perfect(long long n, int primes[], int counts[], int size)
{
    return (sum_of_factor(primes,counts,size)/ n == 2);
}

double density_of_primes(long long n, int primes[], int counts[])
{
    return (n/log(n));
}

void SieveOfEratosthenes(int n)
{
    bool prime[n+1];
    memset(prime,true,sizeof(prime));
    for(int i = 2; i <= sqrt(n); i++)
    {
        if(prime[i] == true)
        {
            for(int p = i*i; p <= n; p += i)
                prime[p] = false;
        }
    }
    for(int i = 2; i <= n; i++)
        if(prime[i])
            cout << i << " ";
}

int main()
{
    long long n; 
    cout << "Nhap n: ";
    cin >> n;

    const int MAX_SIZE = 100; 
    int primes[MAX_SIZE];
    int counts[MAX_SIZE];
    int size;

    primefactor(n, primes, counts, size);

    cout << "Bai1: Phan tich so nguyen to: ";
    for(int i = 0; i < size; i++)
    {
        cout << primes[i] << "^" << counts[i];
        if (i != size - 1) cout << " * ";
    }
    cout << endl;
    cout << "Bai2: So uoc so cua " << n << " la: " << total_factor(n,counts,size)<<endl;
    list_all_factor(n);
    cout << "Bai3: Tong uoc so cua " << n << " la: " << sum_of_factor(primes, counts, size) << endl;
    cout << "Bai4: Tich uoc so cua " << n << " la: " << product_of_factor(n,counts,size) <<endl;
    if(Is_Perfect(n,primes,counts,size))
        cout << "Bai5: "<< n << " la so hoan hao."<<endl;
    else
        cout << "Bai5: "<< n << " khong phai la so hoan hao."<<endl;
    cout << "Bai6: Mat do cac so nguyen to tu 1 den  " << n << " la: " << density_of_primes(n,primes,counts) <<endl;
    cout << "Bai7: Cac so nguyen to nam trong khoang tu 2 den " << n << " la:" << endl;
    SieveOfEratosthenes(n);

    return 0;
}

//bai 3
#include <bits/stdc++.h>
using namespace std;
#define ll long long
class Number
{
    private: 
        ll x,y;
        int m;
    public:
        Number(ll x, ll y, int m): x(x), y(y), m(m){}
        ~Number(){};

        bool MOD1()
        {
            ll temp1 = (x+y)%m;
            ll temp2 = (x%m + y%m)%m;
            cout << "temp1 = " << temp1 << "\n";
            cout << "temp2 = " << temp2 << "\n";
            return (temp1 == temp2);
        }
        bool MOD2()
        {
            ll temp1 = (x-y)%m;
            ll temp2 = (x%m - y%m)%m;
            cout << "temp1 = " << temp1 << "\n";
            cout << "temp2 = " << temp2 << "\n";
            return (temp1 == temp2);
        }
        bool MOD3()
        {
            ll temp1 = (x*y)%m;
            ll temp2 = (x%m * y%m)%m;
            cout << "temp1 = " << temp1 << "\n";
            cout << "temp2 = " << temp2 << "\n";
            return (temp1 == temp2);
        }
        
};
int main()
{
    ll x,y;
    int m;
    cout << "NHAP X, Y, M: ";
    cin >> x;
    cin >> y; 
    cin >> m;
    Number A(x,y,m);
    char choice = '0';
    while(choice != '5'){
    cout << "1. CHECK 1\n";
    cout << "2. CHECK 2\n";
    cout << "3. CHECK 3\n";
    cout << "4. QUIT\n";
    cin >> choice;
    switch (choice)
    {
    case('1'):
    {
        bool h = A.MOD1();
        cout << "\n" <<(h? "true" : "false")<< "\n";
        break;
    }
    case('2'):
    {
        bool h = A.MOD2();
        cout << "\n" <<(h? "true" : "false")<< "\n";
        break;
    }
    case('3'):
    {
        bool h = A.MOD3();
        cout << "\n" <<(h? "true" : "false")<< "\n";
        break;
    }
    case('4'):
    {
        cout << "QUIT";
        continue;
    }
    default:
        break;
    }
    }
}
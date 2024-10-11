
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll Mcalc(ll m[], int size)
{
    ll M = 1;
    for (int i = 0; i<size; i++)
    {
        M*=m[i];
    }
    return M;
}
ll X_of(ll m[], int index, int size)
{
    ll X = 1;
    int i = 0;
    while (i<size)
    {
        if (i == index)
        {
            i++;

        }
        else{
            X *= m[i];
            i++;
        }
    }
    return X;
}
ll index_invertOf(ll m[], int index, int size)
{
    ll temp = X_of(m,index,size);
    int k = 0;
    while ((k*m[index] + 1) % temp != 0)
    {
        k++;
    }
    ll temp_equal = (k*m[index] + 1) / temp;
    return temp_equal;
}
void ChineseTheorem(int size, ll a[], ll m[])
{
    ll M_temp = Mcalc(m,size);
    ll S = 0;
    for (int i = 0; i<size; i++)
    {
        ll temp_X = X_of(m, i, size);
        ll temp_Y = index_invertOf(m, i, size);       
        S += a[i]*temp_X*temp_Y;
    }
    S = S % M_temp;
    while(S % M_temp > M_temp)
    {
        S = S % M_temp;
    }
    cout << "Chinese theorem: X = " << S << " + " << "k*" << M_temp << endl;
}
int main()
{
    int size = 5;
    ll a[size] = {2,3,4,5,6};
    ll m[size] = {5,7,9,11,13};
    cout << "All equations: \n";
    for (int i = 0; i< size; i++)
    {   
        cout << "x = " << a[i] << " mod " << m[i] << "\n";
    }
    ChineseTheorem(size,a,m);

}
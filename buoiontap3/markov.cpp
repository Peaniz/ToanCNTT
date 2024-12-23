#include<iostream>
#include<iomanip>
#include<math.h>
using namespace std;

const double EPS = 1e-6;

void nhan_ma_tran(double A[][4], double B[][4], double c[][4], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0 ; j < n; j++){
            c[i][j] = 0;
            for(int k = 0; k < n; k++){
                c[i][j] += A[i][k] * B[k][j];
            }
            if(fabs(c[i][j]) < EPS) c[i][j] = 0;
        }
    }
}

void in_ma_tran(double A[][4], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            cout << setw(10) << fixed << setprecision(5) << A[i][j] << " ";
        cout << endl;
    }
}

void in_vector(double S[], int n){
    for(int i = 0; i < n; i++)
        cout << setw(10) << fixed << setprecision(5) << S[i] << " ";
    cout << endl;
}

void cap_nhat_matrix(double S[], double tmp[], int n){
    for(int i = 0 ; i < n; i++)
        S[i] = tmp[i];
}

void nhan_ma_tran_vector(double P[][4], double S0[], double ket_qua[], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            ket_qua[i] += P[j][i] * S0[j];
        }
    }
}

void Chuoi_Markov(double P[][4], double S0[4], int n, int expo = 3){
    double ket_qua_dau[n] = {0};
    nhan_ma_tran_vector(P, S0, ket_qua_dau, n);
    cout << "Buoc lap thu 1: "; in_vector(ket_qua_dau, n);
    cout << "Xac suat nguoi do tro nen giau co sau 1 buoc thoi gian la: " << ket_qua_dau[0] << endl;
    cout << "-----------------------------------------------------------\n";
    for(int i = 2 ; i <= expo; i++){
        double tam[n] = {0};
        nhan_ma_tran_vector(P, ket_qua_dau, tam, n);
        cout << "Buoc lap thu " << i << ": ";
        in_vector(tam, n);
        cout << "Xac suat nguoi do tro nen giau co sau " << i << " buoc thoi gian la: " << tam[0] << endl;
        cout << "-----------------------------------------------------------\n";
        cap_nhat_matrix(ket_qua_dau, tam, n);
    }
}

int main(){
    int expo;
    int n = 4;
    double P[4][4] = {
            {0, 0.75, 0.2, 0.05},
            {0.05, 0.2, 0.3, 0.45},
            {0.1, 0.4, 0.3, 0.2},
            {0, 0.15, 0.3, 0.55},
    };
    cout << "Ma tran chuyen doi P: \n";
    in_ma_tran(P, n);
    cout << "Nhap so buoc lap: "; cin >> expo;
    double S0[4] = {0, 1, 0, 0};
    Chuoi_Markov(P, S0, n, expo);
}



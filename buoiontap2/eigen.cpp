
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<vector>
#define PI 3.1415926535898
using namespace std;
typedef float mt[20][20];

float x1, x2, x3;

void input(mt a, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%f", &a[i][j]);
		}
	}
}

void output(mt a, int n, int m){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++) printf("%0.3f ", a[i][j]);
		printf("\n");
	}
}

void copyArr(mt des, mt source, int row, int col) {
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			des[i][j] = source[i][j];
}

void multipleArr(mt a, mt b, int n, int x){
	mt c;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			c[i][j] = 0;
			for(int k = 0; k < n; k++) c[i][j] += a[i][k]*b[k][j];
		}
	}
	if(x == 1) copyArr(a, c, n, n);
	else copyArr(b, c, n, n);
}

void vec_rieng(mt a, float b[], int n, int m){
	mt c;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < 1; j++){
			c[i][j] = 0;
			for(int k = 0; k < n; k++) c[i][j] += a[i][k]*b[k];
		}
	}
	for(int i = 0; i < n; i++) b[i] = c[i][0];
}

void init(mt a, mt m_,mt m, int x){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(i == x) {
				m_[i][j] = a[i+1][j];
				if(j == x) m[i][j] = (float)1/m_[i][j];
				else m[i][j] = -m_[i][j]/a[x+1][x];
			}
			else if(i == j){
				m_[i][j] = 1;
				m[i][j] = 1;
			}
			else{
				m[i][j] = 0;
				m_[i][j] = 0;
			}
		}
	}
}

float* quadratic(float a, float b, float c, int &count) {
	float* result;
	float delta = b*b - 4*a*c;
    if(delta < 0) {
        result = new float[0];
    } else if(delta == 0) {
    	count = 1;
        result = new float[1];
		x1 = -b/(2*a);
		result[0] = x1;
    } else {
    	count = 2;
    	result = new float[2];
        x1 = (-b + sqrt(delta))/(2*a);
        x2 = (-b - sqrt(delta))/(2*a);
        result[0] = x1;
        result[1] = x2;
    }
    return result;
}

float* cubic(float a, float b, float c, float d, int &count) {
	float* result;
	float dt, k;
	dt = pow(b,2)-3*a*c;
	k = (9*a*b*c-2*pow(b,3)-27*pow(a,2)*d)/(2*sqrt(pow(fabs(dt),3)));
	if(dt > 0){
		if(fabs(k) <= 1){
			count = 3;
			result = new float[3];
			x1 = (2*sqrt(dt)*cos(acos(k)/3)-b)/(3*a);
    	  	x2 = (2*sqrt(dt)*cos(acos(k)/3-(2*PI/3))-b)/(3*a);
      		x3 = (2*sqrt(dt)*cos(acos(k)/3+(2*PI/3))-b)/(3*a);
      		result = new float[3];
      		result[0] = x1;
      		result[1] = x2;
      		result[2] = x3;
		}
		else if(fabs(k) > 1){
			count = 1;
			x1 = ((sqrt(dt)*fabs(k))/(3*a*k))
				*(pow((fabs(k)+sqrt(pow(k,2)-1)),1.0/3)
				+ pow((fabs(k)-sqrt(pow(k,2)-1)),1.0/3))-(b/(3*a));
			result = new float[1];
			result[0] = x1;
		}
	}
	else if(dt == 0){
		count = 1;
		x1 = (-b-pow(-(pow(b,3)-27*a*a*d),1.0/3))/(3*a);
		result = new float[1];
		result[0] = x1;
	}
	else {
		count = 1;
		x1 = (sqrt(fabs(dt))/(3*a))*(pow((k+sqrt(k*k+1)),1.0/3)
			-pow(-(k-sqrt(k*k+1)),1.0/3))-(b/(3*a));
		result = new float[1];
		result[0] = x1;
	}
	return result;
}

double f(double x, double a, double b, double c, double d, double e) {
    return a * pow(x, 4) + b * pow(x, 3) + c * pow(x, 2) + d * x + e;
}

double df(double x, double a, double b, double c, double d) {
    return 4 * a * pow(x, 3) + 3 * b * pow(x, 2) + 2 * c * x + d;
}

vector<double> newtonRaphson(double a, double b, double c, 
	double d, double e, double x0, int maxIter, double tol) {
    vector<double> roots;
    double x = x0;
    for (int i = 0; i < maxIter; ++i) {
        double fx = f(x, a, b, c, d, e);
        double dfx = df(x, a, b, c, d);
        if (fabs(dfx) < 1e-6) {
            break;
        }
        double x_next = x - fx / dfx;
        if (fabs(x_next - x) < tol) {
            roots.push_back(x_next);
            return roots;
        }
        x = x_next;
    }
    return roots;
}

bool isUnique(vector<double>& roots, double newRoot, double tol) {
    for (int i = 0; i < roots.size(); i++) {
        if(fabs(roots[i] - newRoot) < tol) {
        	return false;	
        }
    }
    return true;
}

float* quartric(float a, float b, float c, float d, float e, int &count) {
	double x0 = 0;
    int maxIter = 100;
    double tol = 1e-6;

    vector<double> realRoots;
    for (double i = -100; i <= 100; i += 0.1) {
        vector<double> roots = newtonRaphson(a, b, c, d, e, i, maxIter, tol);
		for (int i = 0; i < roots.size(); i++) {
        	double root = roots[i];
            if (isUnique(realRoots, root, tol)) {
            	count++;
                realRoots.push_back(root);
            }
        }
    }
    float* result = new float[count];
    for (int i = 0; i < count; i++) {
    	result[i] = realRoots[i];
    }
    return result;
}

void findEngine(mt a, const int n) {
	mt m_, m1, m;
	int t = n - 1;
	while(t--){
		init(a, m_, m1, t);
		multipleArr(m_,a,n,2);
		multipleArr(a,m1,n,1);
		if(t + 1 == n-1) copyArr(m, m1, n, n);
		else multipleArr(m,m1,n,1);
	}
	float* coefficient = new float[n];
	for (int i = 0; i < n; i++) {
		coefficient[i] = -a[0][i];
	}
	int count = 0;
	float* engine;
	switch(n) {
		case 2:
			engine = quadratic(1, coefficient[0], coefficient[1], count);
			break;
		case 3:
			engine = cubic(1, coefficient[0], coefficient[1], 
				coefficient[2], count);
			break;
		case 4:
			engine = quartric(1, coefficient[0], coefficient[1], 
				coefficient[2], coefficient[3], count);
			break;
	}
	
	printf("Co %d gia tri rieng: ", count);
	for (int i = 0; i < count; i++) {
		printf("%f ", engine[i]);
	}
	printf("\n");
	
	float y[n][n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			y[i][j] = pow(engine[i], n - j - 1);
		}
	}
	mt vectors;
	for (int i = 0; i < n; i++) {
		float row[n];
		for (int j = 0; j < n; j++) {
			row[j] = y[i][j];
		}
		vec_rieng(m,row,n,1);
		printf("Vector rieng: ");
		for (int j = 0; j < n; j++) {
			printf("%f ", row[j]);
			vectors[j][i] = row[j];
		}
		printf("\n");
	}
	if (count == n) {
		printf("\n\nP:\n");
		output(vectors, n, n);
		printf("A:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) printf("%0.3f ", engine[i]);
				else printf("0.000 ");
			}
			printf("\n");
		}
	}
}

int main(){
	int n;
	printf("Hay nhap cap cua ma tran: "); scanf("%d", &n);
	printf("Nhap ma tran:\n");
	mt a;
	input(a, n);
	findEngine(a, n);
}

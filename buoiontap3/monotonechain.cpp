#include <iostream>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector> 

using namespace std;

const int MAX_POINTS = 100; 
std::ostream& operator<<(std::ostream& os, const std::pair<int, int>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}
void swap(int A[2], int B[2]) {
    int temp[2];
    temp[0] = A[0];
    temp[1] = A[1];

    A[0] = B[0];
    A[1] = B[1];

    B[0] = temp[0];
    B[1] = temp[1];
}

int partition(int A[][2], int low, int high) {
    int pivot[2] = {A[high][0], A[high][1]};  
    int i = low - 1;  

    for (int j = low; j < high; j++) {
        if (A[j][0] < pivot[0] || (A[j][0] == pivot[0] && A[j][1] < pivot[1])) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[high]); 
    return i + 1;
}

void quick_sort(int A[][2], int low, int high) {
    if (low < high) {
        int pi = partition(A, low, high);  
        quick_sort(A, low, pi - 1);  
        quick_sort(A, pi + 1, high);  
    }
}

long long cross_product(int O[2], int A[2], int B[2]) {
    return (A[0] - O[0]) * (B[1] - O[1]) - (A[1] - O[1]) * (B[0] - O[0]);
}

int convex_hull(int A[][2], int n, int ans[][2]) {
    int k = 0;

    if (n <= 3) {
        for (int i = 0; i < n; ++i) {
            ans[i][0] = A[i][0];
            ans[i][1] = A[i][1];
        }
        return n;
    }

    quick_sort(A, 0, n - 1);

    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross_product(ans[k - 2], ans[k - 1], A[i]) <= 0) {
            k--;  
        }
        ans[k][0] = A[i][0];
        ans[k][1] = A[i][1];
        k++;
    }

    for (int i = n - 1, t = k + 1; i >= 0; --i) {
        while (k >= t && cross_product(ans[k - 2], ans[k - 1], A[i]) <= 0) {
            k--;  
        }
        ans[k][0] = A[i][0];
        ans[k][1] = A[i][1];
        k++;
    }

    return k - 1;
}

double calculate_area(int hull[][2], int hull_size) {
    double area = 0;

    for (int i = 0; i < hull_size; ++i) {
        int x1 = hull[i][0];
        int y1 = hull[i][1];
        int x2 = hull[(i + 1) % hull_size][0];  
        int y2 = hull[(i + 1) % hull_size][1];
        area += x1 * y2 - y1 * x2;
    }

    return fabs(area) / 2.0;  
}

vector<int> closestPair(vector<pair<int, int>> coordinates, int n) {
    sort(coordinates.begin(), coordinates.end());


    set<pair<int, int>> s;

    int squaredDistance = INT_MAX; 
    int j = 0;
    std::vector<int> closestPoints(4); 

    for (int i=0;i<n;++i) {
        int D = ceil(sqrt(squaredDistance));
        while (coordinates[i].first - coordinates[j].first >= D) {
            s.erase({coordinates[j].second, coordinates[j].first});
            j += 1;
        }

        auto start=s.lower_bound({coordinates[i].second - D, coordinates[i].first});
        auto end=s.upper_bound({coordinates[i].second + D, coordinates[i].first});

        for (auto it = start; it != end; ++it) {
            int dx = coordinates[i].first - it->second;
            int dy = coordinates[i].second - it->first;
            int currentDistance = dx *dx + dy * dy;
            if (currentDistance < squaredDistance) {
                squaredDistance = currentDistance;
                closestPoints[0] = coordinates[i].first;   
                closestPoints[1] = coordinates[i].second;  
                closestPoints[2] = it->second;             
                closestPoints[3] = it->first;              
            }
        }

        s.insert({coordinates[i].second, coordinates[i].first});
    }

    return closestPoints; 
}
vector<pair<int, int>> convertToVector(int coordinates[][2], int n) {
    vector<pair<int, int>> result;
    for (int i = 0; i < n; ++i) {
        result.push_back({coordinates[i][0], coordinates[i][1]});
    }
    return result;
}

int main() {
    int A[MAX_POINTS][2] = {};  
    int ans[MAX_POINTS][2] = {};  
    int n = 15;  

    srand(time(0));

   cout << "Cac toa do la (x, y):\n";
    for (int i = 0; i < n; ++i) {
        A[i][0] = rand() % 15 + 1;  
        A[i][1] = rand() % 15 + 1;  
        cout << "(" << A[i][0] << ", " << A[i][1] << ")\n";
    }

    int hull_size = convex_hull(A, n, ans);

    cout << "Cac diem thuoc bao loi la :\n";
    for (int i = 0; i < hull_size; ++i) {
        cout << "(" << ans[i][0] << ", " << ans[i][1] << ")\n";
    }
    
    // Tính di?n tích c?a bao l?i
    double area = calculate_area(ans, hull_size);
    cout << "Dien tich cua bao loi la: " << area << endl;
    
	vector<pair<int, int>> P = convertToVector(ans, hull_size);
    vector<int> closestPoints = closestPair(P, hull_size);

    int distance = (closestPoints[0] -closestPoints[2])* (closestPoints[0] -closestPoints[2])+(closestPoints[1] - closestPoints[3])*(closestPoints[1] - closestPoints[3]); 
    cout << "The smallest distance is " << sqrt(distance) << endl;
    cout << "The closest points are: (" << closestPoints[0] << ", " << closestPoints[1] << ") and ("
              << closestPoints[2] << ", " << closestPoints[3] << ")" << endl;

    return 0;
}

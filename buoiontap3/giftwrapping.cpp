#include <iostream>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector> 
using namespace std;

int orientation(int p[], int q[], int r[]) {
    int val = (q[1] - p[1]) * (r[0] - q[0]) - 
              (q[0] - p[0]) * (r[1] - q[1]);
 
    if (val == 0) return 0;  
    return (val > 0)? 1: 2; 
}
 
int convexHull(int points[][2], int n, int ans[][2]) {
    if (n < 3) return 0;
 
    vector<int*> hull;
 
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i][0] < points[l][0])
            l = i;
 
    int p = l, q;
    do {
        hull.push_back(points[p]);
 
        q = (p+1) % n;
        for (int i = 0; i < n; i++) {
           if (orientation(points[p], points[i], points[q]) == 2)
               q = i;
        }
 
        p = q;
 
    } while (p != l); 

    for (int i = 0; i < hull.size(); ++i) {
        ans[i][0] = hull[i][0];
        ans[i][1] = hull[i][1];
    }

    return hull.size();  
}

vector<int> closestPair(vector<pair<int, int>> coordinates, int n) {
    sort(coordinates.begin(), coordinates.end());

    set<pair<int, int>> s;

    int squaredDistance = INT_MAX; 
    int j = 0;
    std::vector<int> closestPoints(4); 

    for (int i = 0; i < n; ++i) {
        int D = ceil(sqrt(squaredDistance));
        while (coordinates[i].first - coordinates[j].first >= D) {
            s.erase({coordinates[j].second, coordinates[j].first});
            j += 1;
        }

        auto start = s.lower_bound({coordinates[i].second - D, coordinates[i].first});
        auto end = s.upper_bound({coordinates[i].second + D, coordinates[i].first});

        for (auto it = start; it != end; ++it) {
            int dx = coordinates[i].first - it->second;
            int dy = coordinates[i].second - it->first;
            int currentDistance = dx * dx + dy * dy;  // s?a l?i phép tính kho?ng cách
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

const int MAX_POINTS = 100;  

int main() {
    int A[MAX_POINTS][2] = {};  
    int ans[MAX_POINTS][2] = {};  
    int n;  
    cout << "Nhap so luong diem: ";
    cin >> n;

    srand(time(0));

    cout << "Cac toa do la (x, y):\n";
    for (int i = 0; i < n; ++i) {
        A[i][0] = rand() % 11;  
        A[i][1] = rand() % 11;  
        cout << "(" << A[i][0] << ", " << A[i][1] << ")\n";
    }

    int hull_size = convexHull(A, n, ans);

    cout << "Cac diem thuoc bao loi la :\n";
    for (int i = 0; i < hull_size; ++i) {
        cout << "(" << ans[i][0] << ", " << ans[i][1] << ")\n";
    }

    vector<pair<int, int>> P = convertToVector(ans, hull_size);

    vector<int> closestPoints = closestPair(P, hull_size);

    int distance = (closestPoints[0] - closestPoints[2]) * (closestPoints[0] - closestPoints[2]) +
                   (closestPoints[1] - closestPoints[3]) * (closestPoints[1] - closestPoints[3]);

    cout << "The smallest distance is " << sqrt(distance) << endl;
    cout << "The closest points are: (" << closestPoints[0] << ", " << closestPoints[1] << ") and ("
              << closestPoints[2] << ", " << closestPoints[3] << ")" << endl;

    return 0;
}

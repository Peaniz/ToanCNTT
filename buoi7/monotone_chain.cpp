#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    int x, y;
};

// Hàm tính tích chéo giữa ba điểm
int crossProduct(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// Thuật toán Monotone Chain để tìm Convex Hull
vector<Point> monotoneChain(vector<Point>& points) {
    sort(points.begin(), points.end(), [](Point a, Point b) {
        return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    });

    vector<Point> lowerHull, upperHull;

    // Tạo Lower Hull
    for (const auto& p : points) {
        while (lowerHull.size() >= 2 &&
               crossProduct(lowerHull[lowerHull.size() - 2], lowerHull.back(), p) <= 0) {
            lowerHull.pop_back();
        }
        lowerHull.push_back(p);
    }

    // Tạo Upper Hull
    for (int i = points.size() - 1; i >= 0; --i) {
        while (upperHull.size() >= 2 &&
               crossProduct(upperHull[upperHull.size() - 2], upperHull.back(), points[i]) <= 0) {
            upperHull.pop_back();
        }
        upperHull.push_back(points[i]);
    }

    lowerHull.pop_back();  // Bỏ điểm trùng
    upperHull.pop_back();  // Bỏ điểm trùng

    // Kết hợp hai Hull thành một
    lowerHull.insert(lowerHull.end(), upperHull.begin(), upperHull.end());

    return lowerHull;
}

// Hàm tính diện tích đa giác bằng công thức Shoelace
double polygonArea(const vector<Point>& hull) {
    int n = hull.size();
    double area = 0.0;

    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;  // Điểm tiếp theo (vòng lại nếu cần)
        area += hull[i].x * hull[j].y - hull[i].y * hull[j].x;
    }

    return abs(area) / 2.0;
}

// Hàm main
int main() {
    int N = 15;  // Số điểm ngẫu nhiên
    vector<Point> points(N);

    // Sinh các điểm ngẫu nhiên
    srand(time(0));
    for (int i = 0; i < N; ++i) {
        points[i].x = rand() % 116;
        points[i].y = rand() % 116;
        cout << "Point " << i + 1 << ": (" << points[i].x << ", " << points[i].y << ")\n";
    }

    // Tìm Convex Hull bằng Monotone Chain
    vector<Point> hull = monotoneChain(points);

    // In các điểm trên Hull
    cout << "\nConvex Hull:\n";
    for (const auto& p : hull) {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }

    // Tính diện tích của Convex Hull
    double area = polygonArea(hull);
    cout << "\nDiện tích của Convex Hull: " << area << endl;

    return 0;
}
D
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

struct Point {
    int x, y;
};

int crossProduct(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int distanceSquared(Point a, Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool compare(Point a, Point b, Point origin) {
    int cp = crossProduct(origin, a, b);
    if (cp == 0) {
        return distanceSquared(origin, a) < distanceSquared(origin, b);
    }
    return cp > 0;
}

vector<Point> grahamScan(vector<Point>& points) {
    Point origin = *min_element(points.begin(), points.end(), [](Point a, Point b) {
        return (a.y < b.y) || (a.y == b.y && a.x < b.x);
    });

    sort(points.begin(), points.end(), [&](Point a, Point b) {
        return compare(a, b, origin);
    });

    stack<Point> hull;
    hull.push(points[0]);
    hull.push(points[1]);

    for (int i = 2; i < points.size(); ++i) {
        while (hull.size() >= 2) {
            Point top = hull.top(); hull.pop();
            Point nextToTop = hull.top();
            if (crossProduct(nextToTop, top, points[i]) > 0) {
                hull.push(top);
                break;
            }
        }
        hull.push(points[i]);
    }

    vector<Point> result;
    while (!hull.empty()) {
        result.push_back(hull.top());
        hull.pop();
    }

    return result;
}
double polygonArea(const vector<Point>& hull) {
    int n = hull.size();
    double area = 0.0;

    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;  
        area += hull[i].x * hull[j].y - hull[i].y * hull[j].x;
    }

    return abs(area) / 2.0;
}

int main() {
    int N = 15;
    vector<Point> points(N);

    srand(time(0));
    for (int i = 0; i < N; ++i) {
        points[i].x = rand() % 116;
        points[i].y = rand() % 116;
        cout << "Point " << i + 1 << ": (" << points[i].x << ", " << points[i].y << ")\n";
    }

    vector<Point> hull = grahamScan(points);

    cout << "\nConvex Hull:\n";
    for (const auto& p : hull) {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }

    double area = polygonArea(hull);
    cout << "\nDiện tích của Convex Hull: " << area << endl;

    return 0;
}

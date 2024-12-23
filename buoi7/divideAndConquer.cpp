#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>  

using namespace std;

struct Point {
    int x, y;
};

int crossProduct(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

void addPointToHull(vector<Point>& hull, Point p) {
    while (hull.size() >= 2 && crossProduct(hull[hull.size() - 2], hull.back(), p) <= 0) {
        hull.pop_back();
    }
    hull.push_back(p);
}

vector<Point> divideAndConquer(vector<Point>& points) {
    sort(points.begin(), points.end(), [](Point a, Point b) {
        return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    });

    vector<Point> lowerHull, upperHull;

    for (const auto& p : points) {
        addPointToHull(lowerHull, p);
    }
    for (int i = points.size() - 1; i >= 0; --i) {
        addPointToHull(upperHull, points[i]);
    }

    lowerHull.pop_back();
    upperHull.pop_back();

    lowerHull.insert(lowerHull.end(), upperHull.begin(), upperHull.end());

    return lowerHull;
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

    vector<Point> hull = divideAndConquer(points);

    cout << "\nConvex Hull:\n";
    for (const auto& p : hull) {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }
 
    double area = polygonArea(hull);
    cout << "\nDiện tích của Convex Hull: " << area << endl;

    return 0;
}

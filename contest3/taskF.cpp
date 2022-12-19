#include <iostream>
#include <vector>
#include <algorithm>


struct Point {
    long long x, y;
    bool operator>(Point other) {
        if (x == other.x) {
            return y > other.y;
        }
        return x > other.x;
    }
};

std::istream& operator>>(std::istream& in, Point &p) {
    in >> p.x >> p.y;
    return in;
}

long long cross_prod(Point a, Point b, Point c, Point d) {
    long long x = b.x - a.x;
    long long y = b.y - a.y;
    long long x_ = d.x - c.x;
    long long y_ = d.y - c.y;
    long long prod = (x * y_) - (y * x_);
    if (prod == 0) {
        return 0;
    }
    return (prod) / abs(prod);
}


struct cmp {
    Point start;
    cmp(Point start) : start(start) {}
    bool operator()(Point a, Point b) {
        long long sign = cross_prod(start, a, start, b);
        if (sign == 0) {
            long long dist1 = (a.x - start.x) * (a.x - start.x) + (a.y - start.y) * (a.y - start.y);
            long long dist2 = (b.x - start.x) * (b.x - start.x) + (b.y - start.y) * (b.y - start.y);
            return dist1 < dist2;
        }
        return sign > 0;
    }
};

std::vector<Point> findConvexHull(std::vector<Point>& points) {
    size_t n = points.size();
    Point start = { INT_MAX, INT_MAX };
    int index = 0;
    for (size_t i = 0; i < n; ++i) {
        if (start > points[i]) {
            index = i;
            start = points[i];
        }
    }
    std::swap(points[0], points[index]);
    std::sort(points.begin() + 1, points.end(), cmp(points[0]));
    std::vector<Point> hull;
    hull.push_back(start);
    for (size_t i = 1; i < n; ++i) {
        while (hull.size() >= 2) {
            long long sign = cross_prod(hull[hull.size() - 2], hull.back(), hull.back(), points[i]);
            if (sign <= 0) {
                hull.pop_back();
            }
            else {
                break;
            }
        }
        hull.push_back(points[i]);
    }
    return hull;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<Point> points(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> points[i];
    }
    std::vector<Point> hull = findConvexHull(points);
    std::cout << hull.size() << '\n';
    for (const auto& p : hull) {
        std::cout << p.x << ' ' << p.y << '\n';
    }
}

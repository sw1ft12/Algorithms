#include <iostream>

struct Point {
    int x, y;
};

std::istream& operator>>(std::istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

int area(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool inter(int a, int b, int c, int d) {
    if (a > b) {
        std::swap(a, b);
    }
    if (c > d) {
        std::swap(c, d);
    }
    return std::max(a, c) <= std::min(b, d);
}

bool segmentIntersect(Point a, Point b, Point c, Point d) {
    return inter(a.x, b.x, c.x, d.x) && inter(a.y, b.y, c.y, d.y)
        && area(a, b, c) * area(a, b, d) <= 0
        && area(c, d, a) * area(c, d, b) <= 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);
    Point a, b, c, d;
    std::cin >> a >> b >> c >> d;
    std::cout << (segmentIntersect(a, b, c, d) ? "YES" : "NO");
}

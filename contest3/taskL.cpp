#include <iostream>
#include <algorithm>

const long long N = 100005;

struct Point {
    long long x, y;
    Point(long long x = 0, long long y = 0) :x(x), y(y) {}
    bool operator < (const Point& b) const {
        if (y != b.y) return y < b.y;
        return x < b.x;
    }
    Point operator + (const Point& b) {
        return Point(x + b.x, y + b.y);
    }
    Point operator - (const Point& b) {
        return Point(x - b.x, y - b.y);
    }
};

int n;
int sz[N], d[3];
Point points[3][N], v[3][N], a[N * 3], b[N * 3], c;

int g(const Point& a) {
    return a.y > 0 || (a.y == 0 && a.x >= 0);
}

bool cmp(const Point& a, const Point& b) {
    int s1 = g(a), s2 = g(b);
    if (s1 != s2) return s1 > s2;
    return a.x * b.y - a.y * b.x > 0;
}

long long cross_prod(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

long long len(const Point& a) {
    return a.x * a.x + a.y * a.y;
}

bool func(Point v) {
    if (v < c) return 0;
    v = v - c;
    int l = 0, r = n - 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (cross_prod(a[mid], v) >= 0) l = mid + 1;
        else r = mid - 1;
    }
    --l;
    if (l == n - 1) {
        return  cross_prod(v, a[l]) == 0 && len(v) <= len(a[l]);
    }
    return cross_prod(a[l + 1] - a[l], v - a[l]) >= 0;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    n = 0;
    c = Point(0, 0);
    for (size_t i = 0; i < 3; ++i) {
        std::cin >> sz[i];
        for (size_t j = 0; j < sz[i]; ++j) {
            std::cin >> points[i][j].x >> points[i][j].y;
        }
        points[i][sz[i]] = points[i][0];
        for (size_t j = 0; j < sz[i]; ++j) {
            b[n++] = v[i][j] = points[i][j + 1] - points[i][j];
        }
        d[i] = 0;
        for (size_t j = 1; j < sz[i]; ++j)
            if (points[i][j] < points[i][d[i]]) {
                d[i] = j;
            }
        c = c + points[i][d[i]];
    }
    std::sort(b, b + n, cmp);
    int k = 0;
    for (size_t i = 0; i < n; ++i) {
        int j;
        for (j = i + 1; j < n && cross_prod(b[i], b[j]) == 0; ++j);
        b[k] = b[i];
        for (size_t e = i + 1; e < j; ++e)
            b[k] = b[k] + b[e];
        ++k;
        i = j - 1;
    }
    n = k;
    for (size_t i = 1; i <= n; ++i) {
        a[i] = a[i - 1] + b[i - 1];
    }
    int m;
    std::cin >> m;
    for(size_t i = 0; i < m; ++i) {
        Point p;
        std::cin >> p.x >> p.y;
        p.x *= 3; p.y *= 3;
        std::cout << (func(p) ? "YES" : "NO") << '\n';
    }
}

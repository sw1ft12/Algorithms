#include <iostream>
#include <vector>
#include <algorithm>


struct Point {
    long long x = 0, y = 0;
    Point() = default;
    Point(long long x, long long y) :x(x), y(y) {}
    bool operator<(Point other) const {
        if (y != other.y) return y < other.y;
        return x < other.x;
    }
    Point operator+(Point other) {
        return Point(x + other.x, y + other.y);
    }
    Point operator-(Point other) {
        return Point(x - other.x, y - other.y);
    }
};

std::istream& operator>>(std::istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

struct cmp {
    bool operator()(Point a, Point b) {
        bool s1 = a.y > 0 || (a.y == 0 && a.x >= 0);
        bool s2 = b.y > 0 || (b.y == 0 && b.x >= 0);
        if (s1 != s2) {
            return s1 > s2;
        }
        return a.x * b.y - a.y * b.x > 0;
    }
};

long long cross_prod(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

long long dist(Point a) {
    return a.x * a.x + a.y * a.y;
}

std::vector<Point> findMinkowskiSum(std::vector<std::vector<Point>> &polygons, Point& a) {
    std::vector<Point> diff;
    int cnt = 0;
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < polygons[i].size() - 1; ++j) {
            diff.emplace_back(polygons[i][j + 1] - polygons[i][j]);
            ++cnt;
        }
        int index = 0;
        for (size_t j = 1; j < polygons[i].size() - 1; ++j) {
            if (polygons[i][j] < polygons[i][index]) {
                index = j;
            }
        }
        a = a + polygons[i][index];
    }
    std::sort(diff.begin(), diff.end(), cmp());
    int k = 0;
    for (size_t i = 0; i < cnt; ++i) {
        int j = i + 1;
        while (j < cnt && cross_prod(diff[i], diff[j]) == 0) {
            ++j;
        }
        diff[k] = diff[i];
        for (size_t e = i + 1; e < j; ++e) {
            diff[k] = diff[k] + diff[e];
        }
        ++k;
        i = j - 1;
    }
    cnt = k;
    std::vector<Point> sum(cnt + 1);
    for (size_t i = 1; i <= cnt; ++i) {
        sum[i] = sum[i - 1] + diff[i - 1];
    }
    return sum;
}

bool isValidPoint(std::vector<Point> &sum, Point a, Point b) {
    if (a < b) {
        return false;
    }
    a = a - b;
    int l = 0, r = sum.size() - 2;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (cross_prod(sum[mid], a) >= 0) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    --l;
    if (l == sum.size() - 2) {
        return  cross_prod(a, sum[l]) == 0 && dist(a) <= dist(sum[l]);
    }
    return cross_prod(sum[l + 1] - sum[l], a - sum[l]) >= 0;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::vector<std::vector<Point>> polygons(3);
    for (size_t i = 0; i < 3; ++i) {
        int n;
        std::cin >> n;
        polygons[i] = std::vector<Point>(n + 1);
        for (size_t j = 0; j < n; ++j) {
            std::cin >> polygons[i][j];
        }
        polygons[i][n] = polygons[i][0];
    }
    Point a;
    std::vector<Point> sum = findMinkowskiSum(polygons, a);
    int q;
    std::cin >> q;
    for (size_t i = 0; i < q; ++i) {
        Point p;
        std::cin >> p.x >> p.y;
        p.x *= 3; p.y *= 3;
        std::cout << (isValidPoint(sum, p, a) ? "YES" : "NO") << '\n';
    }
}

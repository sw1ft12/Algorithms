#include <iostream>
#include <vector>
#include <algorithm>


using pll = std::pair<long long, long long>;


long long cross_prod(const pll& a, const pll& b, const pll& c, const pll& d) {
    long long x = b.first - a.first;
    long long y = b.second - a.second;
    long long x_ = d.first - c.first;
    long long y_ = d.second - c.second;
    long long prod = (x * y_) - (y * x_);
    if (prod == 0) {
        return 0;
    }
    return (prod) / abs(prod);
}


struct cmp {
    pll start;
    cmp(const pll &start) : start(start){}
    bool operator()(const pll& a, const pll& b) {
        long long sign = cross_prod(start, a, start, b);
        if (sign == 0) {
            long long dist1 = (a.first - start.first) * (a.first - start.first) + (a.second - start.second) * (a.second - start.second);
            long long dist2 = (b.first - start.first) * (b.first - start.first) + (b.second - start.second) * (b.second - start.second);
            return dist1 < dist2;
        }
        return sign > 0;
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<pll> point(n);
    pll start = { INT_MAX, INT_MAX };
    int index = 0;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> point[i].first >> point[i].second;
        if (start > point[i]) {
            index = i;
            start = point[i];
        }
    }

    std::swap(point[0], point[index]);
    std::sort(point.begin() + 1, point.end(), cmp(point[0]));
    std::vector<pll> hull;
    hull.push_back(start);
    for (size_t i = 1; i < n; ++i) {
        while (hull.size() >= 2) {
            long long sign = cross_prod(hull[hull.size() - 2], hull.back(), hull.back(), point[i]);
            if (sign <= 0) {
                hull.pop_back();
            }
            else {
                break;
            }
        }
        hull.push_back(point[i]);
    }

    std::cout << hull.size() << '\n';
    for (const auto& p : hull) {
        std::cout << p.first << ' ' << p.second << '\n';
    }
}

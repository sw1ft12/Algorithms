#include <iostream>


int area(std::pair<int, int> a, std::pair<int, int> b, std::pair<int, int> c) {
    return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);
    std::pair<int, int> a, b, c, d;
    std::cin >> a.first >> a.second;
    std::cin >> b.first >> b.second;
    std::cin >> c.first >> c.second;
    std::cin >> d.first >> d.second;
    std::cout << (inter(a.first, b.first, c.first, d.first) && inter(a.second, b.second, c.second, d.second)
        && area(a, b, c) * area(a, b, d) <= 0
        && area(c, d, a) * area(c, d, b) <= 0 ? "YES" : "NO");
}

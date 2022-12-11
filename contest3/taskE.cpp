#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>


struct Point {
	long long x, y;
};


long long cross_prod(const Point& a, const Point& b, const Point& c, const Point& d) {
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

double dist(Point a, Point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool isOnSegment(Point a, Point b, Point c) {
	double dist1 = dist(a, b);
	double dist2 = dist(a, c);
	double dist3 = dist(b, c);
	return dist1 == dist2 + dist3;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	std::vector<Point> polygon(n);

	for (size_t i = 0; i < n; ++i) {
		std::cin >> polygon[i].x >> polygon[i].y;
	}

	polygon.push_back(polygon[0]);
	std::vector<Point> points(m);
	std::vector<bool> isBoundary(m);
	for (size_t i = 0; i < m; ++i) {
		std::cin >> points[i].x >> points[i].y;
		for (size_t j = 0; j < n; ++j) {
			if (isOnSegment(polygon[j], polygon[j + 1], points[i])) {
				isBoundary[i] = true;
			}
		}
	}

	for (size_t i = 0; i < m; ++i) {
		long long cnt = 0;
		for (size_t j = 0; j < n; ++j) {
			Point lower = polygon[j];
			Point upper = polygon[j + 1];
			if (lower.y > upper.y) {
				std::swap(lower, upper);
			}
			if (lower.y > points[i].y || upper.y <= points[i].y) {
				continue;
			}
			long long sign = cross_prod(lower, points[i], lower, upper);
			if(sign <= 0){
				++cnt;
			}
		}
		if (isBoundary[i]) {
			std::cout << "BOUNDARY\n";
			continue;
		}
		if (cnt % 2 != 0) {
			std::cout << "INSIDE\n";
		}
		else {
			std::cout << "OUTSIDE\n";
		}
	}
}

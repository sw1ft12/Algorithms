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

int isInPolygon(const std::vector<Point>& polygon, Point p) {
	size_t n = polygon.size() - 1;
	long long cnt = 0;
	for (size_t j = 0; j < n; ++j) {
		if (isOnSegment(polygon[j], polygon[j + 1], p)) {
			return 3;
		}
		Point lower = polygon[j];
		Point upper = polygon[j + 1];
		if (lower.y > upper.y) {
			std::swap(lower, upper);
		}
		if (lower.y > p.y || upper.y <= p.y) {
			continue;
		}
		long long sign = cross_prod(lower, p, lower, upper);
		if (sign <= 0) {
			++cnt;
		}
	}
	return cnt % 2;
}


int main() {
	int n, m;
	std::cin >> n >> m;
	std::vector<Point> polygon(n);

	for (size_t i = 0; i < n; ++i) {
		std::cin >> polygon[i].x >> polygon[i].y;
	}

	polygon.push_back(polygon[0]);
	int x, y;
	for (size_t i = 0; i < m; ++i) {
		std::cin >> x >> y;
		Point p = { x , y };
		int res = isInPolygon(polygon, p);
		if (res == 3) {
			std::cout << "BOUNDARY\n";
		}
		else if (res == 1) {
			std::cout << "INSIDE\n";
		}
		else {
			std::cout << "OUTSIDE\n";
		}
	}
}

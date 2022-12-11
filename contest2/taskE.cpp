#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>


using cdouble = std::complex<double>;
const double PI = 3.14159265358979323846;


void fft(std::vector<cdouble>& a) {
	size_t n = a.size();
	if (n == 1) {
		return;
	}

	std::vector<cdouble> a0;
	std::vector<cdouble> a1;

	for (size_t i = 0; i < n; ++i){
		if (i % 2 == 0) {
			a0.push_back(a[i]);
		}
		else {
			a1.push_back(a[i]);
		}
	}
	fft(a0);
	fft(a1);

	double angle = 2 * PI / n;
	cdouble w(1), w_n(cos(angle), sin(angle));

	for (size_t i = 0; i < n; ++i) {
		a[i] = a0[i % (n / 2)] + w * a1[i % (n / 2)];
		w *= w_n;
	}
}


void inversefft(std::vector<cdouble>& a) {
	fft(a);
	size_t n = a.size();
	for (size_t i = 0; i < n; ++i) {
		a[i] /= n;
	}
	std::reverse(a.begin() + 1, a.end());
}


std::vector<int> mul(const std::vector<int>& a, const std::vector<int>& b) {
	std::vector<cdouble> a_(a.begin(), a.end()), b_(b.begin(), b.end());
	size_t n = 1;
	while (n < std::max(a.size(), b.size())) {
		n <<= 1;
	}
	n <<= 1;
	a_.resize(n);
	b_.resize(n);

	fft(a_);
	fft(b_);
	for (size_t i = 0; i < n; ++i) {
		a_[i] *= b_[i];
	}
	inversefft(a_);

	int deg = a.size() + b.size() - 2;
	std::vector<int> res(deg + 1);
	for (size_t i = 0; i <= deg; ++i) {
		if (a_[i].real() > 0) {
			res[i] = static_cast<int>(a_[i].real() + 0.5);
		}
		else {
			res[i] = static_cast<int>(a_[i].real() - 0.5);
		}
	}
	return res;
}


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1);
    for (size_t i = 0; i <= n; ++i) {
		std::cin >> a[i];
	}

	int m;
	std::cin >> m;
	std::vector<int> b(m + 1);
	for (size_t i = 0; i <= m; ++i) {
		std::cin >> b[i];
	}

	int deg = n + m;
	std::cout << deg << ' ';
	for (auto i : mul(a, b)) {
		std::cout << i << ' ';
	}
}

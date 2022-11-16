#include <iostream>
#include <vector>
#include <map>


std::vector<int> suff_arr(const std::string &s) {
    int n = s.size();
    int counter = 0, classes = 0;
    std::vector<int> c(n), p(n);
    std::map<int, std::vector<int>> cnt;
    for (int i = 0; i < n; i++) {
        cnt[s[i]].push_back(i);
    }
    for (const auto &i : cnt) {
        for (int j : i.second){
            c[j] = classes;
            p[counter++] = j;
        }
        ++classes;
    }
    for (int k = 1; classes < n; ++k) {
        std::vector<std::vector<int> > pn(classes);
        std::vector<int> cn(n);
        int mid = (1 << k) / 2;
        int nclasses  = counter = 0;

        for (size_t i = 0; i < n; ++i) {
            int l = (p[i] - mid + n) % n;
            pn[c[l]].push_back(l);
        }

        for (size_t i = 0; i < classes; ++i) {
            for (size_t j = 0; j < pn[i].size(); ++j) {
                if (j == 0 || c[(pn[i][j] + mid) % n] != c[(pn[i][j - 1] + mid) % n]) {
                    ++nclasses;
                }
                cn[pn[i][j]] = nclasses - 1;
                p[counter++] = pn[i][j];
            }
        }
        c = cn;
        classes = nclasses;
    }
    return p;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);
    std::string s;
    std::cin >> s;
    s += '#';
    std::vector ans = suff_arr(s);
    for(size_t i = 1; i < ans.size(); ++i){
        std::cout << ans[i] + 1 << ' ';
    }
}

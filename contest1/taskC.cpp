#include <iostream>
#include <vector>
#include <queue>


const int ALPH_SZ = 26;


struct Node {
    std::vector<int> to;
    std::vector<int> go;
    int link;
    int length = 0;
    int pos = -1;
    bool term = false;
    Node() : to(std::vector<int>(ALPH_SZ, -1)), go(std::vector<int>(ALPH_SZ)), link(-1) {}
};

int charToInt(const std::string& s, int pos) {
    return s[pos] - 'a';
}

void add(const std::string& s, std::vector<Node>& trie, int num, std::vector<int>& pos) {
    if (trie.empty()) {
        trie.emplace_back();
    }
    int v = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        int pos = charToInt(s, i);
        if (trie[v].to[pos] == -1) {
            trie[v].to[pos] = trie.size();
            trie.emplace_back();
        }
        v = trie[v].to[pos];
    }
    if (trie[v].term) {
        pos.push_back(trie[v].pos);
        return;
    }
    pos.push_back(num);
    trie[v].term = true;
    trie[v].length = s.size();
    trie[v].pos = num;
}

void Aho_Corasick(std::vector<Node>& trie) {
    trie[0].link = 0;
    for (size_t i = 0; i < ALPH_SZ; ++i) {
        if (trie[0].to[i] != -1) {
            trie[0].go[i] = trie[0].to[i];
        }
        else {
            trie[0].go[i] = 0;
        }
    }
    std::queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (size_t i = 0; i < ALPH_SZ; ++i) {
            int u = trie[v].to[i];
            if (u != -1) {
                trie[u].link = (v == 0 ? 0 : trie[trie[v].link].go[i]);
                for (size_t j = 0; j < ALPH_SZ; ++j) {
                    if (trie[u].to[j] != -1) {
                        trie[u].go[j] = trie[u].to[j];
                    }
                    else {
                        trie[u].go[j] = trie[trie[u].link].go[j];
                    }
                }
                q.push(u);
            }
        }
    }
}

std::vector<std::vector<int>> getAns(const std::vector<Node>& trie, const std::string &s, int n) {
    std::vector<std::vector<int>> ans(n);
    int v = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        int pos = charToInt(s, i);
        v = trie[v].go[pos];
        int u = v;
        while (u != 0) {
            if (trie[u].term) {
                ans[trie[u].pos].push_back(static_cast<int>(i) - trie[u].length + 2);
            }
            u = trie[u].link;
        }
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);
    std::string s;
    std::cin >> s;
    int n;
    std::cin >> n;
    std::vector<Node> trie;
    std::vector<int> pos;
    for (int i = 0; i < n; ++i) {
        std::string in;
        std::cin >> in;
        add(in, trie, i, pos);
    }
    Aho_Corasick(trie);
    int v = 0;
    std::vector<std::vector<int>> ans = getAns(trie, s, n);
    
    for (auto j : pos) {
        if (!ans[j].empty()) {
            std::cout << ans[j].size() << ' ';
            for (auto i : ans[j]) {
                std::cout << i << ' ';
            }
            std::cout << '\n';
        }
        else {
            std::cout << 0 << '\n';
        }
    }
}

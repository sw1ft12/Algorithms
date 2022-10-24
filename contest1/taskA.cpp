#include <iostream>
#include <vector>
 
 
std::vector<int> p_function(const std::string& s){
    int n = s.size();
    std::vector<int> p(n);
    int k = 0;
    for(size_t i = 1; i < n; ++i){
        int j = p[i-1];
        while(j > 0 && s[j] != s[i]){
            j = p[j-1];
        }
        if(s[j] == s[i]){
            ++j;
        }
        p[i] = j;
    }
    return p;
}
 
 
int main(){
    std::string s1, s2;
    std::cin >> s1 >> s2;
    s1 = s2 + "#" + s1;
    std::vector<int> p = p_function(s1);
    for(size_t i = 0; i < p.size(); ++i){
        if(s2.size() == p[i]){
            std::cout << i - 2*s2.size() << ' ';
        }
    }
}

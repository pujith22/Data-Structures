#include <iostream>
#include <string>
#include <vector>
#define int unsigned long long

using std::string;
// typedef unsigned long long ull;

using std::cin;
using std::cout;

// void pujith22()
// {
//     #ifndef ONLINE_JUDGE
//         freopen("input.txt","r",stdin);
//         freopen("output.txt","w",stdout);
//     #endif
//     cin.tie(NULL);
//     cout.tie(NULL);
//     std::ios_base::sync_with_stdio(false);
// }

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    if(s.size()>t.size())
        return ans;
    int prime = 31LL;
    int mod = 1e9+7LL;
    int patternHash = 0;
    int textRollingHash = 0;
    for(int i=0;i<s.size();i++)
        patternHash = (patternHash*prime + s[i]+mod)%mod;

    int primePowN = 1;
    for(int i=0;i<s.size();i++)
    {
        textRollingHash = (textRollingHash*prime+t[i]+mod)%mod;
        primePowN *= prime;
        primePowN %= mod;
    }
    
    for (size_t i = s.size(); i <= t.size(); ++i)
    {
        if (patternHash==textRollingHash && t.substr(i-s.size(),s.size())==s)
            ans.push_back(i-s.size());
        if(i==t.size())
            break;
        textRollingHash = ((textRollingHash*prime)%mod + t[i]+mod)%mod;
        textRollingHash = (textRollingHash - (t[i-s.size()]*primePowN)%mod + mod)%mod;
    }
    return ans;
}


int32_t main() {
    // pujith22();
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}

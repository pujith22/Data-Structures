#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
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
struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<vector<string>> elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1e9+7;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i] + prime) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
        elems.resize(bucket_count);
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
     if(query.type=="add")
     {
        auto hashIndex = hash_func(query.s);
        for(string s: elems[hashIndex])
            if(s==query.s)
                return;
        elems[hashIndex].push_back(query.s);
     }
     else if(query.type == "del")
    {
        auto hashIndex = hash_func(query.s);
        auto it = find(elems[hashIndex].begin(),elems[hashIndex].end(),query.s);
        if(it!=elems[hashIndex].end())
            elems[hashIndex].erase(it); 
    }
        else if(query.type=="find")
        {
            auto hashIndex = hash_func(query.s);
            auto it = find(elems[hashIndex].begin(),elems[hashIndex].end(),query.s);
            if(it==elems[hashIndex].end())
                std::cout<<"no\n";
            else
                std::cout<<"yes\n";
        }
        else
        {
            for(auto it = elems[query.ind].rbegin();it!=elems[query.ind].rend();it++)
                std::cout<<*it<<" ";
            std::cout<<"\n";
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    // pujith22();
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}

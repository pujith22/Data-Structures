#include <iostream>
#include <vector>
#include <string>
#define int long long

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::ios_base;

struct Query {
    string type, name;
    int number;
};

// void pujith22()
// {
//     #ifndef ONLINE_JUDGE
//         freopen("input.txt","r",stdin);
//         freopen("output.txt","w",stdout);
//     #endif
//     cin.tie(NULL);
//     cout.tie(NULL);
//     ios_base::sync_with_stdio(false);
// }

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<string> contacts(1e7+1,"not found");
    for (size_t i = 0; i < queries.size(); ++i){
        if (queries[i].type == "add")
            contacts[queries[i].number] = queries[i].name;

        else if(queries[i].type == "del")
            contacts[queries[i].number] = "not found";
        else
            result.push_back(contacts[queries[i].number]);
    }
    return result;
}

int32_t main() {
    // pujith22();
    write_responses(process_queries(read_queries()));
    return 0;
}

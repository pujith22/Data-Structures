#include <iostream>
#include <vector>

using namespace std;

using std::cin;
using std::cout;
using std::vector;
using std::max;

void pujith22()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

void max_sliding_window_naive(vector<int> const & A, int w) {
    for (size_t i = 0; i < A.size() - w + 1; ++i) {
        int window_max = A.at(i);
        for (size_t j = i + 1; j < i + w; ++j)
            window_max = max(window_max, A.at(j));

        cout << window_max << " ";
    }

    return;
}

void max_sliding_window(vector<int> const& arr, int w)
{
    deque<int> d;
    for(int i=0;i<arr.size();i++)
    {
        // remove elements that are no more in the current window
        while(d.size()>0 and d.front()<=i-w)
            d.pop_front();

        // here we are maintaining the monotonicity of deque, i.e all elements would be in decreasing order.
        while(d.size()>0 and arr[d.back()]<=arr[i])
            d.pop_back();

        d.push_back(i);

        // front will always contain the max element of the current window (recall that the elements are in decreasing order)
        if(i>=w-1)
            cout<<arr[d.front()]<<" ";
    }
}

int main() {
    pujith22();
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window(A, w);

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>

// using namespace std;

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

// void pujith22()
// {
//   #ifndef ONLINE_JUDGE
//     freopen("input.txt","r",stdin);
//     freopen("output.txt","w",stdout);
//   #endif
//   cin.tie(NULL);
//   cout.tie(NULL);
//   ios_base::sync_with_stdio(false);
// }

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    for(int i=data_.size()-1;i>=0;i--)
    {
      int index = i;
      while(index<data_.size())
      {
        int minIndex = index;
        if(2*minIndex+1<data_.size() && data_[2*minIndex+1]<data_[minIndex])
          minIndex = 2*minIndex+1;
        if(2*minIndex+2<data_.size() && data_[2*minIndex+2]<data_[minIndex])
          minIndex = 2*minIndex+2;
        if(minIndex!=index)
        {
          auto ele = make_pair(index,minIndex);
          swaps_.push_back(ele);
          swap(data_[index],data_[minIndex]);
          index = minIndex;
        }
        else
          break;
      }
    }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  // pujith22();
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}

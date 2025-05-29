#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define int long long

// using namespace std;

using std::vector;
using std::cin;
using std::cout;
using std::priority_queue;
using std::pair;
using std::greater;

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

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    std::priority_queue<std::pair<int,int>,vector<pair<int,int>>,std::greater<pair<int,int>>> pq;
    for(int i=0;i<num_workers_;i++)
      pq.push({0,i});
    for(int i=0;i<jobs_.size();i++)
    {
      auto thread = pq.top();
      pq.pop();
      assigned_workers_[i] = thread.second;
      start_times_[i] = thread.first;
      thread.first += jobs_[i];
      pq.push(thread);
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int32_t main() {
  // pujith22();
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}

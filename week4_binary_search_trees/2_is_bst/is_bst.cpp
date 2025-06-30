#include <algorithm>
#include <iostream>
#include <vector>

// using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::make_pair;
using std::min;
using std::max;

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
struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

pair<bool,pair<int,int>> helper(const vector<Node>& tree, const Node& node)
{
  if(node.left==-1 && node.right==-1)
    return {true,{node.key,node.key}};
  int MIN = -(1LL<<31);
  int MAX = (1LL<<31)-1LL;
  auto left = make_pair(true,make_pair(MAX,MIN));
  auto right = left;
  if(node.left!=-1)
    left = helper(tree,tree[node.left]);
  if(node.right!=-1)
    right = helper(tree,tree[node.right]);
  bool ans = true;
  ans = ans && left.first && right.first;
  int left_min = left.second.first;
  int left_max = left.second.second;
  int right_min = right.second.first;
  int right_max = right.second.second;
  // cout<<left_min<<", "<<left_max<<", "<<right_min<<", "<<right_max<<"key: "<<node.key<<"\n";
  ans = ans && (left_max<node.key && right_min>node.key);
  int tree_min = min(left_min,right_min);
  tree_min = min(tree_min,node.key);
  int tree_max = max(right_max,left_max);
  tree_max = max(tree_max,node.key);
  return {ans,{tree_min,tree_max}};
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  if(tree.size()<=1)
    return true;
  auto ans = helper(tree,tree[0]);
  return ans.first;
}

int32_t main() {
  // pujith22();
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}

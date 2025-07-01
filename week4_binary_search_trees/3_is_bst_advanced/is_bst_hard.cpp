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

pair<bool,pair<int,int>> helper(const vector<Node>& tree, const Node& root)
{
  if(root.left==-1 && root.right==-1)
    return {true,{root.key,root.key}};
  bool is_bst = true;
  int tree_min = root.key;
  int tree_max = root.key;
  if(root.left!=-1)
  {
    auto left = helper(tree,tree[root.left]);
    is_bst = is_bst && left.first;
    // left subtree max should be strictly less than the root key.
    is_bst = is_bst && (root.key > left.second.second);
    tree_min = min(tree_min,left.second.first);
    tree_max = max(tree_max,left.second.second);
  }
  if(root.right!=-1)
  {
    auto right = helper(tree,tree[root.right]);
    is_bst = is_bst && right.first;
    is_bst = is_bst && (root.key <= right.second.first);
    tree_min = min(tree_min,right.second.first);
    tree_max = max(tree_max,right.second.second);
  }
  return {is_bst,{tree_min,tree_max}};
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  if(tree.size()<=1)
    return true;
  auto p = helper(tree,tree[0]);
  return p.first;
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

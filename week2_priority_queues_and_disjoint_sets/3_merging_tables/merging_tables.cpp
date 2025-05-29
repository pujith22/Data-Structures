#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

// using namespace std;

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

// void pujith22()
// {
// 	#ifndef ONLINE_JUDGE
// 		freopen("input.txt","r",stdin);
// 		freopen("output.txt","w",stdout);
// 	#endif
// 	ios_base::sync_with_stdio(false);
// 	cin.tie(NULL);
// 	cout.tie(NULL);
// }

struct DisjointSetsElement {
	int size, parent, rank;
	
	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
	int max_table_size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size): size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
	}

	int getParent(int table) {
		// find parent and compress path
		if(sets[table].parent==table)
			return table;
		return sets[table].parent = getParent(sets[table].parent);
	}

	void merge(int destination, int source) {
		int realDestination = getParent(destination);
		int realSource = getParent(source);
		if (realDestination != realSource) {
			// merge two components
			// use union by rank heuristic
            // update max_table_size
			max_table_size = max(max_table_size,sets[realDestination].size+sets[realSource].size);
			if(sets[realDestination].rank>=sets[realSource].rank)
			{
				sets[realSource].parent = realDestination;
				// when both ranks are same, rank of the parent will increase as we attach one of the tree to the other tree.
				if(sets[realDestination].rank==sets[realSource].rank)
					sets[realDestination].rank+=1;
				sets[realDestination].size+=sets[realSource].size;

			}
			else
			{
				sets[realDestination].parent = realSource;
				sets[realSource].size += sets[realDestination].size;
			}

		}		
	}
};

int main() {
	// pujith22();
	int n, m;
	cin >> n >> m;

	DisjointSets tables(n);
	for (auto &table : tables.sets) {
		cin >> table.size;
		tables.max_table_size = max(tables.max_table_size, table.size);
	}

	for (int i = 0; i < m; i++) {
		int destination, source;
		cin >> destination >> source;
                --destination;
                --source;
		
		tables.merge(destination, source);
	        cout << tables.max_table_size << endl;
	}

	return 0;
}

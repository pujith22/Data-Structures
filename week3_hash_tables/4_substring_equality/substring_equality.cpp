#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

using namespace std;

// void pujith22()
// {
// 	#ifndef ONLINE_JUDGE
// 		freopen("input.txt","r",stdin);
// 		freopen("output.txt","w",stdout);
// 	#endif
// 	cin.tie(NULL);
// 	cout.tie(NULL);
// 	ios_base::sync_with_stdio(false);
// }
class Solver {
	string s;
	vector<int> hash;
	vector<int> primePow;
	int mod;
	int prime;
public:	
	Solver(string s) : s(s) {	
		// initialization, precalculation
		prime = 31LL;
		mod = 1e9+7LL;
		hash.resize(s.size()+1,0LL);
		primePow.resize(s.size());
		int pow = 1LL;
		for(int i=s.size()-1;i>=0;i--)
		{
			primePow[i] = pow;
			hash[i] = (s[i]*pow)%mod;
			pow = (pow*prime)%mod;
			if(i!=s.size()-1)
				hash[i] = (hash[i]+hash[i+1])%mod;
		}
		// for latter use of powers with 0 based indexing.
		reverse(primePow.begin(),primePow.end());
	}

	bool helper(int a, int b, int l)
	{
		// skipping if start indices are same
		if(a==b)
			return true;
		for(int i=0;i<l;i++)
			if(s[a+i]!=s[b+i])
				return false;
		return true;
	}

	bool hashCompare(int a, int b, int l)
	{
		int maxi = max(a,b);
		int mini = min(a,b);
		int hash1 = (hash[mini]-hash[mini+l]+mod)%mod;
		int hash2 = (hash[maxi]-hash[maxi+l]+mod)%mod;
		// for aligning with hash1
		hash2 = (hash2*(primePow[maxi-mini]))%mod;
		return hash1==hash2;
	}
	bool ask(int a, int b, int l) {
		// will work with probability close to 99.99% due to hash collisions
		// we can reduce this further using 2 diffrent hashes with help of 2 different mod values
		return hashCompare(a,b,l);
	}
};

int32_t main() {
	// pujith22();
	ios_base::sync_with_stdio(0), cin.tie(0);
	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
	return 0;
}

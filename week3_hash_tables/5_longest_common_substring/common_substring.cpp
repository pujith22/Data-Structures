#include <iostream>
#include <vector>
#include <algorithm>

#define int long long

using namespace std;

struct Answer {
	size_t i, j, len;
};

Answer solve(const string &s, const string &t) {
	Answer ans = {0, 0, 0};
	for (size_t i = 0; i < s.size(); i++)
		for (size_t j = 0; j < t.size(); j++)
			for (size_t len = 0; i + len <= s.size() && j + len <= t.size(); len++)
				if (len > ans.len && s.substr(i, len) == t.substr(j, len))
					ans = {i, j, len};
	return ans;
}

std::vector<int> substringHashes(const string &s, int length, int k, int mod)
{
	vector<int> sol;
	int hash = 0;
	int kn = 1;
	for(int i=0;i<length;i++)
	{
		hash = (hash*k+s[i])%mod;
		kn = (kn*k)%mod;
	}

	for(int i=length;i<s.size();i++)
	{
		sol.push_back(hash);
		hash = (hash*k+s[i]+mod-(s[i-length]*kn)%mod)%mod; 
	}
	sol.push_back(hash);
	return sol;
}

// returns lowest index that is greater than or equal to the given value
int custom_lower_bound(const std::vector<std::vector<int>>& s,int val)
{
	int lo = -1;
	int hi = s.size();
	while(lo+1<hi)
	{
		int mid = lo + (hi-lo)/2;
		if(s[mid][0]<val)
			lo = mid;
		else
			hi = mid;
	}
	return hi;
}

// returns lowest index that is greater than the given value.
int custom_upper_bound(const std::vector<std::vector<int>>& s, int val)
{
	int lo = -1;
	int hi = s.size();
	while(lo+1<hi)
	{
		int mid = lo + (hi-lo)/2;
		if(s[mid][0]<=val)
			lo = mid;
		else
			hi = mid;
	}
	return hi;
}

bool isLengthPossible(const string &s, const string &t, int length, Answer& sol)
{
	if(length>min(s.size(),t.size()))
		return false;
	int mod1 = 1e9+7;
	int mod2 = 1e9+9;
	int k = 31;
	std::vector<int> sHashes1 = substringHashes(s,length,k,mod1);
	std::vector<int> sHashes2 = substringHashes(s,length,k,mod2);
	std::vector<int> tHashes1 = substringHashes(t,length,k,mod1);
	std::vector<int> tHashes2 = substringHashes(t,length,k,mod2);

	std::vector<std::vector<int>> tHashes1withIndex;
	for(int i=0;i<tHashes1.size();i++)
		tHashes1withIndex.push_back({tHashes1[i],i});
	sort(tHashes1withIndex.begin(),tHashes1withIndex.end());
	for(int i=0;i<sHashes1.size();i++)
	{
		int lo = custom_lower_bound(tHashes1withIndex,sHashes1[i]);
		int hi = custom_upper_bound(tHashes1withIndex,sHashes1[i]);
		for(int j=lo;j<hi;j++)
		{
			int index = tHashes1withIndex[j][1];
			// this means that hases of substring staring at ith index in first string is matching
			// with substring starting at index in second string of length length.
			// one more confirmation with the second hash to reduce collison probability
			int hash2 = tHashes2[index];
			int hash1 = sHashes2[i];
			if(hash2==hash1)
			{
				sol.i = i;
				sol.j = index;
				sol.len = length;
				return true;
			}

		}
	}
	return false;
}

Answer sol(const string&s, const string&t)
{
	Answer sol = {0,0,0};
	int lo = 0;
	int hi = min(s.size(),t.size())+1;
	while(lo+1<hi)
	{
		int mid = lo+(hi-lo)/2;
		if(isLengthPossible(s,t,mid,sol))
			lo = mid;
		else
			hi = mid;
	}
	if(lo==0)
		return sol;
	// for recomputing solution
	isLengthPossible(s,t,lo,sol);
	return sol;
}

int32_t main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	string s, t;
	while (cin >> s >> t) {
		auto ans = sol(s, t);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
	return 0;
}
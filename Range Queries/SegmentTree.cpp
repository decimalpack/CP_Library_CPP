#include <bits/stdc++.h>
using namespace std;
template <typename T = int>
struct SegmentTree
{
	static constexpr T unit = INT_MIN;
	T f(T a, T b) { return max(a, b); } // (any associative fn)
	vector<T> s;
	int n;
	SegmentTree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
	SegmentTree(vector<T> const &arr) : s(2 * arr.size(), unit), n(arr.size())
	{
		copy(arr.begin(), arr.end(), s.begin() + n);
		for (int i = n - 1; i > 0; i--)
			s[i] = f(s[i * 2], s[i * 2 + 1]);
	}
	void update(int pos, T val)
	{
		s[pos += n] = val;
		while (pos)
		{
			pos /= 2;
			T new_val = f(s[pos * 2], s[pos * 2 + 1]);
			// Stop early if the result is unchanged
			if (s[pos] != new_val)
				s[pos] = new_val;
			else
				return;
		}
	}
	// Query [b,e)
	T query(int b, int e)
	{
		T ans = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2)
		{
			if (b & 1)
				ans = f(ans, s[b++]);
			if (e & 1)
				ans = f(ans, s[--e]);
		}
		return ans;
	}
};

// Test on https://leetcode.com/problems/range-sum-query-mutable/
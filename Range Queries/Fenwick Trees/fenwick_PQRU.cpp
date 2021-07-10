#include <bits/stdc++.h>
using namespace std;

/*
Related Problems:
    - https://binarysearch.com/problems/Range-Update
    
References:
    1) CP-algos: https://cp-algorithms.com/data_structures/fenwick.html
*/

/*
    Fenwick Tree - Point Query Range Update

    Types of operations:
        - f:
            - An associative function
            - By default plus
        - f_rev:
            - Inverse of f
            - By default minus

    Time Complexity: 
        - Insertion: O(log(n))
        - Query: O(log(n))

    Space Complexity:
        - O(n)
    

    Note: 
        - To disable assertions #define NDEBUG before including assert.h
*/
template <typename T>
struct FenwickTree_PQRU
{
private:
    /*
        Not intended to be included in API,
        instead use range_update(i,i,delta)

        Add delta to index
    */
    void point_update(int index, T delta)
    {
        while (index < n)
        {
            fenwick_tree[index] = f(fenwick_tree[index], delta);
            index |= (index + 1);
        }
    }

public:
    vector<T> fenwick_tree;
    int n;

    T f(T a, T b)
    {
        return a + b;
    }
    T f_rev(T a, T b)
    {
        return a - b;
    }
    FenwickTree_PQRU() {}
    FenwickTree_PQRU(int size) : n(size), fenwick_tree(size) {}

    // Initialize from arr of size `n` in O(n*log(n))
    FenwickTree_PQRU(vector<T> arr) : FenwickTree_PQRU(arr.size())
    {
        for (int i = 0; i < n; ++i)
            range_update(i, i, arr[i]);
    }

    // Get value at index
    T point_query(int index)
    {
        assert(0 <= index && index < n);
        T ans = 0;
        while (index >= 0)
        {
            ans = f(ans, fenwick_tree[index]);
            index = (index & (index + 1)) - 1;
        }
        return ans;
    }

    // Add delta to all values in range [L:R]
    void range_update(int l, int r, T delta)
    {
        assert(0 <= l && l <= r);
        assert(r < n);
        point_update(l, delta);
        point_update(r + 1, -delta);
    }
};
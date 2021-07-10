#include <bits/stdc++.h>
using namespace std;
/*
Problems:
    https://binarysearch.com/problems/Range-Query-on-a-List-Mutable

Fork52 Editorial:
    https://binarysearch.com/problems/Range-Query-on-a-List-Mutable/editorials/4533602
    
References:
    1) Stable-Sort: https://youtu.be/uSFzHCZ4E-8
    2) Luv: https://youtu.be/DPiY9wFxGIw
    3) CP-algos: https://cp-algorithms.com/data_structures/fenwick.html
*/

/*
    Fenwick Tree - Point Update Range Query

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
struct FenwickTree_PURQ
{
    vector<T> fenwick_tree;
    const int n;

    T f(T a, T b)
    {
        return a + b;
    }
    T f_rev(T a, T b)
    {
        return a - b;
    }

    FenwickTree_PURQ()
    {
    }

    // Initialize with 0
    FenwickTree_PURQ(int size) : n(size), fenwick_tree(size)
    {
    }

    /* 
        Initialize from array
        Time: O(nlog(n))
    */
    FenwickTree_PURQ(vector<T> arr) : FenwickTree_PURQ(arr.size())
    {
        for (int i = 0; i < n; ++i)
            point_update(i, arr[i]);
    }

    // Return f applied over range [0:R]
    T range_query(int r)
    {
        assert(r < n);
        T ans = 0;
        while (r >= 0)
        {
            ans = f(ans, fenwick_tree[r]);
            r = (r & (r + 1)) - 1;
        }
        return ans;
    }

    // Return f applied over range [L:R], 0 indexed
    T range_query(int l, int r)
    {
        assert(0 <= l && l <= r);
        assert(r < n);
        return f_rev(range_query(r), range_query(l - 1));
    }

    // Add delta to an index
    void point_update(int index, T delta)
    {
        assert(0 <= index && index < n);
        while (index < n)
        {
            fenwick_tree[index] = f(fenwick_tree[index], delta);
            index |= (index + 1);
        }
    }
};

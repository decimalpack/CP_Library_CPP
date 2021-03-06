#include <bits/stdc++.h>
#include "../Range Queries/Fenwick Trees/fenwick_PQRU.cpp"
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"
using namespace std;

TEST_CASE("Entire array")
{
	const int n = 1000;
	vector<int> arr(n);
	iota(arr.begin(), arr.end(), 1);
	FenwickTree_PQRU<int> ft(arr);

	SECTION("From -100 to 100")
	{
		int total = 0;
		for (int delta = -100; delta <= 100; delta++)
		{
			ft.range_update(0, n - 1, delta);
			total += delta;
			for (int i = 0; i < n; i++)
			{
				REQUIRE(ft.point_query(i) == arr[i] + total);
			}
		}
	}
}
TEST_CASE("Benchmark", "[.benchmark]")
{
	for (int n = 1; n <= 1e5; n *= 10)
	{
		vector<int> arr(n);
		iota(arr.begin(), arr.end(), 1);
		BENCHMARK("Array size: " + to_string(n))
		{
			CAPTURE(arr);
			FenwickTree_PQRU<int> ft(arr);
			int total = 0;
			for (int delta = -5; delta <= 5; delta++)
			{
				ft.range_update(0, n - 1, delta);
				total += delta;
				for (int i = 0; i < n; i++)
				{
					REQUIRE(ft.point_query(i) == arr[i] + total);
				}
			}
		};
	}
}

TEST_CASE("Subarray")
{

	const int n = 25;
	vector<int> arr(n);
	iota(arr.begin(), arr.end(), 1);
	FenwickTree_PQRU<int> ft(arr);

	for (int l = 0; l < n; l++)
	{
		for (int r = l; r < n; r++)
		{
			stringstream test_name;
			test_name << "Subarray: [" << l << ", " << r << "]";
			SECTION(test_name.str())
			{
				int total = 0;
				for (int delta = -10; delta <= 10; delta++)
				{
					ft.range_update(l, r, delta);
					total += delta;
					for (int i = l; i <= r; i++)
					{
						REQUIRE(ft.point_query(i) == arr[i] + total);
					}
				}
			}
		}
	}
}
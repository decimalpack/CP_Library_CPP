#include <bits/stdc++.h>
#include "../Number Theory/primality.cpp"
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"
using namespace std;

// Also see https://www.spoj.com/problems/PON/

TEST_CASE("First 100 primes")
{
	// https://miniwebtool.com/list-of-prime-numbers/?to=100
	vector<uint64_t> primes_upto_100 = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

	PrimeSieve<100> sieve;
	REQUIRE(sieve.get_primes() == primes_upto_100);
}
TEST_CASE("First 97 primes")
{
	vector<uint64_t> primes_upto_97 = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

	// Since exclusive
	PrimeSieve<98> sieve;
	REQUIRE(sieve.get_primes() == primes_upto_97);
}

TEST_CASE("Sieve count upto 1e5")
{
	const int N = 1e5;
	PrimeSieve<N> p;
	REQUIRE(p.count() == 9592);
}

TEST_CASE("Non-sieve check upto 1e5")
{
	const int N = 1e5;
	PrimeSieve<1> p;
	int count = 0;
	for (int i = 0; i < N; ++i)
		count += p.is_prime(i);
	REQUIRE(count == 9592);
}

TEST_CASE("Benchmarks", "[.benchmark]")
{
	unordered_map<int, int> ans = {
		{1e3, 168},
		{1e4, 1229},
		{1e5, 9592},
		{1e6, 78498},
	};
	BENCHMARK("Prime counts: 1e4")
	{
		const int N = 1e4;
		PrimeSieve<N> sieve;
		REQUIRE(sieve.count() == ans[N]);
	};
	BENCHMARK("Prime counts: 1e5")
	{
		const int N = 1e5;
		PrimeSieve<N> sieve;
		REQUIRE(sieve.count() == ans[N]);
	};
	BENCHMARK("Prime counts: 1e6")
	{
		const int N = 1e6;
		PrimeSieve<N> sieve;
		REQUIRE(sieve.count() == ans[N]);
	};
	for (int N : {1e3, 1e4, 1e5})
		BENCHMARK("Non sieve count: " + to_string(N))
		{
			PrimeSieve<1> sieve;
			int count = 0;
			for (int i = 0; i < N; ++i)
				count += sieve.is_prime(i);
			REQUIRE(count == ans[N]);
		};
}
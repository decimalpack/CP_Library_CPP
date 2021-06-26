#include <bits/stdc++.h>
using namespace std;
/*

# Note
It's exclusive, i.e. if N is prime, it will not be included

- To be declared globally as below
- On my machine, SIEVE max is 6e7,
- Sometimes, SIEVE=1e5 is better, such as:
   - If only primality testing of large values is needed, see https://www.spoj.com/problems/PON/

const int SIEVE = 1e6;
PrimeSieve<SIEVE> p;
*/
template <int N>
struct PrimeSieve
{
	bitset<N> prime_bitset;

	// Modular exponentiation
	uint64_t binpower(uint64_t base, uint64_t e, uint64_t mod)
	{
		uint64_t result = 1;
		base %= mod;
		while (e)
		{
			if (e & 1)
				result = (__uint128_t)result * base % mod;
			base = (__uint128_t)base * base % mod;
			e >>= 1;
		}
		return result;
	}

	bool check_composite(uint64_t n, uint64_t a, uint64_t d, int s)
	{
		uint64_t x = binpower(a, d, n);
		if (x == 1 || x == n - 1)
			return false;
		for (int r = 1; r < s; r++)
		{
			x = (__uint128_t)x * x % n;
			if (x == n - 1)
				return false;
		}
		return true;
	};

	// https://cp-algorithms.com/algebra/primality_tests.html
	bool MillerRabin(uint64_t n)
	{
		if (n < 2)
			return false;

		int r = 0;
		uint64_t d = n - 1;
		while ((d & 1) == 0)
		{
			d >>= 1;
			r++;
		}
		array<int, 12> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

		// For 32bit and 64bit integers, only 4 and 12 bases are required
		int n_bases = n <= UINT32_MAX ? 4 : 12;
		for (int i = 0; i < n_bases; ++i)
		{
			int a = bases[i];
			if (n == a)
				return true;
			if (check_composite(n, a, d, r))
				return false;
		}
		return true;
	}

	PrimeSieve() : prime_bitset()
	{
		prime_bitset.set();
		prime_bitset[0] = prime_bitset[1] = false;
		for (int j = 4; j < N; j += 2)
			prime_bitset[j] = false;
		for (int i = 3; i * i < N; i += 2)
			if (prime_bitset[i])
				for (int j = i * i; j < N; j += i)
					prime_bitset[j] = false;
	}

	// Checks if n is prime, guaranteed for all integers < 2^64
	bool is_prime(uint64_t n)
	{
		if (n < N)
			return prime_bitset[n]; // n is sieved
		return MillerRabin(n);
	}

	// Return a sorted vector of all primes <N
	vector<uint64_t> get_primes()
	{
		uint64_t n_primes = prime_bitset.count();
		vector<uint64_t> primes(n_primes);
		uint64_t p = 0;
		for (uint64_t i = 2; p < n_primes; i = prime_bitset._Find_next(i))
			primes[p++] = i;
		return primes;
	}

	// Number of primes <N
	uint64_t count()
	{
		return prime_bitset.count();
	}
};

#include "pch.h"
#include "rand.h"
#include <random>


namespace random{

	std::mt19937 _mt32;  // NOLINT
	std::mt19937_64 _mt64;  // NOLINT
	

	void init_rand() {
		const unsigned long long t = time(nullptr);
		_mt32.seed(static_cast<unsigned int>(t));
		_mt64.seed(t);
	}

	void init_rand(const unsigned long long seed) {
		_mt32.seed(static_cast<unsigned int>(seed));
		_mt64.seed(seed);
	}

	int rand_int() {
		return static_cast<int>(_mt32());
	}

	unsigned long long rand_long_long() {
		return _mt64();
	}


}

#pragma once

namespace random {
	
	void init_rand();
	void init_rand(const unsigned long long seed);

	unsigned int rand_int();
	unsigned long long rand_long_long();


};
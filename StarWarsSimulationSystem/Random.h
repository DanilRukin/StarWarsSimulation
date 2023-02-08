#pragma once

#include "StarWarsAPI.h"
#include <random>

namespace Core
{
	class StarWarsObject Random
	{
	public:
        Random() {}
        int Next(int minimum, int maximum)
        {
            std::random_device rd;   // non-deterministic generator
            std::mt19937 gen(rd());  // to seed mersenne twister.
            std::uniform_int_distribution<> dist(minimum, maximum); // distribute results between minimum and maximum inclusive.
            return dist(gen);
        }
        int Next()
        {
            std::random_device rd;   // non-deterministic generator
            std::mt19937 gen(rd());  // to seed mersenne twister.
            return gen();
        }
	};
}

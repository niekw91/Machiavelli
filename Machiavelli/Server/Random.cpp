#include "Random.h"

std::random_device Random::dev;

int Random::Next(int bottom, int top) {
	default_random_engine dre(dev());
	uniform_int_distribution<int> dist(bottom, top);

	return dist(dre);
}


#pragma once
#include <limits>

namespace TempolimitNS{
	enum class Tempolimit
	{
		Innerorts = 50, // km/h
		Landstrasse = 100, // km/h
		Autobahn = std::numeric_limits<int>::max()
	};
}

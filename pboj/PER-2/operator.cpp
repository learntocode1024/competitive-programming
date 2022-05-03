#include <vector>
#include "operator.h"

namespace {
	int var1 = -1, var2 = 42;
	int function() {
		return 42;
	}
}

std::vector<int> solve(int n) {
	query(std::vector<int>(n + 1, n));
	query(std::vector<int>(n + 1, function()));
	return std::vector<int>(n);
}

#include "hexagon.h"

#include <vector>
#include <cstdint>
const int64_t MOD = 1000000007;

int draw_territory(int N, int A, int B,
                   std::vector<int> D, std::vector<int> L) {
  int64_t a = A, b = B;
  int64_t n = L[0] + 1;
  int64_t s = n * (n + 1) / 2 % MOD;
  int64_t s2 = (n * (n + 1) % MOD * (2 * n + 1) % MOD * 166666668 % MOD  + MOD - s) % MOD;
  int ret = (s2 * b % MOD + s * a % MOD) % MOD;
  return ret;
}

/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Jul 18, 2021
 * Algorithm:
 * Difficulty:
 *
 *********************************************************************/

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 998244353;

#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX 100005

template<typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  b = min(a, b);
}

LL x[MX], y[MX];
int n;
inline LL dist2(int a, int b) {
  LL p = x[a] - x[b], q = y[a] - y[b];
  return (p * p + q * q) % mod;
}

namespace SUB30 {
void solve () {
  for (int i = 0; i < n; ++i) {
    LL ans = 1;
    for (int j = 0; j < n; ++j) {
      if (j != i) ans = ans * dist2(i, j) % mod;
    }
    printf("%lld\n", ans);
  }
}
}

void solve() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld%lld", x + i, y + i);
  }
  if (n <= 2000) SUB30::solve();
}

int main() {
  int T = 1;
  while (T--)
    solve();
  return 0;
}


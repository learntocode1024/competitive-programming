/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date:
 * Algorithm:
 * Difficulty:
 *
 *********************************************************************/

#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/********************************** buffer IO *********************************/
namespace IO {
char in[1 << 24];  // sizeof in varied in problem
char const *o;
void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0;  // set 0 at the end of buffer.
}
int rd() {
  unsigned u = 0, s = 0;
  while (*o && *o <= 32) ++o;  // skip whitespaces...
  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o;  // skip sign
  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0');  // u * 10 = u * 8 + u * 2 :)
  return static_cast<int>((u ^ s) + !!s);
}
char *rdstr(char *s) {
  while (*o && *o <= 32) ++o;
  while (*o > 32) *s++ = *o++;
  return s;
}
}  // namespace IO

/********************************* utility ************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef pair<int, int> pii;
#define pb(x) push_back(x)
#define mkp(x, y) make_pair(x, y)
#define fi first
#define se second
#define FOR(x, y, z) for (int x = y; x < z; ++x)  // always [y, z)
#define ROF(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  a = min(a, b);
}
pii operator+(const pii &a, const pii &b) {
  return mkp(a.fi + b.fi, a.se + b.se);
}

/*********************************** solution *********************************/
using IO::rd;
const int N = 55, M = 100005;
const i64 mod = 998244353;

i64 dp[M], cur[M];
int miu[M], low[M], pri[M], tot;
int n, m;

inline void getmiu() {
  miu[1] = 1;
  for (int i = 2; i <= m; ++i) {
    if (!low[i]) {
      low[i] = i;
      pri[tot++] = i;
      miu[i] = -1;
    }
    for (int j = 0; pri[j] * i <= m; ++j) {
      if (pri[j] == low[i]) {
        low[i * pri[j]] = pri[j];
        miu[i * pri[j]] = 0;
        break;
      } else {
        low[i * pri[j]] = pri[j];
        miu[i * pri[j]] = -miu[i];
      }
    }
  }
}

int l[N], r[N];

void solve() {
  n = rd(), m = rd();
  getmiu();
  for (int i = 0; i < n; ++i) {
    l[i] = rd(), r[i] = rd();
  }
  dp[0] = 1;
  i64 ans = 0;
  for (int i = 0; i <= n; ++i) {
    for (int i = 1; i <= m; ++i) {
      dp[i] = (dp[i] + dp[i - 1]) % mod;
    }
  }
  for (int i = 1; i <= m; ++i) {
    int k = m / i;
    for (int j = 0; j < n; ++j) {
      k -= ceil(1.0 * l[j] / i);
    }
    if (k < 0) continue;
    for (int j = 0; j <= k; ++j) {
      cur[j] = dp[j];
    }
    for (int j = 0; j < n; ++j) {
      int kk = r[j] / i - (int)ceil(1.0 * l[j] / i) + 1;
      for (int p = kk; p <= k; ++p) {
        cur[p] = (cur[p] - cur[p - kk] + mod) % mod;
      }
    }
    ans = (ans + mod + miu[i] * cur[k]) % mod;
  }
  cout << ans << '\n';
}

int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
  solve();
#endif
  return 0;
}


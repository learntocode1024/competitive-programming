/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
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
  *s = '\0';
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
// #define MULTI
const int N = 1e5+5;
const int p = 998244353;
inline void red(int &x) { if (x >= p) x -= p; }

inline int q_pow(i64 a, int x) {
  i64 ret = 1;
  while (x) {
    if (x & 1) ret = ret * a % p;
    x >>= 1;
    a = a * a % p;
  }
  return ret;
}

inline int inv(int a) { return q_pow(a, p - 2); }

inline int rdfrac() {
  int a = rd(), b = rd();
  return 1ll * a * inv(b) % p;
}

vector<int> G[N];
int P[N];
int n;


namespace sub50 {
int sz[1005], dpf[4][1005][1005];
int f1[1005], g1[1005], h1[1005];
inline void dfs(int u, int fa) {
  sz[u] = 1;
  auto dp = dpf[0];
  auto f = dpf[1][u], g = dpf[2][u], h = dpf[3][u];
  red(dp[u][0] = 1 + p - P[u]);
  f[1] = P[u];
  int g0 = 1;
  for (auto v : G[u]) {
    if (v == fa) continue;
    dfs(v, u);
    dp[u][0] = 1ll * dp[u][0] * dp[v][0] % p;
    FOR(i, 0, sz[u] + 1) f1[i] = f[i], g1[i] = g[i], h1[i] = h[i], f[i] = g[i] = h[i] = 0;
    for (int i = 1; i <= sz[u]; ++i) {
      for (int j = 0; j <= sz[v]; ++j) {
        red(f[i + j] += 1ll * f1[i] * dp[v][j] % p);
      }
    }
    for (int i = 0; i <= sz[u]; ++i) {
      for (int j = 0; j <= sz[v]; ++j) {
        red(h[i + j] += 1ll * h1[i] * dp[v][j] % p);
        if (i && j) red(h[i + j + 1] += 1ll * g1[i] * dp[v][j] % p);
      }
    }
    sz[u] += sz[v];
    for (int i = 1; i < sz[u]; ++i) {
      if (i <= sz[v]) {
        red(g[i] += 1ll * g0 * dp[v][i] % p);
      }
      red(g[i] += 1ll * g1[i] * dp[v][0]);
    }
    g0 = 1ll * g0 * dp[v][0] % p;
  }
  for (int i = 1; i <= sz[u]; ++i) {
    dp[u][i] = f[i];
    red(dp[u][i] += 1ll * (1 + p - P[u]) * g[i] % p);
    red(dp[u][i] += 1ll * (1 + p - P[u]) * h[i] % p);
  }
}

inline void work() {
  dfs(1, 0);
  int ans = 0;
  FOR(i, 1, n + 1) {
    red(ans += 1ll * dpf[0][1][i] * i % p);
  }
  cout << ans << '\n';
}

}

void solve() {
  n = rd();
  FOR(i, 1, n + 1) P[i] = rdfrac();
  FOR(i, 1, n) {
    int u = rd(), v = rd();
    G[u].pb(v);
    G[v].pb(u);
  }
  if (n <= 1000) sub50::work();
  else cout << n << '\n';
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
/*
 * checklist:
 * - IO buffer size
 * - potential out-of-bound Errors
 * - inappropriate variable type
 * - potential Arithmetic Error
 * - potential Arithmetic Overflow
 * - typo / logical flaws
 * - clean-up on multiple test cases
 * - sufficient stress tests / random data tests
*/

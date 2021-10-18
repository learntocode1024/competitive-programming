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
const i64 p = 998244353;
vector<int> C[N], g[N];
i64 P[N], Q[N], dp[N];
int to[N], vis[N], tot;
bool on_cyc[N], dvis[N];
int n;

inline int q_pow(i64 a, int x) {
  i64 ret = 1;
  while (x) {
    if (x & 1) ret = ret * a % p;
    a = a * a % p;
    x >>= 1;
  }
  return ret;
}

inline i64 rdfrac() {
  i64 a = rd(), b = rd();
  return a * q_pow(b, p - 2) % p;
}

i64 a1[N], a0[N], f[N];

inline void elimination(const vector<int> &a) {
  int n = a.size();
  i64 pdq = 1;
  for (int i = 0; i < n; ++i) {
    pdq = pdq * Q[a[i]] % p;
    pdq = pdq * (p + 1 - P[a[i]]) % p;
  }
  a1[n - 1] = 1;
  a0[n - 1] = 0;
  for (int i = n - 2; i >= 0; --i) {
    i64 c = (p + 1 - P[a[i]]) * Q[a[i + 1]] % p;
    a1[i] = a1[i + 1] * c % p;
    a0[i] = (c * a0[i + 1] + P[a[i]] + p - P[a[i]] * pdq % p) % p;
  }
  i64 c0 = (p + 1 - P[a[n - 1]]) * Q[a[0]] % p;
  i64 A = a1[0] * c0 % p;
  i64 B = (c0 * a0[0] + P[a[n - 1]] + p - P[a[n - 1]] * pdq % p) % p;
  i64 x = (p - B) * q_pow((p + A - 1) % p, p - 2) % p;
  FOR(i, 0, n) {
    dp[a[i]] = (a1[i] * x + a0[i]) % p;
  }
}

int cyc(int u) {
  vis[u] = tot;
  if (vis[to[u]] == tot) {
    C[tot].pb(u);
    on_cyc[u] = 1;
    return to[u];
  } else if (vis[to[u]]) {
    return 0;
  }
  int ret = cyc(to[u]);
  if (!ret) return 0;
  C[tot].pb(u);
  on_cyc[u] = 1;
  if (ret == u) return 0;
  return ret;
}

void dfs(int u) {
  dvis[u] = 1;
  dp[u] = P[u];
  for (auto v : g[u]) {
    if (!dvis[v]) dfs(v);
    dp[u] = (dp[u] + (p + 1 - dp[u]) * dp[v] % p * Q[v] % p) % p;
  }
}

void solve() {
  int n = rd();
  FOR(i, 1, n + 1) P[i] = rdfrac();
  FOR(i, 1, n + 1) to[i] = rd(), g[to[i]].pb(i);
  FOR(i, 1, n + 1) Q[i] = rdfrac();
  for (int i = 1; i <= n; ++i) {
    if (!vis[i]) {
      ++tot;
      cyc(i);
    }
  }
  FOR(i, 1, n + 1) {
    if (!on_cyc[i] && !dvis[i]) {
      dfs(i);
    }
  }
  FOR(i, 1, n + 1) {
    if (!on_cyc[i] && on_cyc[to[i]]) {
      P[to[i]] = (P[to[i]] + (p + 1 - P[to[i]]) * dp[i] % p * Q[i] % p) % p;
    }
  }
  FOR(i, 1, tot + 1) {
    if (!C[i].empty()) {
      elimination(C[i]);
    }
  }
  FOR(i, 1, n + 1) {
    cout << dp[i] << ' ';
  }
  cout << '\n';
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

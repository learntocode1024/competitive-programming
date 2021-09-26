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
const int N = 5e4+5;
const int K = 155;
const int mod = 10007;
int k, n;
vector<int> G[N];
inline void red(int &x) { if (x >= mod) x -= mod; }

int f[N][K];

void dfs1(int u, int fa) {
  f[u][0] = 1;
  for (auto v : G[u]) {
    if (v == fa) continue;
    dfs1(v, u);
    for (int i = 0; i <= k; ++i) {
      if (i) red(f[u][i] += f[v][i - 1]);
      red(f[u][i] += f[v][i]);
    }
  }
}

int tmp[K];

void dfs2(int u, int fa) {
  if (u != 1) {
    for (int i = 0; i <= k; ++i) {
      tmp[i] = f[fa][i];
    }
    for (int i = 0; i <= k; ++i) {
      if (i) red(tmp[i] += mod - f[u][i - 1]);
      red(tmp[i] += mod - f[u][i]);
    }
    for (int i = 0; i <= k; ++i) {
      if (i) red(f[u][i] += tmp[i - 1]);
      red(f[u][i] += tmp[i]);
    }
  }
  for (auto v : G[u]) {
    if (v == fa) continue;
    dfs2(v, u);
  }
}

int S[K][K], fac[N];

void solve() {
  n = rd(), k = rd();
  FOR(i, 1, n) {
    int u = rd(), v = rd();
    G[u].pb(v);
    G[v].pb(u);
  }
  dfs1(1, 0);
  dfs2(1, 0);
  fac[0] = 1;
  for (int i = 1; i < k + 1; ++i) {
    fac[i] = fac[i - 1] * i % mod;
  }
  S[0][0] = 1;
  S[1][1] = 1;
  for (int i = 2; i <= k; ++i) {
    for (int j = 1; j <= i; ++j) {
      red(S[i][j] = (S[i-1][j-1] + j * S[i-1][j]) % mod);
    }
  }
  for (int i = 1; i <= n; ++i) {
    int ans = 0;
    for (int j = 0; j <= k; ++j) {
      red(ans += S[k][j] * fac[j] % mod * f[i][j] % mod);
    }
    cout << ans << '\n';
  }
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

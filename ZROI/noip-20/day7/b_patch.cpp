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
const int N = 3e5+5;
const i64 p = 1e9+7;
int n, k;
vector<int> g[N];
i64 ans;
int d[N], son[N];

inline void red(i64 &x) { if (x >= p) x -= p; }

int h[N], vl[N], nxt[N], pre[N], hv[N], tot;

void dfs(int u, int fa) {
  d[u] = 1;
  for (auto v : g[u]) {
    if (fa != v) {
      dfs(v, u);
      if (d[v] > d[son[u]]) {
        son[u] = v;
      }
    }
  }
  d[u] = d[son[u]] + 1;
}

void dp(int u, int fa) {
  vl[++tot] = 1;
  h[u] = tot;
  hv[u] = tot;
  if (son[u]) {
    int v = son[u];
    dp(son[u], u);
    nxt[h[u]] = h[v];
    pre[h[v]] = h[u];
    hv[u] = hv[v];
    if (d[v] > k) {
      hv[u] = pre[hv[u]];
    }
    if (d[u] > k) ans += vl[hv[u]];
  }
  for (auto v : g[u]) {
    if (fa != v && son[u] != v) {
      dp(v, u);
      if (d[u] > k) {
        for (int i1 = pre[hv[u]], i2 = h[v]; i2 && i1; i1 = pre[i1], i2 = nxt[i2]) {
          ans += 1ll * vl[i1] * vl[i2];
        }
      } else {
        int i2 = h[v];
        for (int t = 0; t < k - d[u] && i2; ++t) i2 = nxt[i2];
        for (int i1 = hv[u]; i1 && i2; i2 = nxt[i2], i1 = pre[i1]) {
          ans += 1ll * vl[i1] * vl[i2];
        }
      }
      for (int i1 = nxt[h[u]], i2 = h[v]; i2; i1 = nxt[i1], i2 = nxt[i2]) {
        vl[i1] += vl[i2];
      }
    }
  }
}

void solve() {
  n = rd(), k = rd();
  FOR(i, 1, n) {
    int u = rd(), v = rd();
    g[u].pb(v);
    g[v].pb(u);
  }
  dfs(1, 0);
  dp(1, 0);
  i64 kk = 1ll * k * (k + 1) / 2;
  kk %= p;
  cout << ans * kk % p << '\n';
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

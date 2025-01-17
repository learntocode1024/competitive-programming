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
i64 ans, cur, all;
int c[N];
int d[N];

inline void red(i64 &x) { if (x >= p) x -= p; }

inline void add(int x, int v) {
  while (x <= n) {
    c[x] += v;
    x += x & -x;
  }
}

inline int get(int x) {
  int ret = 0;
  while (x) {
    ret += c[x];
    x -= x & -x;
  }
  return ret;
}

void dfs(int u, int fa) {
  d[u] = d[fa] + 1;
  red(cur += all - get(u));
  ++all;
  add(u, 1);
  if (d[u] == k) {
    red(ans += cur);
  } else if (d[u] < k) {
    for (auto v : g[u]) {
      if (v != fa) dfs(v, u);
    }
  }
  add(u, -1);
  --all;
  cur = (cur + p - all + get(u)) % p;
}

void solve() {
  n = rd(), k = rd();
  FOR(i, 1, n) {
    int u = rd(), v = rd();
    g[u].pb(v);
    g[v].pb(u);
  }
  d[0] = -1;
  for (int i = 1; i <= n; ++i) {
    dfs(i, 0);
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

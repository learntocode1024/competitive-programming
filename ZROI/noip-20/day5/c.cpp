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
long long rdll() {
  unsigned long long u = 0, s = 0;
  while (*o && *o <= 32) ++o;  // skip whitespaces...
  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o;  // skip sign
  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0');  // u * 10 = u * 8 + u * 2 :)
  return static_cast<long long>((u ^ s) + !!s);
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
const int B = 64, N = 4e5+5;
const int w = 60;
vector<int> g[N];
i64 a[N];
int n;

struct DS {
  i64 s[B];
  inline bool ins(i64 x) {
    for (int i = w; i + 1; i--) {
      if (!(x >> i))
        continue;
      if (!s[i]) {
        s[i] = x;
        return 1;
      }
      x ^= s[i];
    }
    return 0;
  }
  inline i64 gans() {
    i64 ret = 0;
    for (int i = w; i + 1; i--) {
      if (ret < (ret ^ s[i])) ret ^= s[i];
    }
    return ret;
  }
  friend DS merge(const DS &lhs, const DS &rhs) {
    DS ret = lhs;
    FOR(i, 0, w + 1) ret.ins(rhs.s[i]);
    return ret;
  }
} pa[B], pb[B], pd[B][B], da, db;
int ta, tb;
int ia[N], ib[N];

void dfs1(int u, int fa) {
  ia[u] = ta;
  for (auto v : g[u]) {
    if (v != fa) dfs1(v, u);
  }
  if (da.ins(a[u])) pa[++ta] = da;
}
void dfs2(int u, int fa) {
  ib[u] = tb;
  for (auto v : g[u]) {
    if (v != fa) dfs2(v, u);
  }
  if (db.ins(a[u])) pb[++tb] = db;
}
void solve() {
  n = rd();
  FOR(i, 0, n) rd();
  FOR(i, 1, n + 1) a[i] = IO::rdll();
  FOR(i, 1, n) {
    int u = rd(), v = rd();
    g[u].pb(v);
    g[v].pb(u);
  }
  dfs1(1, 0);
  FOR(i, 1, n + 1) reverse(g[i].begin(), g[i].end());
  dfs2(1, 0);
  FOR(i, 0, ta + 1) FOR(j, 0, tb + 1) pd[i][j] = merge(pa[i], pb[j]);
  FOR(i, 1, n + 1) cout << pd[ia[i]][ib[i]].gans() << '\n';
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

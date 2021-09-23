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
#include <set>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

/********************************** buffer IO *********************************/
namespace IO {
char in[1 << 26];  // sizeof in varied in problem
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
const int N = 100005;
int n, m;

/* struct edge { */
/*   int u, v, w; */
/*   edge() = default; */
/*   edge(int _u, int _v, int _w) { */
/*     u = min(_u, _v); */
/*     v = max(_u, _v); */
/*     w = _w; */
/*   } */
/*   bool operator< (const edge &rhs) const { */
/*     return w != rhget<0>(s) ? w < rhget<0>(s) : (u != rhs.u ? u < rhs.u : (v < rhs.v)); */
/*   } */
/* }; */
using edge = tuple<int, int, int>;

/* using mi = set<edge>; */
typedef tree<edge, null_type, less<edge>, rb_tree_tag, null_node_update> mi;
unordered_map<i64, int> gw;
mi a, g[N];
i64 s3[N];
multiset<i64> ss3;
const int C = 7;

inline void sum3(int);

inline void ins() {
  int u = rd(), v = rd(), w = rd();
  if (u > v) swap(u, v);
  edge e(w, u, v);
  a.insert(e);
  g[u].insert(e);
  g[v].insert(e);
  gw[1ll * u * n + v] = w;
  sum3(u), sum3(v);
}

inline void del() {
  int u = rd(), v = rd();
  if (u > v) swap(u, v);
  edge e(gw[1ll * u * n + v], u, v);
  a.erase(e);
  g[u].erase(e);
  g[v].erase(e);
  sum3(u), sum3(v);
}

void sum3(int u) {
  i64 res = 0;
  if (g[u].size() < 3) res = 1e18;
  else {
    auto it = g[u].begin();
    FOR(i, 0, 3) {
      res += get<0>(*it);
      ++it;
    }
  }
  if (s3[u]) {
    ss3.erase(ss3.find(s3[u]));
  }
  if (res < 1e18) ss3.insert(res), s3[u] = res;
}

mi vis;
edge comp[C];
int cnt;

i64 cal(edge e) {
  int u = get<1>(e);
  auto it = g[u].begin();
  FOR(i, 0, min(3, (int)g[u].size())) {
    vis.insert(*it);
    ++it;
  }
  u = get<2>(e);
  it = g[u].begin();
  FOR(i, 0, min(3, (int)g[u].size())) {
    vis.insert(*it);
    ++it;
  }
  i64 ret = get<0>(e);
  for (int i = 0; i < cnt; ++i) {
    if (vis.find(comp[i]) == vis.end()) {
      ret += get<0>(comp[i]);
      break;
    }
  }
  vis.clear();
  return ret;
}

int sol() {
  auto it = a.begin();
  for (int i = 0; it != a.end() && i < C; ++i) {
    cnt = i + 1;
    comp[i] = *it;
  }
  i64 ret = 1e18;
  if (ss3.size()) ret = *ss3.begin();
  edge mn = *a.begin();
  int u = get<1>(mn);
  it = g[u].begin();
  FOR(i, 0, min(3, (int)g[u].size())) {
    chkmin(ret, cal(*it));
    ++it;
  }
  u = get<2>(mn);
  it = g[u].begin();
  FOR(i, 0, min(3, (int)g[u].size())) {
    chkmin(ret, cal(*it));
    ++it;
  }
  return ret;
}


void solve() {
  n = rd(), m = rd();
  FOR(i, 0, m) ins();
  int q = rd();
  while ((cout << sol() << '\n') && q--) {
    if (rd() == 0) del();
    else ins();
  }
}

int main() {
  ios::sync_with_stdio(0);
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

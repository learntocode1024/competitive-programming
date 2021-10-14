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
#include <queue>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

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
  *s = '\0';
  return s;
}
}  // namespace IO

/********************************* utility ************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef pair<int, int> pii;
typedef pair<int, i64> pil;
typedef pair<i64, int> pli;
#define pb(x) push_back(x)
#define eb emplace_back
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
const int N = 1e6+5, M = 2e6+5;
int u[M], v[M], w[M];
int f[N];
i64 d[N], dp[N], val[N];
bool vis[N];
int n, m, V;
vector<pii> g[N];

inline void gdis() {
  FOR(i, 1, n + 1) d[i] = 1e18, vis[i] = 0;
  static priority_queue<pli> pq;
  d[V] = 0;
  pq.push(mkp(0, V));
  while (!pq.empty()) {
    int u = pq.top().se;
    i64 w = d[u];
    vis[u] = 1;
    pq.pop();
    for (auto v : g[u]) {
      if (d[v.fi] > w + v.se) {
        d[v.fi] = w + v.se;
        f[v.fi] = u;
        pq.push(mkp(-d[v.fi], v.fi));
      }
    }
    while (!pq.empty() && vis[pq.top().se]) pq.pop();
  }
}

inline void run_dp() {
  FOR(i, 1, n + 1) dp[i] = 1e18, vis[i] = 0;
  static priority_queue<pli> pq;
  dp[V] = 0;
  pq.push(mkp(0, V));
  while (!pq.empty()) {
    int u = pq.top().se;
    i64 w = dp[u];
    vis[u] = 1;
    pq.pop();
    for (auto v : g[u]) {
      i64 wto = max(val[v.fi], w + v.se);
      if (dp[v.fi] > wto) {
        dp[v.fi] = wto;
        pq.push(mkp(-wto, v.fi));
      }
    }
    while (!pq.empty() && vis[pq.top().se]) pq.pop();
  }
}

int fx[N];
int get(int x) {
  if (x == fx[x]) return x;
  return fx[x] = get(fx[x]);
}
bool used[M];
inline void calc(int u, int v, i64 w) {
	if (f[u] == v && !used[u]) return used[u] = 1, void();
	if (f[v] == u && !used[v]) return used[v] = 1, void();
  u = get(u), v = get(v);
  while (u != v) {
    if (d[u] < d[v]) swap(u, v);
    val[u] = w - d[u];
    fx[u] = f[u];
    u = get(u);
  }
}

int eg[M];

inline void gval() {
  int tot = 0;
  FOR(i, 1, n + 1) fx[i] = i, val[i] = 1e18;
  for (int i = 0; i < m; ++i) {
    if (1 || u[i] != f[v[i]] && v[i] != f[u[i]]) {
      eg[tot++] = i;
    }
  }
  sort(eg, eg + tot, [] (int x, int y) { return d[u[x]] + d[v[x]] + w[x] < d[u[y]] + d[v[y]] + w[y]; });
  FOR(i, 0, tot) {
    int cur = eg[i];
    calc(u[cur], v[cur], d[u[cur]] + d[v[cur]] + w[cur]);
  }
}

void solve() {
  n = rd(), m = rd(), V = rd();
  FOR(i, 0, m) {
    u[i] = rd();
    v[i] = rd();
    w[i] = rd();
    g[u[i]].eb(v[i], w[i]);
    g[v[i]].eb(u[i], w[i]);
  }
  gdis();
  gval();
  run_dp();
  FOR(i, 1, n + 1) cout << (dp[i] == 1e18 ? -1 : dp[i]) << ' ';
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

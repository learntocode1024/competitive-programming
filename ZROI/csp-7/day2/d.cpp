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
const int N = 1000005;
int n, m;
i64 M, NN, B;
vector<int> G[N];
int ord[N], ind[N];

namespace strip {
int deg[N];
bool vis[N];
priority_queue<pii> pq;
inline void work() {
  for (int i = 1; i <= n; ++i) {
    deg[i] = G[i].size();
    pq.push(mkp(-deg[i], i));
  }
  int c = 0, tot = 0;
  while (!pq.empty() && tot < n) {
    if (vis[pq.top().se]) {
      pq.pop();
      continue;
    }
    int u = pq.top().se;
    ord[tot++] = u;
    vis[u] = 1;
    if (-pq.top().fi > c) {
      c = ind[u] = -pq.top().fi;
    }
    pq.pop();
    for (auto v : G[u]) {
      if (vis[v]) continue;
      --deg[v];
      pq.push(mkp(-deg[v], v));
    }
  }
  reverse(ord, ord + n);
}
} // delete nodes by degrees

namespace gen {
int cn[N], cm[N], ca[N];
int fa[N];
bool vis[N], vvis[N];
int get(int x) {
  if (x == fa[x]) return x;
  fa[x] = get(fa[x]);
  return fa[x];
}
i64 val = -1152921504606846976ll;
int ansk;
void work() {
  for (int i = 1; i <= n; ++i) {
    fa[i] = i;
  }
  for (int i = 0; i < n; ++i) {
    int u = ord[i];
    ca[u] = G[u].size();
    cn[u] = 1;
    vis[u] = 1;
    for (auto v : G[u]) {
      if (!vis[v]) continue;
      int o = get(v);
      if (o == u) {
        ++cm[u];
        continue;
      }
      ca[u] += ca[o];
      cn[u] += cn[o];
      cm[u] += cm[o] + 1;
      fa[o] = u;
    }
    if (ind[u]) {
      int ck = ind[u];
      for (int t = i; t >= 0; --t) {
        if (ind[ord[t]] && ind[ord[t]] != ck) break;
        int o = get(ord[t]);
        if (vvis[o]) continue;
        i64 score = M * cm[o] - NN * cn[o] + B * (ca[o] - cm[o] * 2);
        if (score > val) {
          ansk = ck, val = score;
          ansk = ansk;
        }
        vvis[o] = 1;
      }
    }
  }
  cout << ansk << ' ' << val << '\n';
}
} // reform the graph in DSU

void solve() {
  n = rd(), m = rd();
  M = rd(), NN = rd(), B = rd();
  for (int i = 0; i < m; ++i) {
    int u = rd(), v = rd();
    G[u].pb(v);
    G[v].pb(u);
  }
  strip::work();
  gen::work();
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

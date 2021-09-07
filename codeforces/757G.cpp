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
typedef pair<i64, i64> pll;
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

const int N = 200005;
vector<int> G[N];
vector<pii> G1[N];
int n, q;

namespace LCA {
int dep[N], dfn[N], rmq[21][N << 1], tot;
i64 d1[N];
void dfs(int u, int fa) {
  dfn[u] = ++tot;
  dep[u] = dep[fa] + 1;
  rmq[0][tot] = u;
  for (auto v : G1[u]) {
    if (v.fi != fa) d1[v.fi] = d1[u] + v.se, dfs(v.fi, u), rmq[0][++tot] = u;
  }
}
inline int gmin(int a, int b) {
  return dep[a] < dep[b] ? a : b;
}
inline void init() {
  dfs(1, 0);
  FOR(i, 1, 21) {
    for (int j = 1; j + (1 << i) - 1 <= tot; ++j) {
      rmq[i][j] = gmin(rmq[i - 1][j], rmq[i - 1][j + (1 << (i - 1))]);
    }
  }
}
int lca(int a, int b) {
  int x = dfn[a], y = dfn[b];
  if (x > y) swap(x, y);
  int t = 31 - __builtin_clz(y - x + 1);
  return gmin(rmq[t][x], rmq[t][y + 1 - (1 << t)]);
}
inline i64 dis(int a, int b) {
  return d1[a] + d1[b] - (d1[lca(a, b)] << 1);
}
}
using LCA::dis;
struct seg {
  struct node {
    int l, r;
    i64 s;
  } a[N << 8];
  int tot;
  void add(int &p, int l, int r, int x, i64 v) {
    if (!p) p = ++tot;
    if (r - l == 1) {
      a[p].s += v;
      return;
    }
    int mid = (l + r) >> 1;
    if (x < mid) add(a[p].l, l, mid, x, v);
    else add(a[p].r, mid, r, x, v);
    a[p].s = a[a[p].l].s + a[a[p].r].s;
  }
  i64 sum(int p, int l, int r, int s, int t) {
    if (!p) return 0ll;
    if (l == s && r == t) {
      return a[p].s;
    }
    int mid = (l + r) >> 1;
    i64 ret = 0;
    if (s < mid) ret += sum(a[p].l, l, mid, s, min(t, mid));
    if (t > mid) ret += sum(a[p].r, mid, r, max(s, mid), t);
    return ret;
  } 
};
//seg Ts, Tn;
using node = pair<int, pll>;
vector<node> s[N];

int a[N], pos[N];
int rt, all, rtcs[N], rtfs[N], rtn[N];

bool vis[N];
int sz[N], son[N], f[N];
void centroid(int u, int fa) {
  sz[u] = 1;
  son[u] = 0;
  for (auto v : G[u]) {
    if (vis[v] || v == fa) continue;
    centroid(v, u);
    sz[u] += sz[v];
    chkmax(son[u], sz[v]);
  }
  chkmax(son[u], all - sz[u]);
  if (son[u] < son[rt]) rt = u;
}

void work(int u, int fa) {
  sz[u] = 1;
  if (f[rt]) {
    s[rt].eb(pos[u], mkp(dis(u, rt), dis(u, f[rt])));
  } else {
    s[rt].eb(pos[u], mkp(dis(u, rt), 0));
  }
//  Ts.add(rtcs[rt], 1, n + 1, pos[u], dis(u, rt));
//  Tn.add(rtn[rt], 1, n + 1, pos[u], 1);
//  if (f[rt]) {
//    Ts.add(rtfs[rt], 1, n + 1, pos[u], dis(u, f[rt]));
//  }
  for (auto v : G[u]) {
    if (vis[v] || v == fa) continue;
    work(v, u);
    sz[u] += sz[v];
  }
}

void build(int u) {
  work(u, 0);
  vis[u] = 1;
  for (auto v : G[u]) {
    if (vis[v]) continue;
    rt = 0;
    all = sz[v];
    centroid(v, u);
    f[rt] = u;
    build(rt);
  }
}

i64 query(int l, int r, int u) {
  i64 ret = 0;
  int c = u;
  ++r;
  while (c) {
    if (s[c].empty()) {
      c = f[c];
      continue;
    }
    auto L = lower_bound(begin(s[c]), end(s[c]), mkp(l, mkp(0ll, 0ll)));
    if (L == s[c].end()) {
      c = f[c];
      continue;
    }
    auto R = lower_bound(begin(s[c]), end(s[c]), mkp(r, mkp(0ll, 0ll)));
    if (R == L) {
      c = f[c];
      continue;
    }
    --R;
    i64 cnt = R - L + 1;
    ret += R->se.fi - R->se.se;
    if (L != begin(s[c])) --L, ret -= L->se.fi - L->se.se;
    ret += cnt * dis(c, u);
    if (f[c]) ret -= cnt * dis(f[c], u);
    c = f[c];
  }
  return ret;
}

void modify(int x) {
  int c = a[x];
  while (c) {
    auto it = lower_bound(begin(s[c]), end(s[c]), mkp(x, mkp(0ll, 0ll)));
    auto itr = it + 1;
    if (itr != s[c].end() && itr->fi == x + 1) {
      i64 x = 0, y = 0;
      if (it != s[c].begin()) x = (it - 1)->se.fi, y = (it - 1)->se.se;
      it->se.fi = x + itr->se.fi - it->se.fi;
      it->se.se = y + itr->se.se - it->se.se;
    } else {
      it->fi += 1;
    }
    c = f[c];
  }
  c = a[x + 1];
  while (c) {
    auto it = lower_bound(begin(s[c]), end(s[c]), mkp(x + 1, mkp(0ll, 0ll)));
    if (it != s[c].begin() && (it - 1)->fi == x) {
      c = f[c];
      continue;
    } else {
      it->fi -= 1;
    }
    c = f[c];
  }
  ++pos[a[x]];
  --pos[a[x + 1]];
  swap(a[x], a[x + 1]);
}

const i64 mask = (1 << 30) - 1;
i64 last = 0;
void solve() {
  n = rd(), q = rd();
  FOR(i, 1, n + 1) a[i] = rd();
  FOR(i, 1, n + 1) pos[a[i]] = i;
  FOR(i, 1, n) {
    int u = rd(), v = rd(), w = rd();
    G[u].pb(v);
    G[v].pb(u);
    G1[u].eb(v,w);
    G1[v].eb(u,w);
  }
  LCA::init();
  rt = 0;
  all = n;
  centroid(1, 0);
  build(rt);
  FOR(i, 1, n + 1) sort(begin(s[i]), end(s[i]));
  FOR(i, 1, n + 1) {
    for (int j = 1; j < s[i].size(); ++j) {
      s[i][j].se.fi += s[i][j - 1].se.fi;
      s[i][j].se.se += s[i][j - 1].se.se;
    }
  }
  while (q--) {
    int op = rd();
    if (op == 1) {
      int l = rd() ^ last, r = rd() ^ last, u = rd() ^ last;
      cout << (last = query(l, r, u)) << '\n';
      last &= mask;
    } else {
      modify(rd() ^ last);
    }
  }
}

int main() {
  son[0] = 1e8;
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
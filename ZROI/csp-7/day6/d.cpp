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
const int N = 2e5+5;
vector<int> g[N];

struct DS {
  struct node {
    int l, r;
    int c;
  } a[N << 5];
  int tot;
  inline void up(int p) {
    a[p].c = a[a[p].l].c + a[a[p].r].c;
  }
  #define lc a[p].l
  #define rc a[p].r
  #define P a[p]
  void ins(int &p, int l, int r, int t) {
    if (p == 0) p = ++tot;
    if (r - l == 1) {
      ++P.c;
      return;
    }
    int mid = (l + r) >> 1;
    if (t < mid) ins(lc, l, mid, t);
    else ins(rc, mid, r, t);
    up(p);
  }
  void dec(int &p, int l, int r, int t) {
    if (p == 0) p = ++tot;
    if (r - l == 1) {
      --P.c;
      return;
    }
    int mid = (l + r) >> 1;
    if (t < mid) dec(lc, l, mid, t);
    else dec(rc, mid, r, t);
    up(p);
  }
  void merge(int &p, int q) {
    if (!p || !q) {
      p = p | q;
      return;
    }
    a[p].c += a[q].c;
    merge(a[p].l, a[q].l);
    merge(a[p].r, a[q].r);
  }
  int rnk(int p, int l, int r, int k) {
    if (p == 0) return 0;
    if (r - l == 1) return a[p].c;
    int mid = (l + r) >> 1;
    if (k < mid) return rnk(lc, l, mid, k);
    return a[lc].c + rnk(rc, mid, r, k);
  }
  int kth(int p, int l, int r, int k) {
    if (p == 0) return -1;
    if (r - l == 1) return l;
    int mid = (l + r) >> 1;
    if (a[lc].c >= k) return kth(lc, l, mid, k);
    return kth(rc, mid, r, k - a[lc].c);
  }
  inline int pre(int p, int l, int r, int k) {
    return kth(p, l, r, rnk(p, l, r, k));
  }
  inline int nxt(int p, int l, int r, int k) {
    return kth(p, l, r, rnk(p, l, r, k) + 1);
  }
  int rnkr(int p, int q, int l, int r, int k) {
    if (p == 0) return 0;
    if (r - l == 1) return a[p].c - a[q].c;
    int mid = (l + r) >> 1;
    if (k < mid) return rnkr(lc, a[q].l, l, mid, k);
    return a[lc].c - a[a[q].l].c + rnkr(rc, a[q].r, mid, r, k);
  }
  int kthr(int p, int q, int l, int r, int k) {
    if (p == 0) return -1;
    if (r - l == 1) return l;
    int mid = (l + r) >> 1;
    int cnt = a[lc].c - a[a[q].l].c;
    if (cnt >= k) return kthr(lc, a[q].l, l, mid, k);
    return kthr(rc, a[q].r, mid, r, k - cnt);
  }
  inline int prer(int p, int q, int l, int r, int k) {
    return kthr(p, q, l, r, rnkr(p, q, l, r, k));
  }
  inline int nxtr(int p, int q, int l, int r, int k) {
    return kthr(p, q, l, r, rnkr(p, q, l, r, k) + 1);
  }
  // void walk(int p, int q, int l, int r) {
  //   if (r - l == 1) {
  //     cerr << "[" << l << ": " << a[p].c - a[q].c << "] ";
  //     return;
  //   }
  //   int mid = (l + r) >> 1;
  //   walk(a[p].l, a[q].l, l, mid);
  //   walk(a[p].r, a[q].r, mid, r);
  // }
} A;

int rt1[N], rt2[N];
int sz[N];
int ans = 1e7;
int n;

inline int getans(int a, int b, int c) {
  return max(a, max(b, c)) - min(a, min(b, c));
}

void dfs1(int u, int fa) {
  sz[u] = 1;
  for (auto v : g[u]) {
    if (v == fa) continue;
    dfs1(v, u);
    sz[u] += sz[v];
    A.merge(rt1[u], rt1[v]);
  }
  A.ins(rt1[u], 1, n + 1, sz[u]);
  if (sz[u] > 1) {
    int ot = n - sz[u];
    int h = sz[u] / 2;
    int v1 = A.pre(rt1[u], 1, n + 1, h);
    int v2 = A.nxt(rt1[u], 1, n + 1, h);
    chkmin(ans, getans(ot, v1, sz[u] - v1));
    chkmin(ans, getans(ot, v2, sz[u] - v2));
  }
}

void dfs2(int u, int fa) {
  A.dec(rt1[1], 1, n + 1, sz[u]);
  for (auto v : g[u]) {
    if (v == fa) continue;
    dfs2(v, u);
    A.merge(rt2[u], rt2[v]);
  }
  A.ins(rt2[u], 1, n + 1, sz[u]);
  A.ins(rt1[1], 1, n + 1, sz[u]);
  int ot = n - sz[u];
  int h = ot / 2;
  int v1 = A.prer(rt1[1], rt2[u], 1, n + 1, h);
  int v2 = A.nxtr(rt1[1], rt2[u], 1, n + 1, h);
  chkmin(ans, getans(ot - v1, v1, sz[u]));
  chkmin(ans, getans(ot - v2, v2, sz[u]));
}

void solve() {
  cin >> n;
  FOR(i, 1, n) {
    int u, v;
    cin >> u >> v;
    g[u].pb(v);
    g[v].pb(u);
  }
  dfs1(1, 0);
  cerr << ans << '\n';
  dfs2(1, 0);
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
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

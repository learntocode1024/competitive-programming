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
#include <cassert>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

/********************************** buffer IO *********************************/
namespace IO {
char in[1 << 25];  // sizeof in varied in problem
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
const int N = 2e5+5;
vector<int> g[N];
int a[N], b[N], c[N];
int n, m, k, AL;

bool comp(int x, int y) {
  return a[x] < a[y];
}
int ord[N];

vector<int> qp[N];

struct qry {
  int id;
  int V;
  inline void init(int x) {
    id = x;
    V = rd();
    int _p = rd();
    FOR(i, 0, _p) qp[x].pb(rd());
  }
  bool operator<(const qry &rhs) const {
    return V < rhs.V;
  }
} qy[N];
int ans[N];

struct SEG {
  int a[N << 2];
  void _add(int p, int l, int r, int t, int v) {
    if (r - l == 1) {
      a[p] += v;
      return;
    }
    int mid = (l + r) >> 1;
    if (t < mid) _add(p<<1, l, mid, t, v);
    else _add(p<<1|1, mid, r, t, v);
    a[p] = max(a[p<<1], a[p<<1|1]);
  }
  inline void add(int x, int v) {
    if (v != 0) _add(1, 1, n + 1, x, v);
  }
  inline int qry() {
    return a[1];
  }
} T;

int rt[N];
struct SEG2 {
  int tot = 0;
  struct node {
    int l, r;
    int c, s;
  } a[N << 5];
  int get(int p) { return a[rt[p]].s; }
  void _merge(int &p, int q, int l, int r) {
    if (!p || !q) {
      p |= q;
      return;
    }
    if (r - l == 1) {
      a[p].c += a[q].c;
      a[p].s = ((a[p].c % k == 0) && a[p].c > 0);
      return;
    }
    int mid = (l + r) >> 1;
    _merge(a[p].l, a[q].l, l, mid);
    _merge(a[p].r, a[q].r, mid, r);
    a[p].s = a[a[p].l].s + a[a[p].r].s;
  }
  void _ins(int &p, int l, int r, int t) {
    if (!p) p = ++tot;
    if (r - l == 1) {
      ++a[p].c;
      a[p].s = ((a[p].c % k == 0) && a[p].c > 0);
      return;
    }
    int mid = (l + r) >> 1;
    if (t < mid) _ins(a[p].l, l, mid, t);
    else _ins(a[p].r, mid, r, t);
    a[p].s = a[a[p].l].s + a[a[p].r].s;
  }
  inline void merge(int &p, int q) { _merge(p, q, 0, AL); }
  inline void ins(int &p, int v) { _ins(p, 0, AL, v); }
} T2;

struct DSU {
  int f[N], sz[N];
  int stk[N], tot;
  bool msk[N];
  inline void _init(int x) {
    f[x] = x;
    sz[x] = 1;
    T2.ins(rt[x], b[x]);
    T.add(x, T2.get(x));
  }
  int get(int x) {
    if (f[x] == x) return x;
    return f[x] = get(f[x]);
  }
  inline void Union(int u, int v) {
    if (sz[v] > sz[u]) swap(u, v);
    int f1 = get(u), f2 = get(v);
    if (f1 == f2) return;
    sz[f1] += sz[f2];
    f[f2] = f1;
    T.add(f2, -T2.get(f2));
    T.add(f1, -T2.get(f1));
    T2.merge(rt[f1], rt[f2]);
    T.add(f1, T2.get(f1));
  }
  inline void init(int x) {
    _init(x);
    for (auto v : g[x]) {
      if (f[v] != 0) Union(x, v);
    }
  }
  inline void mask(const vector<int> &t) {
    for (auto v : t) {
      if (f[v] == 0) continue;
      int ff = get(v);
      if (!msk[ff]) {
        msk[ff] = 1;
        stk[tot++] = ff;
      }
    }
    FOR(i, 0, tot) {
      T.add(stk[i], -T2.get(stk[i]));
    }
  }
  inline void unmask() {
    FOR(i, 0, tot) {
      T.add(stk[i], T2.get(stk[i]));
      msk[stk[i]] = 0;
    }
    tot = 0;
  }
} D;

inline void discrete() {
  int tot = 0;
  FOR(i, 1, n + 1) c[tot++] = b[i];
  sort(c, c + tot);
  AL = unique(c, c + tot) - c;
  FOR(i, 1, n + 1) b[i] = lower_bound(c, c + AL, b[i]) - c;
}

void solve() {
  n = rd(), m = rd(), k = rd();
  FOR(i, 1, n + 1) ord[i] = i;
  FOR(i, 1, n + 1) a[i] = rd();
  FOR(i, 1, n + 1) b[i] = rd();
  ++AL;
  sort(ord + 1, ord + n + 1, comp);
  FOR(i, 0, m) {
    int u = rd(), v = rd();
    g[u].pb(v);
    g[v].pb(u);
  }
  int q = rd();
  FOR(i, 0, q) qy[i].init(i);
  discrete();
  sort(qy, qy + q);
  int l = 0;
  for (int i = 0; i < q; ++i) {
    while (l < n && a[ord[l + 1]] <= qy[i].V) ++l, D.init(ord[l]);
    D.mask(qp[qy[i].id]);
    ans[qy[i].id] = T.qry();
    D.unmask();
  }
  FOR(i, 0, q) cout << ans[i] << '\n';
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


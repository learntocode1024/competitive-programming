/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Jul 18, 2021
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
typedef long long LL;
typedef unsigned long long ULL;

#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX 2000005

template<typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  a = min(a, b);
}

int n, q;
int a[MX], pre[MX], col[MX];

struct qry {
  int l, r, id;
  bool operator< (const qry &b) const {
    return l > b.l;
  }
} c[MX];

namespace seg1 {
int low[MX << 2];
void build(int p, int l, int r) {
  if (l + 1 == r) {
    low[l] = pre[l];
    return;
  }
  int mid = l + (r - l) / 2;
  int lc = p << 1, rc = lc + 1;
  build(lc, l, mid);
  build(rc, mid, r);
  low[p] = min(low[lc], low[rc]);
}

int s, t;
int get(int p, int l, int r) {
  if (r - l == 1) return l;
  int mid = l + (r - l) / 2;
  int lc = p << 1, rc = lc + 1;
  if (mid >= t || low[rc] >= s) return get(lc, l, mid);
  return get(rc, mid, r);
}
}

namespace seg2 {
struct node {
  int l, x;
  int t = -1;
  void tag(int a) {
    x += l + a;
    t = a;
  }
} a[MX << 2];
void up(int u) {
  int lc = u << 1, rc = lc + 1;
  if (a[lc].x <= a[rc].x) {
    a[u].l = a[lc].l;
    a[u].x = a[lc].x;
  } else {
    a[u].l = a[rc].l;
    a[u].x = a[rc].x;
  }
}
void build(int p, int l, int r) {
  a[p].l = l;
  a[p].t = -1;
  if (r - l == 1) {
    return;
  }
  int mid = l + (r - l) / 2;
  int lc = p << 1, rc = lc + 1;
  build(lc, l, mid);
  build(rc, mid, r);
}
void down(int u) {
  if (a[u].t != -1) {
    int lc = u << 1, rc = lc + 1;
    a[lc].tag(a[u].t);
    a[rc].tag(a[u].t);
    a[u].t = -1;
  }
}
int get(int p, int l, int r, int s, int t) {
  if (l == s && r == t) {
    return a[p].x;
  }
  int mid = l + (r - l) / 2;
  int lc = p << 1, rc = lc + 1;
  int ret = 1e7;
  down(p);
  if (s < mid) chkmin(ret, get(lc, l, mid, s, min(mid, t)));
  if (t > mid) chkmin(ret, get(rc, mid, r, max(s, mid), t));
  return ret;
}
void assign(int p, int l, int r, int s, int t, int v) {
  if (l == s && r == t) {
    a[p].tag(v);
    return;
  }
  int mid = l + (r - l) / 2;
  int lc = p << 1, rc = lc + 1;
  down(p);
  if (s < mid) assign(lc, l, mid, s, min(mid, t), v);
  if (t > mid) assign(rc, mid, r, max(mid, s), t, v);
  up(p);
}
}
int ans[MX];
void solve() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i <= n; ++i) col[i] = -1;
  for (int i = 0; i < n; ++i) {
    pre[i] = col[a[i]];
    col[a[i]] = i;
  }
  seg1::build(1, 0, n);
  cin >> q;
  for (int i = 0; i < q; ++i) {
    cin >> c[i].l >> c[i].r;
    --c[i].l, --c[i].r;
    c[i].id = i;
  }
  sort(c, c + q);
  int cur = 0;
  for (int i = 0; i <= n; ++i) col[i] = n;
  seg2::build(1, 0, n);
  for (int i = n - 1; i >= 0; --i) {
    seg2::assign(1, 0, n, i, col[a[i]], -i);
    col[a[i]] = i;
    while (cur < q - 1 && c[cur].l == i) {
      seg1::s = c[cur].l, seg1::t = c[cur].r + 1;
      int r0 = seg1::get(1, 0, n);
      ans[c[cur].id] = seg2::get(1, 0, n, i, r0 + 1);
      ++cur;
    }
  }
  for (int i = 0; i < q; ++i) {
    cout << ans[i] << '\n';
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  int T = 1;
  while (T--)
    solve();
  return 0;
}


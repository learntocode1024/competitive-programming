#include <algorithm>
#include <climits>
#include <iostream>

#include "utils"
#include "io"

const int N = 200005;

int n, m;
i64 ori;

struct segt {
  struct node {
    i64 c = -1e18, t;
  } a[N << 2];
  #define lc (p << 1)
  #define rc ((p << 1) + 1)
  void down(int p) {
    if (a[p].t) {
      a[lc].c += a[p].t;
      a[rc].c += a[p].t;
      a[lc].t += a[p].t;
      a[rc].t += a[p].t;
      a[p].t = 0;
    }
  }
  void up(int p) {
    a[p].c = max(a[lc].c, a[rc].c);
  }
  i64 val(int p, int l, int r, int s, int t) {
    if (l == s && r == t) {
      return a[p].c;
    }
    down(p);
    i64 ret = -1e18;
    int mid = l + (r - l) / 2;
    if (s < mid) chkmax(ret, val(lc, l, mid, s, min(t, mid)));
    if (t > mid) chkmax(ret, val(rc, mid, r, max(s, mid), t));
    return ret;
  }
  void ins(int p, int l, int r, int s, int t, i64 v) {
    if (l == s && r == t) {
      a[p].c += v;
      a[p].t += v;
      return;
    }
    down(p);
    int mid = l + (r - l) / 2;
    if (s < mid) ins(lc, l, mid, s, min(t, mid), v);
    if (t > mid) ins(rc, mid, r, max(s, mid), t, v);
    up(p);
  }
  void ch(int p, int l, int r, int s, i64 v) {
    if (r - l == 1) {
      a[p].c = v;
      return;
    }
    down(p);
    int mid = l + (r - l) / 2;
    if (s < mid) ch(lc, l, mid, s, v);
    else ch(rc, mid, r, s, v);
    up(p);
  }
} T;

struct seg {
  int l, r;
  i64 a;
  inline void init() {
    l = rd() - 1, r = rd() - 1, a = rd();
    ori += a;
    a = -a;
  }
  bool operator< (const seg &rhs) const {
    return r < rhs.r || r == rhs.r && l < rhs.l;
  }
} q[N];
i64 dp[N];

int main() {
  IO::init_in();
  n = rd(), m = rd();
  FOR(i, 0, m) q[i].init();
  sort(q, q + m);
  int t = 0;
  i64 s = 0;
  for (int i = 0; i < n; ++i) {
    if (i) dp[i] = T.val(1, 0, n, 0, i);
    chkmax(dp[i], s);
    while (t < m && q[t].r == i) {
      s += q[t].a;
      if (q[t].l) T.ins(1, 0, n, 0, q[t].l, q[t].a);
      ++t;
    }
    T.ch(1, 0, n, i, dp[i]);
  }
  cout << max(s, T.val(1, 0, n, 0, n)) + ori << endl;
}

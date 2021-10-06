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
// #define MULTI
const int N = 1000005;

struct DS {
  struct node {
    int ma, sec, cnt, b;
    i64 s;
    int tam, ta, tbm, tb;
  } a[N << 2];
  #define lc a[p<<1]
  #define rc a[p<<1|1]
  #define P a[p]
  inline void up(int p) {
    P.s = lc.s + rc.s;
    P.b = max(lc.b, rc.b);
    if (lc.ma == rc.ma) {
      P.cnt = lc.cnt + rc.cnt;
      P.ma = lc.ma;
      P.sec = max(lc.sec, rc.sec);
    } else if (lc.ma > rc.ma) {
      P.cnt = lc.cnt;
      P.ma = lc.ma;
      P.sec = max(lc.sec, rc.ma);
    } else {
      P.cnt = rc.cnt;
      P.ma = rc.ma;
      P.sec = max(lc.ma, rc.sec);
    }
  }
  inline void _tag(int p, int len, int tam, int ta, int tbm, int tb) {
    chkmax(P.b, P.ma + tbm);
    chkmax(P.tbm, P.tam + tbm);
    chkmax(P.tb, P.ta + tb);
    P.s += 1ll * (len - P.cnt) * ta + 1ll * P.cnt * tam;
    P.ma += tam;
    if (P.sec != INT_MIN) P.sec += ta;
    P.tam += tam;
    P.ta += ta;
  }
  inline void down(int p, int l, int r) {
    int mid = (l + r) >> 1;
    int tmp = max(lc.ma, rc.ma);
    if (tmp == lc.ma) _tag(p<<1, mid-l, P.tam, P.ta, P.tbm, P.tb);
    else _tag(p<<1, mid-l, P.ta, P.ta, P.tb, P.tb);
    if (tmp == rc.ma) _tag(p<<1|1, r-mid, P.tam, P.ta, P.tbm, P.tb);
    else _tag(p<<1|1, r-mid, P.ta, P.ta, P.tb, P.tb);
    P.ta = P.tam = P.tb = P.tbm = 0;
  }
  void build(int p, int l, int r, int* _A) {
    // P._dirty = 0; P.ta = P.tam = P.tb = P.tbm = 0;
    // P.s = P.ma = 0;
    // P.cnt = 0;
    if (r - l == 1) {
      P.b = P.s = P.ma = _A[l];
      P.cnt = 1;
      P.sec = INT_MIN;
      return;
    }
    int mid = (l + r) >> 1;
    build(p<<1, l, mid, _A);
    build(p<<1|1, mid, r, _A);
    up(p);
  }
  void chkmin(int p, int l, int r, int s, int t, int val) {
    if (val >= P.ma) return;
    if (l == s && r == t && val >= P.sec) {
      _tag(p, r - l, val - P.ma, 0, val - P.ma, 0);
      return;
    }
    down(p, l, r);
    int mid = (l + r) >> 1;
    if (s < mid) chkmin(p<<1, l, mid, s, min(t, mid), val);
    if (t > mid) chkmin(p<<1|1, mid, r, max(s, mid), t, val);
    up(p);
  }
  void add(int p, int l, int r, int s, int t, int val) {
    if (l == s && r == t) {
      _tag(p, r - l, val, val, val, val);
      return;
    }
    down(p, l, r);
    int mid = (l + r) >> 1;
    if (s < mid) add(p<<1, l, mid, s, min(t, mid), val);
    if (t > mid) add(p<<1|1, mid, r, max(s, mid), t, val);
    up(p);
  }
  int Max(int p, int l, int r, int s, int t) {
    if (s == l && r == t) {
      return P.ma;
    }
    int ret = INT_MIN;
    int mid = (l + r) >> 1;
    down(p, l, r);
    if (s < mid) chkmax(ret, Max(p<<1, l, mid, s, min(t, mid)));
    if (t > mid) chkmax(ret, Max(p<<1|1, mid, r, max(s, mid), t));
    return ret;
  }
  int allMax(int p, int l, int r, int s, int t) {
    if (s == l && r == t) {
      return P.b;
    }
    int ret = -1e9;
    int mid = (l + r) >> 1;
    down(p, l, r);
    if (s < mid) chkmax(ret, allMax(p<<1, l, mid, s, min(t, mid)));
    if (t > mid) chkmax(ret, allMax(p<<1|1, mid, r, max(s, mid), t));
    return ret;
  }
  i64 sum(int p, int l, int r, int s, int t) {
    if (s == l && r == t) {
      return P.s;
    }
    i64 ret = 0;
    int mid = (l + r) >> 1;
    down(p, l, r);
    if (s < mid) ret += sum(p<<1, l, mid, s, min(t, mid));
    if (t > mid) ret += sum(p<<1|1, mid, r, max(s, mid), t);
    return ret;
  }
} D;

int a[N];
void solve() {
  int n, m;
  cin >> n >> m;
  FOR(i, 0, n) cin >> a[i];
  D.build(1, 0, n, a);
  while (m--) {
    int op, x, y, t;
    cin >> op >> x >> y;
    if (op == 1) cin >> t, D.add(1, 0, n, x-1, y, t);
    else if (op == 2) cin >> t, D.chkmin(1, 0, n, x-1, y, t);
    else if (op == 3) cout << D.sum(1, 0, n, x-1, y) << '\n';
    else if (op == 4) cout << D.Max(1, 0, n, x-1, y) << '\n';
    else cout << D.allMax(1, 0, n, x-1, y) << '\n';
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
#ifdef MULTI
  int T;
  cin >> T;
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
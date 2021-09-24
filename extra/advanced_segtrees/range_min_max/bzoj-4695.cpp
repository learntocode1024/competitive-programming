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
    int mx, sx, cx, mn, sn, cn;
    i64 s;
    int tmax, tmin, t;
  } a[N << 2];
  #define lc a[p<<1]
  #define rc a[p<<1|1]
  #define P a[p]
  inline void up(int p) {
    P.s = lc.s + rc.s;
    if (lc.mx == rc.mx) {
      P.cx = lc.cx + rc.cx;
      P.mx = lc.mx;
      P.sx = max(lc.sx, rc.sx);
    } else if (lc.mx > rc.mx) {
      P.cx = lc.cx;
      P.mx = lc.mx;
      P.sx = max(lc.sx, rc.mx);
    } else {
      P.cx = rc.cx;
      P.mx = rc.mx;
      P.sx = max(lc.mx, rc.sx);
    }
    if (lc.mn == rc.mn) {
      P.cn = lc.cn + rc.cn;
      P.mn = lc.mn;
      P.sn = min(lc.sn, rc.sn);
    } else if (lc.mn < rc.mn) {
      P.cn = lc.cn;
      P.mn = lc.mn;
      P.sn = min(lc.sn, rc.mn);
    } else {
      P.cn = rc.cn;
      P.mn = rc.mn;
      P.sn = min(lc.mn, rc.sn);
    }
  }
  inline void _tag(int p, int len, int tmax, int t, int tmin) {
    if (P.mn != P.mx) {
      P.s += 1ll * P.cx * tmax + 1ll * P.cn * tmin + 1ll * (len - P.cx - P.cn) * t;
      if (P.sx == P.mn) {
        P.sx += tmin;
        P.sn += tmax;
      } else {
        P.sx += t;
        P.sn += t;
      }
      P.mx += tmax;
      P.mn += tmin;
    } else {
      if (t == tmin) { // with chkmin
        tmin = tmax;
      } else {
        tmax = tmin;
      } // with chkmax
      P.s += 1ll * tmax * len;
      P.mn += tmax;
      P.mx += tmax;
    }
    P.tmax += tmax;
    P.t += t;
    P.tmin += tmin;
  }
  inline void down(int p, int l, int r) {
    int mid = (l + r) >> 1;
    int tmx = max(lc.mx, rc.mx), tmn = min(lc.mn, rc.mn);
    _tag(p<<1, mid-l, lc.mx == tmx ? P.tmax : P.t, P.t, lc.mn == tmn ? P.tmin : P.t);
    _tag(p<<1|1, r-mid, rc.mx == tmx ? P.tmax : P.t, P.t, rc.mn == tmn ? P.tmin : P.t);
    P.t = P.tmax = P.tmin = 0;
  }
  void build(int p, int l, int r, int* _A) {
    // P._dirty = 0; P.ta = P.tam = P.tb = P.tbm = 0;
    // P.s = P.mx = 0;
    // P.cnt = 0;
    if (r - l == 1) {
      P.s = P.mx = P.mn = _A[l];
      P.cx = P.cn = 1;
      P.sx = INT_MIN;
      P.sn = INT_MAX;
      return;
    }
    int mid = (l + r) >> 1;
    build(p<<1, l, mid, _A);
    build(p<<1|1, mid, r, _A);
    up(p);
  }
  void chkmin(int p, int l, int r, int s, int t, int val) {
    if (val >= P.mx) return;
    if (l == s && r == t && val >= P.sx) {
      _tag(p, r - l, val - P.mx, 0, 0);
      return;
    }
    down(p, l, r);
    int mid = (l + r) >> 1;
    if (s < mid) chkmin(p<<1, l, mid, s, min(t, mid), val);
    if (t > mid) chkmin(p<<1|1, mid, r, max(s, mid), t, val);
    up(p);
  }
  void chkmax(int p, int l, int r, int s, int t, int val) {
    if (val <= P.mn) return;
    if (l == s && r == t && val <= P.sn) {
      _tag(p, r - l, 0, 0, val - P.mn);
      return;
    }
    down(p, l, r);
    int mid = (l + r) >> 1;
    if (s < mid) chkmax(p<<1, l, mid, s, min(t, mid), val);
    if (t > mid) chkmax(p<<1|1, mid, r, max(s, mid), t, val);
    up(p);
  }
  void add(int p, int l, int r, int s, int t, int val) {
    if (l == s && r == t) {
      _tag(p, r - l, val, val, val);
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
      return P.mx;
    }
    int ret = INT_MIN;
    int mid = (l + r) >> 1;
    down(p, l, r);
    if (s < mid) ::chkmax(ret, Max(p<<1, l, mid, s, min(t, mid)));
    if (t > mid) ::chkmax(ret, Max(p<<1|1, mid, r, max(s, mid), t));
    return ret;
  }
  int Min(int p, int l, int r, int s, int t) {
    if (s == l && r == t) {
      return P.mn;
    }
    int ret = INT_MAX;
    int mid = (l + r) >> 1;
    down(p, l, r);
    if (s < mid) ::chkmin(ret, Min(p<<1, l, mid, s, min(t, mid)));
    if (t > mid) ::chkmin(ret, Min(p<<1|1, mid, r, max(s, mid), t));
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
  void walk(int p, int l, int r) {
    if (r - l == 1) {
      cerr << P.mx << ' ';
      return;
    }
    int mid = (l + r) >> 1;
    down(p, l, r);
    walk(p<<1, l, mid);
    walk(p<<1|1, mid, r);
    return;
  }
} D;

int a[N];
void solve() {
  int n, m;
  cin >> n;
  FOR(i, 0, n) cin >> a[i];
  D.build(1, 0, n, a);
  cin >> m;
  while (m--) {
    int op, x, y, t;
    cin >> op >> x >> y;
    switch (op) {
      case 1:
        cin >> t, D.add(1, 0, n, x-1, y, t);
        break;
      case 2:
        cin >> t, D.chkmax(1, 0, n, x-1, y, t);
        break;
      case 3:
        cin >> t, D.chkmin(1, 0, n, x-1, y, t);
        break;
      case 4:
        cout << D.sum(1, 0, n, x-1, y) << '\n';
        break;
      case 5:
        cout << D.Max(1, 0, n, x-1, y) << '\n';
        break;
      default:
        cout << D.Min(1, 0, n, x-1, y) << '\n';
    }
    // D.walk(1, 0, n);
    // cerr << endl;
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
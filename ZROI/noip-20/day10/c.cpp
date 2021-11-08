#include <bits/stdc++.h>
using namespace std;
template<typename T>
void rd(T &a) {
  cin >> a;
}
template<typename A, typename... B>
void rd(A &a, B& ...b) {
  cin >> a;
  rd(b...);
}
template<typename A>
void print(const A& a) {
  cout << a;
}
template<typename A, typename... B>
void print(const A& a, const B& ...b) {
  cout << a;
  print(b...);
}
template<typename A>
void println(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void println(const A& a, const B& ...b) {
  cout << a << ' ';
  println(b...);
}
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef pair<int, int> pii;
#define mkp make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i < (k); ++i)
#define ROF(i, j, k) for (int i = ((k) - 1); i >= j; --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

const int N = 2e5+5;
int n;
i64 g, r;
int L[N];
i64 f[N];
i64 h[N], hh[N];

struct DS {
  struct node {
    int l, r;
    int c;
  } a[N << 6];
#define lc a[p].l
#define rc a[p].r
#define P a[p]
  int rt, tot = 0;
  void seg(int &p, int l, int r, int s, int t, int v) {
    if (!p) {
      p = ++tot;
      P.c = -1;
    }
    if (l == s && r == t) {
      P.c = v;
      return;
    }
    if (P.c != -1) {
      if (!lc) lc = ++tot;
      a[lc].c = P.c;
      if (!rc) rc = ++tot;
      a[rc].c = P.c;
      P.c = -1;
    }
    int mid = l + (r - l) / 2;
    if (t <= mid) seg(lc, l, mid, s, t, v);
    else if (s >= mid) seg(rc, mid, r, s, t, v);
    else seg(lc, l, mid, s, mid, v), seg(rc, mid, r, mid, t, v);
  }
  int get(int p, int l, int r, int s) {
    if (!p) return 0;
    if (P.c != -1) {assert(P.c > 0);return P.c;}
    int mid = l + (r - l) / 2;
    if (s < mid) return get(lc, l, mid, s);
    else return get(rc, mid, r, s);
  }
} T;

inline i64 query(i64 t) {
  int _r = T.get(1, 0, g + r, t % (g + r));
  if (_r == 0) return t + hh[n];
  else {
    t += hh[_r - 1];
    t += g + r - t % (g + r);
    t += f[_r];
  }
  return t;
}
int rt;

inline void solve() {
  cin >> n >> g >> r;
  FOR(i, 0, n + 1) cin >> L[i];
  FOR(i, 1, n + 1) h[i] = (h[i - 1] + L[i - 1]) % (g + r);
  hh[0] = L[0];
  FOR(i, 1, n + 1) hh[i] = hh[i - 1] + L[i];
  f[n] = L[n];
  ROF(i, 1, n + 1) {
    if (g - h[i] >= 0) T.seg(rt, 0, r + g, g - h[i], g - h[i] + r, i);
    else T.seg(rt, 0, r + g, g + g + r - h[i], g + r, i), T.seg(rt, 0, r + g, 0, g - h[i] + r, i);
    int R = T.get(1, 0, g + r, (g + r - h[i]) % (g + r));
    if (R == 0) f[i] = hh[n] - hh[i - 1];
    else {
      i64 t = hh[r - 1] - hh[i - 1];
      t += g + r - t % (g + r);
      f[i] = f[R] + t;
    }
    assert(f[i] > 0);
  }
  int q;
  cin >> q;
  i64 lst = 0;
  while (q--) {
    i64 cur;
    cin >> cur;
    cur ^= lst;
    cout << (lst = query(cur)) << '\n';
    lst %= 2147483647ll;
  }
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
  solve();
  return 0;
}
/* Checklist:
 * - data type
 * - overflow
 * - typo/logic
 * - special cases
 * - cleanup (multi-test)
 * - bounds
 * - memory usage
 * - file IO
 */


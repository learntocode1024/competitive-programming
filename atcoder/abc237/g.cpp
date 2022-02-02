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

//#define MULTI
const int N = 2e5+5;
int n, q, x;
int a[N];
int b[N], c[N];

struct sgT {
  struct node {
    int s, t;
    bool f;
  } a[N<<2];
  inline void down(int p, int l, int r) {
    int lc = p<<1, rc = p<<1|1;
    if (a[p].f) {
      a[lc].s = a[lc].t = a[rc].s = a[rc].t = 0;
      a[lc].f = a[rc].f = 1;
      a[p].f = 0;
    }
    int &g = a[p].t;
    int mid = (l + r) >> 1;
    a[lc].s += (mid - l) * g;
    a[lc].t += g;
    a[rc].s += (r - mid) * g;
    a[rc].t += g;
    g = 0;
  }
  void up(int p) {
    a[p].s = a[p<<1].s + a[p<<1|1].s;
  }
  void clr(int p, int l, int r, int s, int t) {
    if (l == s && r == t) {
      a[p].s = a[p].t = 0;
      a[p].f = 1;
      return;
    }
    down(p, l, r);
    int mid = (l + r) >> 1;
    if (s < mid) clr(p<<1, l, mid, s, min(mid, t));
    if (t > mid) clr(p<<1|1, mid, r, max(s, mid), t);
    up(p);
  }
  void add(int p, int l, int r, int s, int t) {
    if (l == s && r == t) {
      a[p].s += r - l;
      ++a[p].t;
      return;
    }
    down(p, l, r);
    int mid = (l + r) >> 1;
    if (s < mid) add(p<<1, l, mid, s, min(mid, t));
    if (t > mid) add(p<<1|1, mid, r, max(s, mid), t);
    up(p);
  }
  int sum(int p, int l, int r, int s, int t) {
    if (l == s && r == t) {
      return a[p].s;
    }
    down(p, l, r);
    int mid = (l + r) >> 1, ans = 0;
    if (s < mid) ans += sum(p<<1, l, mid, s, min(mid, t));
    if (t > mid) ans += sum(p<<1|1, mid, r, max(s, mid), t);
    return ans;
  }
  void out(int p, int l, int r, int *o) {
    if (r - l == 1) {
      o[l] = a[p].s;
      return;
    }
    down(p, l, r);
    int mid = (l + r) >> 1;
    out(p<<1, l, mid, o);
    out(p<<1|1, mid, r, o);
  }
} T1, T2;

inline void solve() {
  rd(n, q, x);
  FOR(i, 0, n) cin >> a[i];
  FOR(i, 0, n) if (a[i] >= x) T1.add(1, 0, n, i, i+1);
  FOR(i, 0, n) if (a[i] > x) T2.add(1, 0, n, i, i+1);
  FOR(i, 0, q) {
    int c, l, r;
    cin >> c >> l >> r;
    --l;
    int s = T1.sum(1, 0, n, l, r);
    if (s && s != r - l) {
      T1.clr(1, 0, n, l, r);
      if (c == 1) T1.add(1, 0, n, r-s, r);
      else T1.add(1, 0, n, l, l + s);
    }
    s = T2.sum(1, 0, n, l, r);
    if (s && s != r - l) {
      T2.clr(1, 0, n, l, r);
      if (c == 1) T2.add(1, 0, n, r-s, r);
      else T2.add(1, 0, n, l, l + s);
    }
  }
  T1.out(1, 0, n, b+1);
  T2.out(1, 0, n, c+1);
  FOR(i, 1, n + 1) {
    if (b[i] != c[i]) {
      println(i);
      return;
    }
  }
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
#ifdef MULTI
  int T;
  cin >> T;
  while (T--)
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


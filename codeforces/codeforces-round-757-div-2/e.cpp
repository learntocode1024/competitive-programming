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
int M = 1e9+1;

struct DS {
  struct node {
    int l, r, tg;
    int lcc, rcc;
  } a[N<<5];
#define lc a[p].lcc
#define rc a[p].rcc
#define leaf (!a[p].lcc && !a[p].rcc)
  int tot;
  int rt;
  DS() {
    tot = 1;
    rt = 1;
    a[1].l = 0, a[1].r = M - 1;
  }
  inline void init(int &p, int l, int r) {
    p = ++tot;
    a[p].l = l;
    a[p].r = r;
    if (a[p].r < 0) a[p].l = a[p].r = 0;
    else if (a[p].l < 0) a[p].l = 0;
    if (a[p].l >= M) a[p].l = a[p].r = M-1;
    else if (a[p].r >= M) a[p].r = M - 1;
  }
  inline void _down(int p, int v) {
    a[p].l += v;
    a[p].r += v;
    a[p].tg += v;
    if (a[p].r < 0) a[p].l = a[p].r = 0;
    else if (a[p].l < 0) a[p].l = 0;
    if (a[p].l >= M) a[p].l = a[p].r = M-1;
    else if (a[p].r >= M) a[p].r = M - 1;
  }
  inline void down(int p, int l, int r) {
    int v = a[p].tg;
    if (!v || r == l) return;
    int mid = l + (r - l) / 2;
    if (!lc) init(lc, l + v, mid + v);
    else _down(lc, v);
    if (!rc) init(rc, mid + 1 + v, r + v);
    else _down(rc, v);
    a[p].tg = 0;
  }
  inline void up(int p) {
    a[p].l = a[lc].l;
    a[p].r = a[rc].r;
  }
  int get(int p, int l, int r, int x) {
    if (leaf || r == l) {
      return a[p].l + x - l;
    }
    int mid = l + (r - l) / 2;
    down(p, l, r);
    if (x <= mid) return get(lc, l, mid, x);
    return get(rc, mid + 1, r, x);
  }
  void ch(int &p, int l, int r, int x) {
    if (!p) init(p, l, r);
    if (a[p].l == x && a[p].r == x) return;
    if (a[p].r < x) return _down(p, 1);
    if (a[p].l > x) return _down(p, -1);
    down(p, l, r);
    int mid = l + (r - l) / 2;
    ch(lc, l, mid, x);
    ch(rc, mid + 1, r, x);
    up(p);
  }
  inline void center(int x) {
    ch(rt, 0, M - 1, x);
  }
  int operator[] (int x) {
    return get(rt, 0, M - 1, x);
  }
} D;
int lst = 0;

inline void solve() {
  int n;
  cin >> n;
  FOR(i, 0, n) {
    int x;
    cin >> x;
    D.center(x);
    int k;
    cin >> k;
    while (k--) {
      int c;
      cin >> c;
      c = (lst + c) % M;
      println(lst = D[c]);
    }
  }
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  // ios::sync_with_stdio(0);
  // cin.tie(0);
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


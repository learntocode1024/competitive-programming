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
const int P = 998244353;

struct segT {
  struct node {
    int l, r;
    i64 s, m, c;
  } a[N<<5];
  #define lc a[p].l
  #define rc a[p].r
  int tot;
  inline void init(int &p) {
    p = ++tot;
    a[p].m = 1;
  }
  inline void up(int p) {
    a[p].s = (a[lc].s + a[rc].s) % P;
  }
  inline void _dwn(int p, i64 l, i64 m, i64 c) {
    a[p].s = (a[p].s * (P + m) + c * l) % P;
    a[p].m = a[p].m * (P + m) % P;
    a[p].c = (c + a[p].c * (P + m)) % P;
  }
  inline void dwn(int p, int l, int r) {
    int mid = (r + l) >> 1;
    if (!lc) init(lc);
    if (!rc) init(rc);
    _dwn(lc, mid - l, a[p].m, a[p].c);
    _dwn(rc, r - mid, a[p].m, a[p].c);
    a[p].m = 1;
    a[p].c = 0;
  }
  void mul(int &p, int l, int r, int s, int t, i64 v) {
    if (!p) init(p);
    if (l == s && r == t) {
      return _dwn(p, r - l, v, 0);
    }
    dwn(p, l, r);
    int mid = (l + r) >> 1;
    if (s < mid) mul(lc, l, mid, s, min(mid, t), v);
    if (t > mid) mul(rc, mid, r, max(s, mid), t, v);
    up(p);
  }
  void ch(int &p, int l, int r, int s, int t, i64 v) {
    if (!p) init(p);
    if (l == s && r == t) {
      return _dwn(p, r - l, 1, v);
    }
    dwn(p, l, r);
    int mid = (l + r) >> 1;
    if (s < mid) ch(lc, l, mid, s, min(mid, t), v);
    if (t > mid) ch(rc, mid, r, max(s, mid), t, v);
    up(p);
  }
  int sum(int &p, int l, int r, int s, int t) {
    if (!p) init(p);
    if (l == s && r == t) {
      return a[p].s;
    }
    dwn(p, l, r);
    int mid = (l + r) >> 1;
    i64 ret = 0;
    if (s < mid) ret += sum(lc, l, mid, s, min(mid, t));
    if (t > mid) ret += sum(rc, mid, r, max(s, mid), t);
    return ret % P;
  }
} T;

int n, rt, a;
int L = 1, R = 1e9+1;

inline void solve() {
  cin >> n >> a;
  T.ch(rt, L, R, 1, a + 1, 1);
  FOR(I, 1, n) {
    cin >> a;
    int s = T.a[rt].s;
    if (a + 1 < R) T.mul(rt, L, R, a + 1, R, 0);
    T.mul(rt, L, R, 1, a + 1, -1);
    T.ch(rt, L, R, 1, a + 1, s);
  }
  println(T.a[rt].s);
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


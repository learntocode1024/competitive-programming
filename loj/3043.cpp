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
const int N = 1e5+5;
const int P = 998244353;
const int i2 = 499122177;
inline void red(int &x) {
  if (x >= P) x -= P;
}
int pw = 1;

inline int por(int a, int b) {
  return (1 + P - 1ll * (1 + P - a) * (1 + P - b) % P) % P;
}

struct segT {
  struct node {
    int a, b, s, tg;
  } a[N<<2];
  inline void down(int p) {
    if (a[p].tg) {
      int tg = a[p].tg;
      a[p<<1].b = por(a[p<<1].b, tg);
      a[p<<1|1].b = por(a[p<<1|1].b, tg);
      a[p<<1].tg = por(a[p<<1].tg, tg);
      a[p<<1|1].tg = por(a[p<<1|1].tg, tg);
      a[p].tg = 0;
    }
  }
  inline void tag(int p) {
    red(a[p].s += P - a[p].a);
    a[p].a = 1ll * (a[p].a + a[p].b) * i2 % P;
    red(a[p].s += a[p].a);
  }
  void oper(int p, int l, int r, int s, int t) {
    if (l == s && r == t) {
      red(a[p].s += P - a[p].a);
      a[p].a = por(i2, a[p].a);
      a[p].b = por(i2, a[p].b);
      a[p].tg = por(a[p].tg, i2);
      red(a[p].s += a[p].a);
      return;
    }
    int m = (l + r) >> 1;
    down(p);
    red(a[p].s += P - a[p].a);
    a[p].a = 1ll * a[p].a * i2 % P;
    a[p].b = 1ll * a[p].b * i2 % P;
    red(a[p].s += a[p].a);
    if (t <= m) {
      oper(p<<1, l, m, s, t);
      tag(p<<1|1);
    } else if (s > m) {
      oper(p<<1|1, m+1, r, s, t);
      tag(p<<1);
    } else {
      oper(p<<1, l, m, s, m);
      oper(p<<1|1, m+1, r, m+1, t);
    }
    a[p].s = (1ll * a[p<<1].s + a[p<<1|1].s + a[p].a) % P;
  }
} T;
int n, m;

inline void solve() {
  rd(n, m);
  FOR(i, 0, m) {
    int op;
    rd(op);
    if (op == 1) {
      int l, r;
      pw = pw * 2 % P;
      rd(l, r);
      T.oper(1, 1, n, l, r);
    } else {
      println(1ll * pw * T.a[1].s % P);
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


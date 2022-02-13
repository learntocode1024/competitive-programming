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
pii farey_pre(int N, pii a, pii b) { // Concrete Mathematics (Exercise 4.61)
  int m = b.se - b.fi, m1 = a.se - a.fi;
  int n = b.se, n1 = a.se;
  int r = (n + N) / n1;
  int n2 = r * n1 - n;
  int m2 = r * m1 - m;
  return {n2-m2, n2};
}

void print(pii a) {
  cout << a.fi << '/' << a.se;
}
int n, m, k;

bool frac_lt(pii a, pii b, pii c) {
  i64 s = c.fi;
  s *= a.se;
  s *= b.se;
  i64 x = c.se, y = c.se;
  x *= a.fi;
  x *= b.se;
  y *= a.se;
  y *= b.fi;
  x = abs(x-s);
  y = abs(y-s);
  return x<y;
}

inline void solve() {
  rd(n, m, k);
  pii a0 = {1,1}, a1 = {n-1, n};
  FOR(i, 1, k) {
    pii tmp = a1;
    a1 = farey_pre(n, a1, a0);
    a0 = tmp;
  }
  pii x = a1;
  if (m >= n) {
  print(x);
  cout << ' ';
  print(x);
  cout << '\n';
  return;
  }
  a1 = {m-1, m}, a0 = {1,1};
  pii y = {m-1, 1};
  FOR(i, 0, k) {
    if (frac_lt(a1, y, x)) y = a1;
    if (a1.fi == 0) break;
    pii tmp = a1;
    a1 = farey_pre(m, a1, a0);
    a0 = tmp;
  }
  print(x);
  cout << ' ';
  print(y);
  cout << '\n';
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


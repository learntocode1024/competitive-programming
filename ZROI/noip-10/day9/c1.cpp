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

const int N = 5e5+5;
int n, a, b, c, d, e;
int x[N], x2[N];

namespace sub2 {
inline void work() {
  FOR(i, 0, n) {
    if (x[i] & 1) --a, --x[i];
    x[i] >>= 1;
  }
  if (a < 0) {
    println("NO");
    return;
  }
  b += a >> 1;
  FOR(i, 0, n) {
    if (x[i] & 1) --b, --x[i];
    x[i] >>= 1;
  }
  if (b < 0) {
    println("NO");
    return;
  }
  c += b >> 1;
  FOR(i, 0, n) {
    c -= x[i];
  }
  if (c < 0) {
    println("NO");
    return;
  }
  println("YES");
}
}

namespace sol {
inline void work() {
  FOR(i, 0, n) {
    if (x[i] & 1) --a, --x[i];
    x[i] >>= 1;
  }
  if (a < 0) {
    println("NO");
    return;
  }
  b += a >> 1;
  FOR(i, 0, n) {
    x2[i] = x[i] % 5;
    x[i] /= 5;
  }
  FOR(i, 0, n) {
    if (x2[i] & 1) --b, --x2[i];
    x2[i] >>= 1;
  }
  if (b < 0) {
    println("NO");
    return;
  }
  c += b / 2;
  FOR(i, 0, n) {
    c -= x2[i];
  }
  if (c < 0) {
    println("NO");
    return;
  }
  // convert b, c to d
  int k = min(b / 2, c);
  b = b & 1 + 2 * k;
  c = c - k;
  int d1 = min(c / 2, b);
  d += d1;
  c -= 2 * d1;
  b -= d1;
  int d2 = min(b / 3, c);
  d += d2;
  b -= 3 * d2;
  c -= d2;
  d += b / 5;
  FOR(i, 0, n) {
    if (x[i] & 1) --d, --x[i];
    x[i] >>= 1;
  }
  if (d < 0) {
    println("NO");
    return;
  }
  e += d / 2;
  FOR(i, 0, n) {
    e -= x[i];
  }
  if (e < 0) {
    println("NO");
    return;
  }
  println("YES");
}
}

inline void solve() {
  rd(n, a, b, c, d, e);
  FOR(i, 0, n) cin >> x[i];
  if (d == 0 && e == 0) sub2::work();
  else sol::work();
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
  int T;
  cin >> T;
while (T--)
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

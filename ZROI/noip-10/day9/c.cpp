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
bool solve15(int s1, int s5) {
  FOR(i, 0, n) {
    int t = min(s5, x2[i] / 5);
    s5 -= t;
    x2[i] -= t * 5;
  }
  FOR(i, 0, n) s1 -= x2[i];
  return s1 >= 0;
}
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
  int tot = 0, tot5 = 0;
  FOR(i, 0, n) tot += x[i] & 1;
  FOR(i, 0, n) if ((x[i] & 1) && x[i] >= 5) ++tot5;
  sort(x, x + n);
  reverse(x, x + n);
  if (b + d < tot) {
    println("NO");
    return;
  }
  FOR(d5, 0, min(d, tot5) + 1) {
    if (b - tot + d5 < 0) continue;
    FOR(i, 0, n) x2[i] = x[i];
    int t = d5;
    FOR(i, 0, n) {
      if (t && (x2[i] & 1)) x2[i] -= 5, --t;
      else if (x2[i] & 1) --x2[i];
      x2[i] >>= 1;
    }
    if (solve15(c + (b - tot + d5) / 2, e + (d - d5) / 2)) {
      println("YES");
      return;
    }
  }
  println("NO");
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

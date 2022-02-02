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

#define MULTI
const int N = 2e5+5;
int n, k;
int c[N], a[N];

inline void solve() {
  rd(n, k);
  FOR(i, 1, n + 1) c[i] = 0;
  FOR(i, 1, n + 1) cin >> a[i], ++c[a[i]];
  int l, r;
  int mn = 1e7, s = 0;
  int x, y;
  for (r = 1, l = 1; r <= n; ++r) {
    s += c[r];
    while (l < r && (s - c[l]) * 2 >= n + k) s -= c[l], ++l;
    if (s * 2 >= n + k && r - l < mn) {
      mn = r - l;
      x = l, y = r;
    }
  }
  println(x, y);
  FOR(i, 1, n + 1) {
    if (a[i] >= x && a[i] <= y) a[i] = 1;
    else a[i] = -1;
  }
  if (k == 1) {
    println(1, n);
    return;
  }
  for (s = 0, l = 1, r = 1; r <= n; ++r) {
    s += a[r];
    if (s == 1) {
      --k;
      println(l, r);
      l = r + 1;
      s = 0;
      if (k == 1) {
        println(l, n);
        return;
      }
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


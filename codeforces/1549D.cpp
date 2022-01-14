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
i64 a[N];
int n;
i64 f[N];

inline void solve() {
  cin >> n;
  int ans = 1;
  FOR(i, 0, n) cin >> a[i], f[i] = 0;
  ROF(i, 1, n) a[i] -= a[i-1], a[i] = abs(a[i]);
  for (int l, r, m = 1; m < n;) {
    f[m] = a[m];
    l = m;
    while (l>1 && !f[l-1]) --l, f[l] = __gcd(f[l+1], a[l]);
    i64 ar = a[m];
    for (r = m; r < n && l <= m; ++r) {
      while (__gcd(f[l], ar) == 1 && l <= m) ++l;
      if (l <= m) chkmax(ans, r - l + 2);// println(l, r);
      ar = __gcd(ar, a[r+1]);
    }
    m = r;
  }
  println(ans);
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


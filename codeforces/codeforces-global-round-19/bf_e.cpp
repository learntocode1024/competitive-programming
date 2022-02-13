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
const int N = 1000;
int a[N];
int x[N], y[N];
int n, m;

inline void solve() {
  rd(n, m);
  FOR(i, 0, n) cin >> a[i];
  FOR(i, 0, m) rd(x[i], y[i]);
  i64 ans = 0;
  FOR(i, 0, n) FOR(j, i + 1, n) {
    bool ok = a[i] != a[j];
    FOR(k, 0, m) {
      if (a[i] == x[k] && a[j] == y[k]) ok = 0;
      if (a[i] == y[k] && a[j] == x[k]) ok = 0;
    }
    if (!ok) continue;
    i64 cc = 0, xx = a[i] + a[j];
    FOR(k, 0, n) {
      if (a[k] == a[i] || a[k] == a[j]) ++cc;
    }
    chkmax(ans, cc * xx);
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


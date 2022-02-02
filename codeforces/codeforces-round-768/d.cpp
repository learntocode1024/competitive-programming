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
const int N = 1e6+5;
int b;
int n, m;
int a[N];
i64 ans = 0;
int mn[N];
bool v[N];

inline void solve() {
  rd(n, m);
  b = ans = 0;
  FOR(i, 0, n) cin >> a[i], ans += abs(a[i]);
  for (int i = 0, ib; i < m; ++i) {
    cin >> ib;
    b = __gcd(b, ib);
  }
  if (b == 1) {
    println(ans);
    return;
  }
  FOR(i, 0, b) mn[i] = 1e9+7, v[i] = 0;
  FOR(i, 0, n) chkmin(mn[i%b], abs(a[i]));
  FOR(i, 0, n) if (a[i]<0) v[i%b] ^= 1;
  FOR(i, 0, b-1) v[i] ^= v[b-1];
  i64 c1 = 0, c2 = mn[b-1];
  FOR(i, 0, b-1) if (v[i]) c1 += mn[i];
  FOR(i, 0, b-1) if (!v[i]) c2 += mn[i];
  println(ans - 2*min(c1,c2));
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


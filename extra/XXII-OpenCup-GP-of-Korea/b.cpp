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

const int N = 5e6+5;
char s[N], t[N];
int c;
int n;

inline void solve() {
  cin >> n >> s >> t;
  FOR(i, 0, n) c += s[i] == 'Y';
  int c1 = c, c2 = c;
  FOR(i, 0, n) c -= t[i] == 'Y';
  if (c != 0) {
    println(0);
    return;
  }
  int l = n - 1;
  int x = 0;
  while (s[x] != t[l] || c1 != c2) {
    c1 -= s[l] == 'Y';
    c2 -= s[l] == 'Y';
    --l;
  }
  if (l > 0) for (; x < n; ++x) {
    while (s[x] != t[l]) --l;
    if (l == 0) break;
    --l;
  }
  i64 ans = 0;
  FOR(i, 0, x + 1) {
    if (s[i] == t[0]) ans += i + 1;
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


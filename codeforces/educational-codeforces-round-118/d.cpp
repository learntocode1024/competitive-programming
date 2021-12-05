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
const int p = 998244353;
inline void red(int &x) { if (x >= p) x -= p; }
int f[N], g[N];
int n;

inline void solve() {
  cin >> n;
  FOR(i, 0, n + 5) f[i] = g[i] = 0;
  FOR(i, 0, n) {
    int a;
    cin >> a;
    if (a >= 1) red(g[a-1] += g[a-1]), red(g[a-1] += f[a-1]);
    red(g[a+1] += g[a+1]);
    red(f[a+1] += f[a+1]);
    red(f[a+1] += f[a]);
    if (a == 1) red(++g[0]);
    if (a == 0) red(++f[1]);
  }
  int ans = 0;
  FOR(i, 0, n + 5) red(ans += f[i]);
  FOR(i, 0, n + 5) red(ans += g[i]);
  println(ans);
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


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
const int N = 3e5+5;
char s[N], t[N];
int n, m;
int l[N], r[N];

inline void solve() {
  rd(n, m, s, t);
  int c = 0, cc = 1e9;
  FOR(i, 0, m + n) if (s[i] == '1') ++l[i];
  FOR(i, 1, m + n) l[i] += l[i-1];
  FOR(i, 0, m + n) if (t[i] == '1') ++r[i];
  FOR(i, 1, m + n) r[i] += r[i-1];
  if (min(l[0], r[0])==0){ for (int i = 1, s = 0, v = 0; i < m + n; ++i) {
    if (min(l[i], r[i]) <= s + v && max(l[i], r[i]) >= s + v) s += v;
    else v ^= 1, s += v, ++c;
  }
  cc = c;
  c = 0;}
  if (max(l[0], r[0])>=1){ for (int i = 1, s = 1, v = 1; i < m + n; ++i) {
    if (min(l[i], r[i]) <= s + v && max(l[i], r[i]) >= s + v) s += v;
    else v ^= 1, s += v, ++c;
  }
  chkmin(cc,c);}
  println(m + n - 1 - cc);
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


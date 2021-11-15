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

const int N = 1<<14|5;
#define popcnt __builtin_popcount
char s[N];
int t[N];
int n;
int c[N];
int ans[N];


inline void solve() {
  cin >> n >> s;
  FOR(i, 0, 1<<n) s[i] -= '0';
  iota(t, t + (1 << n), 0);
  sort(t, t + (1 << n), [] (const int &a, const int &b) {return popcnt(a) > popcnt(b); } );
  FOR(I, 0, 1<<n) {
    int u = t[I];
    FOR(i, 0, 1<<n) c[u&i] |= 1<<s[i];
    FOR(i, 0, 1<<n) if (c[u&i] != 3) ans[i] = u;
    for (int v = u; v; v = (v - 1) & u) c[v] = 0;
    c[0] = 0;
  }
  FOR(i, 0, 1<<n) cout << popcnt(ans[i]) << " ";
  cout << '\n';
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


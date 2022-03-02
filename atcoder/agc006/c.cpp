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
const int N = 1e5+5;
int n, m;
i64 k;
int a[N];
i64 b[N];
int p[N], o[N];
int tmp[N];
inline void com(int *a, int *b, int *out) {
  FOR(i, 1, n) tmp[i] = b[a[i]];
  FOR(i, 1, n) out[i] = tmp[i];
}

inline void solve() {
  cin >> n;
  FOR(i, 0, n) cin >> a[i];
  ROF(i, 1, n) a[i] -= a[i-1];
  iota(p, p + n, 0);
  iota(o, o + n, 0);
  rd(m, k);
  FOR(i, 0, m) {
    int x;
    cin >> x;
    swap(p[x], p[x-1]);
  }
  while (k) {
    if (k & 1) com(o, p, o);
    k >>= 1;
    com(p, p, p);
  }
  com(o, a, a);
  b[0] = a[0];
  FOR(i, 1, n) b[i] = b[i-1] + a[i];
  FOR(i, 0, n) cout << b[i] << '\n';
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


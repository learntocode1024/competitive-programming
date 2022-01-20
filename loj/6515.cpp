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
const int N = 5e4+5, P = 505;
int m, p;
i64 f[2][N][P];
int w[2][N], v[2][N], t[2], s[2];

inline void nxt(i64 *f, i64 *g, int w, int v) {
  FOR(i, 0, p) g[i] = max(f[i], f[(i + p - w) % p] + v);
}

inline void ins(int c) {
  int &l = t[c];
  ++l;
  rd(w[c][l], v[c][l]);
  w[c][l] %= p;
  nxt(f[c][l-1], f[c][l], w[c][l], v[c][l]);
}

inline void del(int c) {
  if (t[c] == s[c]) {
    int r = t[c^1] >> 1;
    
  } else --t[c];
}

i64 h[P<<1];
d
inline i64 query() {
  int l, r;
  rd(l, r);
  i64 ans = 0, cur = 0;
  FOR(i, 0, p) h[i] = h[i+p] = f[1][t[1]][i];
  
  return ans;
}

inline void solve() {
  
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


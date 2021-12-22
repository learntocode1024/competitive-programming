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
const int N = 1e3+5, M = 2e5+5;
int d[N][N];
int n, m;
int h[M];

inline void solve() {
  rd(n, m);
  FOR(i, 1, n + 1) d[i][i] = m + 1;
  FOR(i, 1, m + 1) {
    int u, v;
    rd(u, v);
    d[u][v] = i;
  }
  ROF(i, 1, n + 1) {
    FOR(k, 1, n + 1) if (d[k][i]) {
      int cur = d[k][i];
      if (k > i) FOR(j, 1, i) chkmax(d[k][j], min(d[i][j], cur));
      else FOR(j, 1, n + 1) chkmax(d[k][j], min(d[i][j], cur));
    }
    FOR(j, i, n + 1) {
      int t = min(d[i][j], d[j][i]);
      ++h[0];
      --h[t];
    }
  }
  FOR(i, 1, m + 1) h[i] += h[i - 1];
  FOR(i, 0, m + 1) cout << h[i] << " \n"[i==m];
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


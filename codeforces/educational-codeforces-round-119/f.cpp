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
const int inf = 1e7;
int n;
int p[N], q[N];
int f[N][2][2];
int pre[N][2][2];

inline void solve() {
  rd(n);
  FOR(i, 1, n + 1) rd(p[i]);
  FOR(i, 1, n + 1) FOR(j, 0, 2) FOR(k, 0, 2) f[i][j][k] = inf;
  f[1][0][0] = -inf;
  f[1][1][0] = -inf;
  FOR(i, 2, n + 1) {
    for (int j = 0; j < 2; ++j, p[i] = -p[i]) {
      int x, y;
      for (int k = 0; k < 2; ++k, p[i - 1] = -p[i - 1]) {
        for (int l = 0; l < 2; ++l) {
          if (f[i-1][k][l] == inf) continue;
          x = p[i-1];
          y = f[i-1][k][l];
          if (l) swap(x, y);
          if (p[i] > x) {
            if (y < f[i][j][0]) {
              f[i][j][0] = y;
              pre[i][j][0] = k << 1 | l;
            }
          }
          else if (p[i] > y) {
            if (x < f[i][j][1]) {
              f[i][j][1] = x;
              pre[i][j][1] = k<<1|l;
            }
          }
        }
      }
    }
  }
  FOR(i, 0, 2) FOR(j, 0, 2) if (f[n][i][j] < inf) {
    println("YES");
    q[n] = p[n];
    if (i) q[n] = -q[n];
    ROF(t, 1, n) {
      int pp = pre[t + 1][i][j];
      i = pp >> 1;
      j = pp & 1;
      q[t] = p[t];
      if (i) q[t] = -q[t];
    }
    FOR(s, 1, n + 1) cout << q[s] << " \n"[s==n];
    return;
  }
  println("NO");
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


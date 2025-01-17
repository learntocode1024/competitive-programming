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
const int N = 1e5+5, M = 23;
int n, m, k;
int s[N], f[1<<M];
int c[M][M];
int g[M], h[M];
int g1[M][1<<12], g2[M][1<<12];
int h1[M][1<<12], h2[M][1<<12];
int H, T;

inline void solve() {
  rd(n, m, k);
  H = m / 2;
  T = (1 << H) - 1;
  FOR(i, 0, n) cin >> s[i];
  FOR(i, 1, n) ++c[s[i-1]-1][s[i]-1];
  FOR(i, 0, m) c[i][i] = 0;
  FOR(i, 0, m) FOR(j, 0, m) g[i] += c[j][i], h[i] += c[i][j];
  FOR(i, 0, m) FOR(u, 0, 1 << H) {
    FOR(j, 0, H) if ((u >> j) & 1) {
      g1[i][u] += c[j][i];
      h1[i][u] += c[i][j];
    }
  }
  FOR(i, 0, m) FOR(u, 0, 1 << (m - H)) {
    FOR(j, 0, m - H) if ((u >> j) & 1) {
      g2[i][u] += c[j + H][i];
      h2[i][u] += c[i][j + H];
    }
  }
  FOR(u, 1, 1<<m) {
    f[u] = INT_MAX;
    int ci = __builtin_popcount(u);
    FOR(i, 0, m) if ((u>>i)&1) {
      int v = u ^ (1<<i);
      int cur = 0;
      cur = k * g[i] - h[i];
      cur -= (k - 1) * (g1[i][v & T] + g2[i][v >> H]);
      cur += (k + 1) * (h1[i][v & T] + h2[i][v >> H]);
      cur *= ci;
      cur += f[v];
      /*
      FOR(j, 0, m) {
        if ((v>>j)&1) {
          cur += ci * c[j][i];
          cur += k * ci * c[i][j];
        } else {
          cur += k * ci * c[j][i];
          cur -= ci * c[i][j];
        }
      }
      */
      chkmin(f[u], cur);
    }
  }
  println(f[(1<<m)-1]);
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


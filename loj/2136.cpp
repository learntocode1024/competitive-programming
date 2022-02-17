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
typedef long double dbl;
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
const int N = 12, M = 95;
int n, m;
int G[N][N];
dbl f[1<<N][M], fac[M];
int cnt[1<<N];

inline dbl C(int n, int k) {
  if (n < k || k < 0) return 0;
  return fac[n] / fac[k] / fac[n-k];
}

inline void solve() {
  rd(n, m);
  FOR(i, 0, m) {
    int u, v;
    rd(u, v);
    --u, --v;
    G[u][v] = G[v][u] = 1;
  }
  fac[0] = fac[1] = 1;
  FOR(i, 2, M) fac[i] = fac[i-1] * i;
  
  FOR(u, 0, 1 << n) {
    FOR(i, 0, n) FOR(j, i + 1, n) {
      if (G[i][j] && ((u >> i) & 1) && ((u >> j) & 1)) {
        ++cnt[u];
      }
    }
  }
  FOR(u, 1, 1 << n) {
    if (__builtin_popcount(u) == 1) {
      f[u][0] = 1;
    } else {
      FOR(i, 0, cnt[u] + 1) {
        f[u][i] = C(cnt[u], i);
        for (int s = (u - 1) & u; s > (u ^ s); s = (s - 1) & u) {
          FOR(j, 0, min(cnt[s], i) + 1) {
            f[u][i] -= f[s][j] * C(cnt[u^s], i-j);
          }
        }
      }
    }
  }
  int u = (1 << n) - 1;
  dbl ans = 0;
  FOR(i, 1, m + 1) {
    ans += 1.0l * i / (m + 1) * (f[u][i] / C(m, i) - f[u][i-1] / C(m, i-1));
  }
  cout << fixed << setprecision(6) << ans << '\n';
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


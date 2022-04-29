#include <bits/stdc++.h>
using namespace std;
#ifndef MISAKA
#define OO(x)
#else
#define OO(x) cout << __PRETTY_FUNCTION__ << ": " << #x << " : " << (x) << '\n';
#endif
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
void O(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void O(const A& a, const B& ...b) {
  cout << a << ' ';
  O(b...);
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
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

//#define MULTI
const int N = 105, M = 5005;
const int p = 998244353;
int n, t, s;
int f[N][N][N];
int g[N][N];
int to[N][M], m[N];
int inv[M];

inline void solve() {
  inv[1] = 1;
  FOR(i,2,M-1) {
    inv[i] = 1ll * (p-p/i) * inv[p%i] % p;
  }
  rd(n,s,t);
  FOR(i,1,n) f[i][i][0] = 1;
  FOR(i,1,n) {
    rd(m[i]);
    FOR(j,1,m[i]) rd(to[i][j]);
  }
  FOR(i,0,t-1) FOR(j,1,n) FOR(k,1,n) if (f[j][k][i]) {
    FOR(l, 1, m[k]) {
      f[j][to[k][l]][i+1] = (f[j][to[k][l]][i+1] + 1ll * inv[m[k]] * f[j][k][i]) % p;
    }
  }
  int ans = 0;
  FOR(u,1,n) {
    FOR(tt,1,m[u]) {
      int v = to[u][tt];
      g[v][0] = v == u;
      FOR(i,1,t) {
        g[v][i] = f[v][u][i];
        FOR(j,0,i-1) {
          g[v][i] = (g[v][i] + p - 1ll * g[v][j] * f[u][u][i-j] % p) % p;
        }
      }
      FOR(i,1,t) g[v][i] = (g[v][i] + g[v][i-1]) % p;
    }
    FOR(i,0,t-1) {
      FOR(nxt,1,m[u]) {
        int v = to[u][nxt];
        ans = (ans + 1ll * v * f[s][u][i] % p * g[v][t-i-1]) % p;
      }
    }
  }
  O(ans);
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


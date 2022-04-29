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
const int N = 3e5+5, D = 50, L = 90;
const int mod = 998244353;
const int mu[L] = {
  0,1,-1,-1,0,-1,1,-1,0,0,1,-1,0,-1,1,1,0,-1,0,-1,0,
 1,1,-1,0,0,1,0,0,-1,-1,-1,0,1,1,1,0,-1,1,1,0,-1,
 -1,-1,0,0,1,-1,0,0,0,1,0,-1,0,1,0,1,1,-1,0,-1,1,0,
 0,1,-1,-1,0,1
};
int n, k;
vector<int> G[N];
int f[N][L], g[N][L];
int ans = 0;
int dp[D][D];

void dfs(int u) {
  f[u][0] = 1;
  for (auto v : G[u]) {
    dfs(v);
    for (int i = 0; i < L && f[v][i]; ++i) {
      f[u][i+1] += f[v][i];
    }
  }
}

void dfs2(int u, int fa) {
  if (G[u].size() + (u != 1) >= k) for (int i = 1; i < L; ++i) {
    if (!mu[i]) continue;
    int t = 1, vl = 0;
    dp[1][1] = 0;
    dp[1][0] = 1;
    for (int j = i; j < L; j += i) dp[1][1] += g[u][j];
    for (auto v : G[u]) {
      vl = 0;
      for (int j = i - 1; j < L; j += i) vl += f[v][j];
      ++t;
      dp[t][0] = 1;
      FOR(j,1,min(k,t)) {
        dp[t][j] = (dp[t-1][j] + 1ll * dp[t-1][j-1] * vl) % mod;
      }
    }
    if (mu[i] > 0) ans = (ans + dp[t][k]) % mod;
    else ans = (ans - dp[t][k] + mod) % mod;
  }
  for (auto v : G[u]) {
    for (int i = 0; i < L-1; ++i) {
      g[v][i+1] = g[u][i] + f[u][i];
      if (i) g[v][i+1] -= f[v][i-1];
    }
    dfs2(v, u);
  }
}

inline void solve() {
  rd(n,k);
  dp[0][0] = 1;
  FOR(i,2,n) {
    int u, v;
    rd(u,v);
    if (u < v) swap(u,v);
    G[v].pb(u);
  }
  bool sol = 0;
  FOR(i,1,n) sol |= G[i].size() >= k;
  if (!sol) {
    O(0);
    return;
  }
  dfs(1);
  dfs2(1, 0);
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


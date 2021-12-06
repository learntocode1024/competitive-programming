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

const int N = 5e4+5;
vector<pii> g[N];
int b[N];
i64 h[18][N];
int f[18][N];
int n, m;
bool vis[N];

void dfs(int u, int fa) {
  for (auto v : g[u]) {
    if (v.fi != fa) {
      f[0][v.fi] = u;
      h[0][v.fi] = v.se;
      dfs(v.fi, u);
    }
  }
}

inline pair<int, i64> to(int u, i64 w) {
  i64 cw = 0;
  ROF(i, 0, 18) {
    if (f[i][u] && h[i][u] + cw <= w) {
      cw += h[i][u];
      u = f[i][u];
    }
  }
  return {u, w - cw};
}

bool valid(int u, int fa) {
  if (vis[u]) return true;
  else if (g[u].size() == 1) return false;
  for (auto v : g[u]) {
    if (v.fi == fa) continue;
    if (!valid(v.fi, u)) return false;
  }
  return true;
}

set<pair<i64,int> > S;
set<pair<i64,int>, greater<pair<i64, int> > > T;
i64 mV[N], R[N];

bool chk(i64 w) {
  S.clear();
  T.clear();
  FOR(i, 1, n + 1) vis[i] = 0, mV[i] = -1;
  FOR(i, 0, m) {
    auto [u, r] = to(b[i], w);
    if (u == 1) {
      S.insert({r, i});
      int l = lst(b[i]);
      R[i] = r;
      if (mV[l] == -1) mV[l] = i;
      else if (R[mV[l]] > r) mV[l] = i;
    }
    else vis[u] = 1;
  }
  for (auto v : g[1]) {
    if (!valid(v.fi, 1)) {
      T.insert({v.se, v.fi});
    }
  }
  for (auto [w, u] : T) {
    auto it = S.lower_bound({w, 0});
    if (it != S.end()) {
      if (mV[u] != -1) {
        
      }
    } else return false;
  }
  return true;
}

inline void solve() {
  cin >> n;
  FOR(i, 1, n) {
    int u, v, w;
    rd(u, v, w);
    g[u].eb(v, w);
    g[v].eb(u, w);
  }
  cin >> m;
  FOR(i, 0, m) cin >> b[i];
  dfs(1, 0);
  FOR(i, 1, 18) FOR(j, 1, n + 1) {
    h[i][j] = h[i-1][f[i-1][j]] + h[i-1][j];
    f[i][j] = f[i-1][f[i-1][j]];
  }
  if (chk(0)) {
    println(-1);
  }
  i64 l = 0, r = 1e16;
  while (r - l > 1) {
    i64 mid = (l + r) >> 1;
    if (chk(mid)) r = mid;
    else l = mid;
  }
  if (r == 1e16) println(-1);
  else println(r);
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

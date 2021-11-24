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
template <typename T> int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

const int N = 6e5+5;
set<int> S[N][2];
char s[N];
bool msk[N], vis[N];
int u[N], v[N], w[N];
int p1[N], p2[N];
int n, m, m0;
vector<pii> g[N];

void col(int id, int a) {
  if (id <= m0) {
    if (1 == a) s[id] = '1';
    else s[id] = '2';
    return;
  }
  col(abs(p1[id]), a * sgn(p1[id]));
  col(abs(p2[id]), a * sgn(p2[id]));
}

void merge(int i, int j) {
  int c = ++m;
  w[c] = w[i];
}

void dfs(int u, int op) {
  if (vis[u]) return;
  for (auto [v, id] : g[u]) {
    if (!vis[v]) {
      col(abs(id), op * sgn(id));
      dfs(v, -op);
    }
  }
}

inline void solve() {
  cin >> n >> m;
  m0 = m;
  FOR(i, 1, m + 1) rd(u[i], v[i], w[i]);
  FOR(i, 1, m + 1) {
    --w[i];
    S[u[i]][w[i]].insert(i);
    S[v[i]][w[i]].insert(i);
  }
  // merge edges
  FOR(i, 1, n + 1) {
    FOR(j, 0, 2) {
      if (S[i][j].size() > 1) {
        auto it = S[i][j].begin();
        for (int t = 0; t < S[i][j].size(); t += 2) {
          int a = *it;
          ++it;
          int b = *it;
          ++it;
          merge(a, b);
        }
      }
    }
  }
  // dfs
  FOR(i, 1, m + 1) {
    if (!msk[i]) g[u[i]].eb(v[i], i), g[v[i]].eb(u[i], -i);
  }
  FOR(i, 1, n + 1) dfs(i, 1);
  cout << s;
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


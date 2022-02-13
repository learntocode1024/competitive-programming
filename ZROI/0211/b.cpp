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
const int N = 2005;
int n;
vector<int> g1[N], g2[N];
int cnt[N*N];
int to, tot1, tot2, v1[N], v2[N];

void get1(int u, int fa) {
  if (u == to) {
    v1[u] = 114514;
    return;
  }
  for (auto v : g1[u]) if (v != fa) {
    get1(v, u);
    if (v1[v] == 114514) {
      v1[u] = 114514;
      return;
    }
  }
}
void get2(int u, int fa) {
  if (u == to) {
    v2[u] = 114514;
    return;
  }
  for (auto v : g2[u]) if (v != fa) {
    get2(v, u);
    if (v2[v] == 114514) {
      v2[u] = 114514;
      return;
    }
  }
}

void dfs1(int u, int fa) {
  v1[u] = tot1;
  for (auto v : g1[u]) if (v != fa && !v1[v]) {
    dfs1(v, u);
  }
}

void dfs2(int u, int fa) {
  v2[u] = tot2;
  for (auto v : g2[u]) if (v != fa && !v2[v]) {
    dfs2(v, u);
  }
}

inline void solve() {
  cin >> n;
  FOR(i, 0, n * 2 - 3) {
    int u, v;
    rd(u, v);
    g1[u].pb(v);
    g1[v].pb(u);
  }
  FOR(i, 0, n * 2 - 3) {
    int u, v;
    rd(u, v);
    g2[u].pb(v);
    g2[v].pb(u);
  }
  i64 rec = 0, c4 = 1;
  FOR(i, 0, 4) c4 = c4 * (n-i);
  c4 /= 12ll;
  FOR(i, 1, n + 1) FOR(j, i+1, n + 1) {
    FOR(k, 1, n*2-1) {
      v1[k] = v2[k] = 0;
    }
    tot1 = tot2 = 0;
    to = j;
    get1(i, 0);
    get2(i, 0);
    FOR(k, 1, n*2-1) {
      if (!v1[k]) ++tot1, dfs1(k, 0);
      if (!v2[k]) ++tot2, dfs2(k, 0);
    }
    FOR(k, 1, n + 1) {
      if (v1[k] != 114514 && v2[k] != 114514) ++cnt[v1[k]<<11|v2[k]];
    }
    FOR(k, 1, n + 1) {
      if (v1[k] != 114514 && v2[k] != 114514) {
        int id = v1[k]<<11|v2[k];
        rec += (cnt[id] * (cnt[id]-1)) >> 1;
        cnt[id] = 0;
      }
    }
  }
  println(c4 - rec);
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


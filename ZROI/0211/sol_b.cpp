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
i64 cnt;
int v[N], cv[3];
int eu[N], ev[N], tot;
int f[N][3];

void col(int u, int fa, int ccol) {
  if (u <= n) v[u] = ccol, ++cv[ccol];
  for (auto v : g1[u]) if (v != fa) {
    col(v, u, ccol);
  }
}

int c2(int x) {
  return x * (x-1) / 2;
}

int g[3][3];

void calc(int u, int fa) {
  FOR(i, 0, 3) f[u][i] = 0;
  if (u <= n) {
    f[u][v[u]] = 1;
    return;
  }
  for (auto v : g2[u]) if (v != fa) {
    calc(v, u);
    FOR(i, 0, 3) f[u][i] += f[v][i];
  }
  memset(g, 0, sizeof(g));
  int c = 0;
  for (auto v : g2[u]) if (v != fa) {
    FOR(i, 0, 3) g[c][i] = f[v][i];
    ++c;
  }
  if (fa != 0) {
    int a0 = c2(cv[0] - f[u][0]);
    int a1 = c2(cv[1] - f[u][1]);
    int a2 = c2(cv[2] - f[u][2]);
    int s = a0 + a1 + a2;
    cnt += c2(f[u][0]) * (s - a0);
    cnt += c2(f[u][1]) * (s - a1);
    cnt += c2(f[u][2]) * (s - a2);
    FOR(i, 0, 3) g[c][i] = cv[i] - f[u][i];
  }
  FOR(i, 0, 3) FOR(j, i + 1, 3) {
    int a0 = c2(g[j][0]);
    int a1 = c2(g[j][1]);
    int a2 = c2(g[j][2]);
    int s = a0 + a1 + a2;
    cnt -= c2(g[i][0]) * (s - a0);
    cnt -= c2(g[i][1]) * (s - a1);
    cnt -= c2(g[i][2]) * (s - a2);
  }
}

inline void solve() {
  cin >> n;
  FOR(i, 0, n * 2 - 3) {
    int u, v;
    rd(u, v);
    g1[u].pb(v);
    g1[v].pb(u);
    if (u > n && v > n) {
      eu[tot] = u;
      ev[tot] = v;
      ++tot;
    }
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
  FOR(i, 0, tot) { // edge
    cv[0] = cv[1] = cv[2] = 0;
    col(eu[i], ev[i], 0);
    col(ev[i], eu[i], 1);
    calc(n+1, 0);
    rec += cnt;
    cnt = 0;
  }
  FOR(i, n + 1, n * 2 - 1) { // vertex
    cv[0] = cv[1] = cv[2] = 0;
    int tc = 0;
    for (auto v : g1[i]) {
      col(v, i, tc++);
    }
    calc(n+1, 0);
    rec -= cnt;
    cnt = 0;
  }
  println(c4 - rec*2);
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


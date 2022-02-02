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
const int N = 1e5+5;
const i64 k = 1e9, inf = 1e18;
vector<pair<int, i64> > g[N];
i64 d[N];
priority_queue<pair<i64, int> > pq;
int n;
bool vis[N];

template<typename T>
class diff_constraints {
  std::vector<std::vector<std::pair<int, T> > > g;
  std::vector<T> d;
  int n;
public:
  diff_constraints(int _n) : g(_n + 1), n(_n), d(_n + 1, std::numeric_limits<T>::max()) {};
  void add_edge(int u, int v, T c) {
    g[v].emplace_back(u, c);
  }
  std::pair<std::vector<T>, bool> solve() {
    for (int i = 1; i <= n; ++i) {
      g[0].emplace_back(i, 0);
    }
    d[0] = 0;
    bool flag = 0;
    for (int i = 0; i <= n; ++i) {
      flag = 0;
      for (int u = 0; u <= n; ++u) {
        for (auto v : g[u]) {
          if (d[v.first] > d[u] + v.second) {
            d[v.first] = d[u] + v.second;
            flag = 1;
          }
        }
      }
    }
    if (flag) return {{}, 0};
    std::vector<T> out;
    for (int i = 1; i <= n; ++i) out.push_back(d[i] == std::numeric_limits<T>::max() ? 0 : d[i]);
    return {out, 1};
  }
};
inline void solve() {
  cin >> n;
  diff_constraints<i64> G(n);
  FOR(i, 1, n + 1) {
    int j;
    cin >> j;
    if (i!=j) G.add_edge(j, i, k);
    if (j != n) G.add_edge(i, j + 1, -k - 1);
  }
  FOR(i, 1, n) G.add_edge(i, i + 1, 0);
  auto [res, ok] = G.solve();
  if (!ok) exit(1);
  i64 mn = 0;
  for (auto v : res) chkmin(mn, v);
  println(k);
  for (auto v : res) println(v - mn + 1);
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


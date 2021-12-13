#include <bits/stdc++.h>
using namespace std;
template <typename T>
void rd(T& a) {
  cin >> a;
}
template <typename A, typename... B>
void rd(A& a, B&... b) {
  cin >> a;
  rd(b...);
}
template <typename A>
void print(const A& a) {
  cout << a;
}
template <typename A, typename... B>
void print(const A& a, const B&... b) {
  cout << a;
  print(b...);
}
template <typename A>
void println(const A& a) {
  cout << a << '\n';
}
template <typename A, typename... B>
void println(const A& a, const B&... b) {
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
#define ROF(i, j, k) for (int i = ((k)-1); i >= j; --i)
template <typename T>
inline void chkmin(T& a, const T b) {
  a = min(a, b);
}
template <typename T>
inline void chkmax(T& a, const T b) {
  a = max(a, b);
}

template <typename T>
class diff_constraints {
  vector<vector<pair<int, T> > > g;
  vector<T> d;
  int n;

 public:
  diff_constraints(int _n)
      : g(_n + 1), n(_n), d(_n + 1, numeric_limits<T>::max()){};
  inline void add_edge(int u, int v, T c) { g[v + 1].emplace_back(u + 1, c); }
  inline pair<vector<T>, bool> solve() {
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
    vector<T> out;
    for (int i = 1; i <= n; ++i)
      out.push_back(d[i] == numeric_limits<T>::max() ? 0 : d[i]);
    return {out, 1};
  }
};

const int N = 305;
int n, m;
int a[N][N], b[N][N];

inline void solve() {
  cin >> n >> m;
  FOR(i, 1, n) FOR(j, 1, m) cin >> b[i][j];
  FOR(i, 1, n)
  FOR(j, 1, m) a[i][j] = b[i][j] - a[i - 1][j] - a[i][j - 1] - a[i - 1][j - 1];
  diff_constraints<i64> f(n + m);
  FOR(i, 0, n) FOR(j, 0, m) {
    if ((i & 1) ^ (j & 1)) {
      f.add_edge(n + j, i, a[i][j]);
      f.add_edge(i, n + j, 1000000 - a[i][j]);
    } else {
      f.add_edge(i, n + j, a[i][j]);
      f.add_edge(n + j, i, 1000000 - a[i][j]);
    }
  }
  auto ret = f.solve();
  if (ret.se) {
    println("YES");
    FOR(i, 0, n) FOR(j, 0, m) {
      if ((i & 1) ^ (j & 1)) {
        a[i][j] -= ret.fi[n + j] - ret.fi[i];
      } else {
        a[i][j] += ret.fi[n + j] - ret.fi[i];
      }
      cout << a[i][j] << " \n"[j == m - 1];
      a[i][j] = 0;
    }
  } else
    println("NO");
}

int main() {
#ifndef MISAKA
  // freopen(".in", "r", stdin);
  // freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
int T;
cin >> T;
while (T--)
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

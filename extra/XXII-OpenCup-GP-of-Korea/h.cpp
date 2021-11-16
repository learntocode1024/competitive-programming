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

const int N = 3e5;
vector<pii> g[N];
i64 d[8][N];
bool vis[8][N];
int a[N], c[N];
typedef pair<i64, int> pli;
priority_queue<pli, vector<pli>, greater<pli> > pq;
int n, l;
i64 t;

inline void solve() {
  cin >> n >> l >> t;
  FOR(i, 1, l + 1) {
    int u, v;
    cin >> u >> v;
    g[v].eb(u, i);
  }
  FOR(i, 1, n + 1) cin >> a[i];
  for (int i = 0; i < 8; ++i) {
    FOR(I, 1, n + 1) d[i][I] = t + 1;
    FOR(I, 1, n + 1) {
      if ((a[I] >> i) & 1) {
        d[i][I] = 0;
        pq.push({0, I});
      }
    }
    while (!pq.empty()) {
      auto u = pq.top();
      pq.pop();
      if (vis[i][u.se]) continue;
      vis[i][u.se] = 1;
      for (auto v : g[u.se]) {
        i64 w = (u.fi % l < v.se) ? u.fi + v.se - u.fi % l
                                  : u.fi + l - u.fi % l + v.se;
        chkmin(w, t + 1);
        if (d[i][v.fi] > w) {
          d[i][v.fi] = w;
          pq.push({w, v.fi});
        }
      }
    }
    FOR(I, 1, n + 1) if (d[i][I] <= t) c[I] |= 1 << i;
  }
  FOR(i, 1, n + 1) cout << c[i] << " \n"[i == n];
}

int main() {
#ifndef MISAKA
  // freopen(".in", "r", stdin);
  // freopen(".out", "w", stdout);
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

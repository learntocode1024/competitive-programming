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

const int M = 1e5+5, N = 1e6+5;
int n, m;
int V[N];

set<int> S;
struct dist {
  i64 dis;
  int x;
  int t;
  dist() = default;
  dist(int _x, i64 _dis, int _t) {
    x = _x, dis = _dis, t = _t;
  }
  bool operator< (const dist &rhs) const {
    return dis > rhs.dis;
  }
};
priority_queue<dist> pq;

map<int, i64> d;
map<int, vector<pii> > g;

inline void run_dist() {
  pq.emplace(1, 0, 0);
  S.insert(1);
  d[1] = 0;
  while (!pq.empty()) {
    auto u = pq.top();
    pq.pop();
    auto it = S.find(u.x);
    if (u.t == 1) {
      auto itn = S.upper_bound(u.x);
      if (itn != S.end()) {
        pq.emplace(*itn, u.dis - u.x + *itn, 1);
      }
    }
    if (it == S.end()) continue;
    d[u.x] = u.dis;
    auto itn = it;
    ++itn;
    if (itn != S.end()) {
      pq.emplace(*itn, u.dis - u.x + *itn, 1);
    }
    for (auto v : g[u.x]) {
      if (S.find(v.fi) == S.end()) continue;
      if (d.find(v.fi) == d.end() || d[v.fi] > u.dis + v.se) {
        d[v.fi] = u.dis + v.se;
        pq.emplace(v.fi, u.dis + v.se, 0);
      }
    }
    S.erase(u.x);
  }
}

inline void solve() {
  cin >> n >> m;
  FOR(i, 0, n) cin >> V[i];
  FOR(i, 0, m) {
    int a, b, c;
    cin >> a >> b >> c;
    g[b].eb(a, c);
    S.insert(a);
    S.insert(b);
  }
  run_dist();
  i64 cur = INT_MAX;
  for (auto &v : d) {
    //cerr << v.fi << ' ' << v.se << '\n';
    chkmin(cur, v.se - v.fi);
    v.se = cur;
    //cerr << v.se << '\n';
  }
  i64 ans = 0;
  FOR(i, 0, n) {
    auto it = d.lower_bound(V[i]);
    if (it == d.end() || it->fi > V[i]) --it;
    ans += it->se + V[i];
    //cerr << it->se + V[i] << '\n';
  }
  cout << ans << '\n';
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


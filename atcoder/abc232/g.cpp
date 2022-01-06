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
typedef pair<i64, int> pii;
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

const int N = 2e5+5;
map<int, vector<int> > s;
int a[N], b[N];
int n, m;
i64 d[N];
priority_queue<pii, vector<pii>, greater<pii> > pq;
int nxt(int x) {
  if (x > s.end()->fi) return s.begin()->fi;
  else return s.lower_bound(x)->fi;
}

inline void solve() {
  rd(n, m);
  FOR(i, 1, n + 1) cin >> a[i];
  FOR(i, 1, n + 1) cin >> b[i];
  FOR(i, 1, n) s[a[i]].pb(i);
  int ori = nxt((m - b[n]) % m);
  pq.push(mkp((ori + b[n]) % m, ori));
  while (!pq.empty()) {
    auto u = pq.top();
    pq.pop();
    if (s.find(u.se) == s.end()) {
      continue;
    }
    for (auto v : s[u.se]) {
      d[v] = u.fi;
      pq.push();
    }
    s.erase(u.se);
  }
  println(d[1]);
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


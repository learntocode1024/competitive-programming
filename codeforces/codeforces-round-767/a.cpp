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

#define MULTI
const int N = 2e5+5;
int n, m;
int b[N], a[N];
vector<int> S[N];
set<int> T;

inline int nxt(int x, int v) {
  auto it = lower_bound(begin(S[v]), end(S[v]), x);
  if (it == S[v].end()) return -1;
  else return *it;
}

inline void solve() {
  m = 0;
  rd(n);
  FOR(i, 0, n + 1) S[i].clear();
  FOR(i, 0, n + 2) T.insert(i);
  FOR(i, 1, n + 1) {
    cin >> a[i];
    S[a[i]].pb(i);
  }
  int i = 1;
  while (i <= n) {
    int t = nxt(i, 0);
    if (t == -1) {
      FOR(j, i, n + 1) b[++m] = 0;
      break;
    }
    FOR(j, i, t + 1) T.erase(a[j]);
    while (t < n) {
      int tt = nxt(t + 1, *T.begin());
      if (tt == -1) break;
      FOR(j, t + 1, tt + 1) T.erase(a[j]);
      t = tt;
    }
    b[++m] = *T.begin();
    FOR(j, i, t + 1) T.insert(a[j]);
    i = t + 1;
  }
  println(m);
  FOR(i, 1, m+1) cout << b[i] << " \n"[i==m];
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


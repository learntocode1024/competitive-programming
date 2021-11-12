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

const int N = 2e5+5;
const int inf = 1919810;
int p1[N], p2[N], p3[N];
int r1[N], r2[N], r3[N];
int n;

struct SEGT_MN {
  int c[N];
  inline void build(int *a) {
    
  }
};

struct DS1 {

} T1;

bool scc_path(int u, int v) {
  if (scc[u] == scc[v]) return true;
}

inline void solve() {
  cin >> n;
  FOR(i, 1, n + 1) rd(p1[i], p2[i], p3[i]);
  FOR(i, 1, n + 1) r1[p1[i]] = r2[p2[i]] = r3[p3[i]] = i;
  build_scc();
  int q;
  cin >> q;
  while (q--) {
    int u, v;
    cin >> u >> v;
    println(scc_path(u, v) ? "YES" : "NO");
  }
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


#include <bits/stdc++.h>
namespace {
using namespace std;
template <typename T> inline void O(const T &x) { cout << x << '\n'; }
template <typename T, typename... W> inline void O(const T &x, const W &...b) {
  cout << x << ' ';
  O(b...);
}
template <typename T> inline void rd(const T &x) { cin >> x; }
template <typename T, typename... W> inline void rd(const T &x, const W &...b) {
  cin >> x;
  rd(b...);
}
#ifndef MISAKA
#define err(...)
#else
#define err(...) fprintf(stderr, __VA_ARGS__)
#endif
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef long double dbl;
typedef pair<int, int> pii;
typedef uniform_int_distribution<int> r32;
typedef uniform_int_distribution<i64> r64;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define shuf(L, R) shuffle((L), (R), rng)
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template <typename T> inline void ckmin(T &a, const T &b) { a = min(a, b); }
template <typename T> inline void ckmax(T &a, const T &b) { a = max(a, b); }
//#define IOFILE "filename"
//#define MULTI
vector<vector<int> > g;
vector<int> ans;
void dfs(int u, int fa) {
  ans[u-1] = ans[fa-1];
  if (u < fa) ans[u-1] ^= 1;
  for (auto v : g[u]) if (v != fa) dfs(v, u);
}
}
std::vector <int> Init(int N, int T, std::vector <int> A, std::vector <int> B) {
  g.resize(N+1);
  ans.resize(N);
  FOR(i,0,N-2) {
    g[A[i]].pb(B[i]);
    g[B[i]].pb(A[i]);
  }
  dfs(T, T);
  return ans;
}

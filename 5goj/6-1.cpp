#include <bits/stdc++.h>
using namespace std;
#ifndef MISAKA
#define OO(x)
#else
#define OO(x) cout << __PRETTY_FUNCTION__ << ": " << #x << " : " << (x) << '\n';
#endif
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
void O(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void O(const A& a, const B& ...b) {
  cout << a << ' ';
  O(b...);
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
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

//#define MULTI
const int N = 2e5+5;
i64 ans;
int f[N];
bool typ[N];

struct E {
  int u, v, w;
  bool operator< (const E& r) const {
    return w < r.w;
  }
} e[N];

int get(int x) {
  return x == f[x] ? x : f[x] = get(f[x]);
}

inline void solve() {
  int n, m;
  rd(n,m);
  int tot = 0;
  iota(f,f+n+m+1,0);
  FOR(i,1,n) FOR(j,1,m) {
    int a;
    rd(a);
    e[tot++] = {i,j+n,a};
  }
  sort(e, e + tot);
  int cnt = n;
  FOR(i,0,tot-1) {
    int u = get(e[i].u), v = get(e[i].v);
    if (u == v) {
      if (!typ[u]) ans += e[i].w, typ[u] = 1;
      --cnt;
    } else {
      if (typ[u] && typ[v]) continue;
      f[v] = u;
      typ[u] |= typ[v];
      ans += e[i].w;
    }
  }
  O(ans);
}

int main() {
#ifndef MISAKA
  freopen("junior.in", "r", stdin);
  freopen("junior.out", "w", stdout);
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


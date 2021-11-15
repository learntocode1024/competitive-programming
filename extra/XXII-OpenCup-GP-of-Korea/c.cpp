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

const int N = 5e5+5;
const i64 p = 901807721642715077ll;
inline void red(i64 &x) { if (x >= p) x -= p; }
mt19937 rng(chrono::steady_clock().now().time_since_epoch().count());
int d, n;
i64 a[N], c[N], H[N];
int f[N];
unordered_map<i64, int> mp;
pair<int, pair<int,int> > e[N];

inline void init() {
  iota(f, f + n + 1, 0);
  copy(a, a + n + 1, c);
}

int get(int x) {
  if (x == f[x]) return x;
  return (f[x] = get(f[x]));
}

inline __int128 merge(int u, int v) {
  u = get(u);
  v = get(v);
  f[v] = u;
  __int128 ret = c[u];
  ret = ret * c[v] % p;
  red(c[u] += c[v]);
  return ret;
}

inline void solve() {
  rd(d, n);
  FOR(i, 1, n + 1) a[i] = rng();
  FOR(_, 1, d + 1) {
    FOR(i, 1, n) rd(e[i].se.fi, e[i].se.se, e[i].fi);
    sort(e + 1, e + n);
    reverse(e + 1, e + n);
    init();
    FOR(i, 1, n) {
      red(H[_] += merge(e[i].se.fi, e[i].se.se) * e[i].fi % p);
    }
    if (mp.find(H[_]) == mp.end()) {
      mp[H[_]] = _;
    }
  }
  FOR(i, 1, d + 1) {
    cout << mp[H[i]] << " \n"[i==d];
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


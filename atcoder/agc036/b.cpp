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
int hd[N], lst[N], nxt[N], r[N];
int a[N], p[N];

inline void solve() {
  int n;
  i64 k;
  rd(n, k);
  FOR(i,1,n) rd(a[i]);
  FOR(i,1,n) {
    if (!hd[a[i]]) hd[a[i]] = i;
    nxt[lst[a[i]]] = i;
    lst[a[i]] = i;
  }
  r[n] = n;
  ROF(i,1,n-1) {
    r[i] = nxt[i] ? r[nxt[i]+1] : i;
  }
  int m = 0;
  p[m++] = 1;
  while (true) {
    p[m] = hd[a[r[p[m-1]]]]+1;
    if (p[m] == 1) break;
    else ++m;
  }
  --k;
  k %= m;
  if (p[k] == n+1) return;
  int u = p[k];
  while (u <= n) {
    if (nxt[u]) u = nxt[u] + 1;
    else cout << a[u] << ' ', ++u;
  }
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


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

#define MULTI
const int N = 2e5+5;
i64 a[N], b[N];

inline void solve() {
  int n;
  rd(n);
  FOR(i,1,n) rd(a[i]);
  FOR(i,1,n) rd(b[i]);
  i64 ans = 0, a2 = abs(a[1]-b[1]), a3 = abs(a[n]-b[n]), a4 = abs(a[1]-b[n]), a5 = abs(a[n]-b[1]);
  i64 x = INT_MAX;
  FOR(i,1,n) chkmin(x, abs(a[1]-b[i]));
  ans += x;
  x = INT_MAX;
  FOR(i,1,n) chkmin(x, abs(a[n]-b[i]));
  ans += x;
  x = INT_MAX;
  FOR(i,1,n) chkmin(x, abs(b[1]-a[i]));
  ans += x;
  x = INT_MAX;
  FOR(i,1,n) chkmin(x, abs(b[n]-a[i]));
  ans += x;
  x = INT_MAX;
  FOR(i,1,n) chkmin(x, abs(a[1]-b[i]));
  a3 += x;
  x = INT_MAX;
  FOR(i,1,n) chkmin(x, abs(a[n]-b[i]));
  a2 += x;
  x = INT_MAX;
  FOR(i,1,n) chkmin(x, abs(b[1]-a[i]));
  a3 += x;
  x = INT_MAX;
  FOR(i,1,n) chkmin(x, abs(b[n]-a[i]));
  a2 += x;
  x = INT_MAX;
  FOR(i,1,n) chkmin(x, abs(a[1]-b[i]));
  a5 += x;
  x = INT_MAX;
  FOR(i,1,n) chkmin(x, abs(a[n]-b[i]));
  a4 += x;
  x = INT_MAX;
  FOR(i,1,n) chkmin(x, abs(b[1]-a[i]));
  a4 += x;
  x = INT_MAX;
  FOR(i,1,n) chkmin(x, abs(b[n]-a[i]));
  a5 += x;
  O(min({min(ans,min(a2,min(a3,abs(a[1]-b[1])+abs(a[n]-b[n])))), abs(a[1]-b[n])+abs(a[n]-b[1]),a4,a5}));
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


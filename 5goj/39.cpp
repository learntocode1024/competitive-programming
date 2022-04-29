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
int n;
i64 a[N];
map<pair<int, i64>, i64> mf;
i64 f(int i, i64 x) {
  if (i == n) return n * (x-1);
  if (mf.find({i,x}) != mf.end()) return mf[{i,x}];
  int p = upper_bound(a+1,a+n+1,x,greater<i64>{}) - a;
  chkmin(p,n);
  i64 d = x / a[p];
  return mf[{i,x}] = max(f(p,a[p])+a[p]*(d-1)*(p-1), f(p, x % a[p]) + d * a[p] * (p-1));
}

inline void solve() {
  rd(n);
  FOR(i,1,n) rd(a[i]);
  FOR(i,2,n) chkmin(a[i], a[i-1]);
  O(f(1,a[1]));
}

int main() {
#ifndef MISAKA
  freopen("sum.in", "r", stdin);
  freopen("sum.out", "w", stdout);
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


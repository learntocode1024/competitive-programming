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
const int N = 1e5+5;
char s[N];
int n;

int get(i64 t, i64 k) {
  if (t > 63) {
    return (t-63+get(63, k)) % 3;
  }
  if (t == 0) return 0;
  i64 mid = 1ll << (t-1);
  if (k < mid) return (1+get(t-1,k)) % 3;
  else return(2+get(t-1,k&(mid-1))) % 3;
}

inline void solve() {
  i64 t, k, i, r;
  rd(t,k);
  --k;
  if (t <= 63) {
  i = k >> t;
  r = k - (i << t);
  } else {
    i = 0;
    r = k;
  }
  O(char('A' + (s[i]+get(t,r))%3));
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
  rd(s);
  n = strlen(s);
  FOR(i,0,n-1) s[i] -= 'A';
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


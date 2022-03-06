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
const int N = 1e6+5;
const int p = 998244353;
char s[N], t[N];
int n;

int pw[N];

inline void solve() {
  rd(n, s);
  int m = n / 2;
  int r = m + (n&1) - 1;
  int ans = 0;
  FOR(i,0,m-1) {
    FOR(j,'A',s[i]-1) {
      ans = (ans + pw[r-i]) % p;
    }
  }
  if (n & 1) {
    ans = (ans + (s[n/2]-'A')) % p;
    t[n/2] = s[n/2];
  }
  FOR(i, 0, n/2-1) {
    t[i] = t[n-i-1] = s[i];
  }
  bool ok = 1;
  FOR(i, 0,n-1) {
    if (s[i] != t[i]) {
      if (s[i] < t[i]) ok = 0;
      break;
    }
  }
  ans = (ans + ok) % p;
  O(ans);
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
  pw[0] = 1;
  FOR(i,1,N-1) pw[i] = 26ll * pw[i-1] % p;
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


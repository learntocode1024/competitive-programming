#include <bits/stdc++.h>
using namespace std;
#ifndef MISAKA
#define OO(x)
#else
#define OO(x) cout << __PRETTY_FUNCTION__ << ": " << #x << " : " << (x) << '\n';
#endif
template <typename T>
void rd(T& a) {
  cin >> a;
}
template <typename A, typename... B>
void rd(A& a, B&... b) {
  cin >> a;
  rd(b...);
}
template <typename A>
void O(const A& a) {
  cout << a << '\n';
}
template <typename A, typename... B>
void O(const A& a, const B&... b) {
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
template <typename T>
inline void chkmin(T& a, const T b) {
  a = min(a, b);
}
template <typename T>
inline void chkmax(T& a, const T b) {
  a = max(a, b);
}

//#define MULTI
const int N = 1e7 + 5;
char s[N];
bool vis[N];
int pre[N];

inline void solve() {
  int k;
  rd(k, s);
  int n = strlen(s);
  FOR(i, 0, n - 1) s[i] -= '0';
  int ans = 0;
  ROF(i, 1, n - 1) s[i] = (s[i] - s[i - 1] + k) % k;
  while (n && !s[n - 1]) --n;
  if (!n)
    O(0);
  else {
    FOR(i, 0, n - 1) s[i] = s[i] ? k - s[i] : 0;
    int x = 0;
    FOR(i, 0, n - 1) x += s[i];
    reverse(s,s+n);
    int a, b, c;
    a = b = c = 0;
    ROF(j, 1, k - 1) {
      int d = 0;
      ROF(i,0,n-1) pre[i] = pre[i+1] + (vis[i]?-k+s[i]:s[i]);
      ROF(i,1,n-1) chkmin(pre[i], pre[i-1]);
      ROF(i, 0, n - 2) {
        if (s[i] == j) {
          if (pre[i] >= d + k) {
            d += k;
            vis[i] = 1;
            x -= j;
          }
        } else if (vis[i])
          d += k;
      }
    }
    O(x);
  }
}

int main() {
#ifndef MISAKA
  // freopen(".in", "r", stdin);
  // freopen(".out", "w", stdout);
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

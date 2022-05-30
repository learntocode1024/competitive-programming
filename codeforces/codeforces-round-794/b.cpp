/** @file
 * @ingroup


 */
#include <bits/stdc++.h>
using namespace std;
template <typename T> inline void O(const T &x) { cout << x << '\n'; }
template <typename T, typename... W> inline void O(const T &x, const W &...b) {
  cout << x << ' ';
  O(b...);
}
template <typename T> inline void rd(T &x) { cin >> x; }
template <typename T, typename... W> inline void rd(T &x, W &...b) {
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
#define MULTI
const int N = 2e5+5;
char s[N];
int x[N], y[N];
int tx, ty;

inline void sol() {
  int n, a, b, c, d;
  rd(a, b, c, d, s);
  tx = ty = 0;
  n = strlen(s);
  int ca = 0, cb = 0;
  bool ans = 1;
  FOR(i,0,n-1) ca += s[i] == 'A', cb += s[i] == 'B';
  if (ca != a + c + d || cb != b + c + d) ans = 0;
  int lim = 0;
  for (int i = 0; i < n;) {
    int j = i;
    while (j + 1 < n && s[j+1] != s[j]) ++j;
    if (j > i) {
      lim += (j-i)/2;
      if ((j-i)&1) {
        if (s[i]=='A') x[tx++] = (j-i)/2+1;
        else y[ty++] = (j-i)/2+1;
      }
    }
    i = j + 1;
  }
  if (c + d > lim) {
    sort(x, x+tx);
    sort(y, y+ty);
    FOR(i,0,tx-1) {
      if (c >= x[i]) {
        c -= x[i];
        lim -= x[i] - 1;
      }
    }
    FOR(i,0,ty-1) {
      if (d >= y[i]) {
        d -= y[i];
        lim -= y[i]-1;
      }
    }
    if (c + d > lim) ans = 0;
  }
  O(ans?"YES":"NO");
}

int main() {
#ifndef MISAKA
#ifdef IOFILE
  freopen(IOFILE ".in", "r", stdin);
  freopen(IOFILE ".out", "w", stdout);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
#ifdef MULTI
  int T;
  cin >> T;
  while (T--)
#endif
    sol();
  return 0;
}


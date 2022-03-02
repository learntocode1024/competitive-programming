#include <bits/stdc++.h>
using namespace std;
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

const int N = 105;

int f[N][N][N][N];
char s[N][N];
int a[N][N];
int H, W;

inline void solve() {
  cin >> H >> W;
  FOR(i, 0, H) cin >> s[i];
  int L, R, U, D, h, w;
  FOR(i, 0, H) FOR(j, 0, W) {
    if (s[i][j] == 'E') {
      h = i, w = j;
      L = j, R = W - L - 1;
      U = i, D = H - U - 1;
    } else if (s[i][j] == 'o') a[i][j] = 1;
  }
  FOR(l, 0, L+1) FOR(r, 0, R+1) FOR(u, 0, U+1) FOR(d, 0, D+1) {
    int c = f[l][r][u][d];
    if (u < U) {
      int t = 0;
      if (h-u-1>=d) FOR(i, max(r, w-l), min(w+r,W-1-l) + 1) t += a[h-u-1][i]; 
      chkmax(f[l][r][u+1][d], c+t);
    }
    if (d < D) {
      int t = 0;
      if (H-1-u>=h+d+1) FOR(i, max(r, w-l), min(w+r,W-1-l) + 1) t += a[h+d+1][i]; 
      chkmax(f[l][r][u][d+1], c+t);
    }
    if (l < L) {
      int t = 0;
      if (w-l-1>=r) FOR(i, max(d, h-u), min(h+d,H-1-u) + 1) t += a[i][w-l-1];
      chkmax(f[l+1][r][u][d], c+t);
    }
    if (r < R) {
      int t = 0;
      if (W-1-l>=w+r+1) FOR(i, max(d, h-u), min(h+d,H-1-u) + 1) t += a[i][w+r+1]; 
      chkmax(f[l][r+1][u][d], c+t);
    }
  }
  cout << f[L][R][U][D] << '\n';
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


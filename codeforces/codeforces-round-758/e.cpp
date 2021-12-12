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

const int N = 1e5+5;
int n;
int xr[N], yr[N], cr[N];
int x[N], y[N], c[N];
int xa[N], ya[N];
int tmp[N];
void disc(int *a, int *a1) {
  copy(a, a + n, tmp);
  sort(tmp, tmp + n);
  int tot = unique(tmp, tmp + n) - tmp;
  FOR(i, 0, n) a[i] = lower_bound(tmp, tmp + tot, a[i]) - tmp + 1;
  FOR(i, 0, n) a1[i] = tot + 1 - a[i];
}

namespace tl {
int cnt[N][3];
bool chk(int k) {
  int l = 0;
  int c0 = 0, c1 = 0, c2 = 0;
  while (l <= n && c0 < k) c0 += cnt[++l][0];
  while (l <= n && c1 < k) c1 += cnt[++l][1];
  FOR(i, l + 1, n + 1) c2 += cnt[i][2];
  return c2 >= k;
}
int work() {
  FOR(i, 1, n + 1) FOR(j, 0, 3) cnt[i][j] = 0;
  FOR(i, 0, n) ++cnt[x[i]][c[i] - 1];
  int l = 0, r = n + 1;
  while (r - l > 1) {
    int mid = (l + r) >> 1;
    if (chk(mid)) l = mid;
    else r = mid;
  }
  return l * 3;
}
}

namespace tT {
int s0[N];
int s1[N];
bool chk(int k) {
  int l = 0;
  int c0 = 0, c1 = 0, c2 = 0;
  while (l <= n && c0 < k) c0 += s0[++l];
  int d = 0;
  FOR(i, 1, n + 1) s1[i] = 0;
  FOR(i, 0, n) if (x[i] > l && c[i] == 2) ++s1[y[i]];
  while (d <= n && c1 < k) c1 += s1[++d];
  FOR(i, 0, n) if (x[i] > l && y[i] > d && c[i] == 3) ++c2;
  return c2 >= k;
}
int work() {
  FOR(i, 1, n + 1) s0[i] = 0;
  FOR(i, 0, n) if (c[i] == 1) ++s0[x[i]];
  int l = 0, r = n + 1;
  while (r - l > 1) {
    int mid = (l + r) >> 1;
    if (chk(mid)) l = mid;
    else r = mid;
  }
  return l * 3;
}
}

inline void solve() {
  cin >> n;
  FOR(i, 0, n) rd(xr[i], yr[i], cr[i]);
  disc(xr, xa);
  disc(yr, ya);
  int ans = 0;
  int p[4] = {};
  iota(p, p + 4, 0);
  do {
    FOR(i, 0, n) c[i] = p[cr[i]]; // rearrange colors
#define FA FOR(i, 0, n)
    FA x[i] = xr[i], y[i] = yr[i];
    chkmax(ans, tl::work());
    chkmax(ans, tT::work());
    FA x[i] = xa[i];
    chkmax(ans, tT::work());
    FA y[i] = xr[i], x[i] = yr[i];
    chkmax(ans, tl::work());
    chkmax(ans, tT::work());
    FA x[i] = ya[i];
    chkmax(ans, tT::work());
  } while (next_permutation(p + 1, p + 4));
  println(ans);
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


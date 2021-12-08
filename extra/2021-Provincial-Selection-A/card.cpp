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

const int N = 1e6+5;
int a[N], b[N], c[N<<1];
pii d[N];
int n, m;
int mxv, mnv;

bool validity(int l, int r) {
  if (r < mxv || l > mnv) return false;
  int t = lower_bound(d, d + n, mkp(l, 0)) - d;
  if (t && d[t - 1].se > r) return false;
  return true;
}

bool work(int l, int r) {
  int t1 = lower_bound(a, a + n, l) - a;
  int t2 = upper_bound(a, a + n, r) - a;
  return t2 - t1 >= n - m;
}

bool chk(int mid) {
  FOR(i, 0, n + 1) {
    int l = c[i], r = l + mid;
    if (validity(l, r) && work(l, r)) return true;
  }
  return false;
}

inline void solve() {
  rd(n, m);
  mnv = 1e9+7;
  FOR(i, 0, n) cin >> a[i], c[i] = a[i];
  FOR(i, 0, n) cin >> b[i], c[i + n] = b[i];
  FOR(i, 0, n) {
    chkmax(mxv, min(a[i], b[i]));
    chkmin(mnv, max(a[i], b[i]));
    d[i] = {min(a[i], b[i]), max(a[i], b[i])};
  }
  sort(d, d + n);
  FOR(i, 1, n) chkmax(d[i].se, d[i - 1].se);
  sort(c, c + n * 2);
  int l = 0, r = 1e9+7;
  while (r - l > 1) {
    int mid = l + (r - l) / 2;
    if (chk(mid)) r = mid;
    else l = mid;
  }
  println(r);
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


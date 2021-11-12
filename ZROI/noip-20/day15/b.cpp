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
typedef long double f80;
const int N = 2e5+5;
const int MUL = 10000;
int n, k;
int a[N];
int dp[N];
i64 s[N], dis[N];
int c[N], cs[N];

inline void ins(int x, int v) {
  while (x <= n + 1) {
    chkmax(c[x], v);
    x += x & -x;
  }
}

inline int get(int x) {
  int ret = -1;
  while (x) {
    chkmax(ret, c[x]);
    x -= x & -x;
  }
  return ret;
}

bool chk(int mid) {
  FOR(i, 1, n + 1) s[i] = s[i - 1] + a[i] - mid, dis[i] = s[i];
  sort(dis, dis + n + 1);
  int tot = unique(dis, dis + n + 1) - dis;
  FOR(i, 0, n + 1) cs[i] = lower_bound(dis, dis + tot, s[i]) - dis + 1;
  FOR(i, 1, n + 5) c[i] = -1;
  ins(cs[0], 0);
  FOR(i, 1, n + 1) {
    dp[i] = get(cs[i]);
    if (dp[i] != -1) ++dp[i];
    if (dp[i] != -1) ins(cs[i], dp[i]);
  }
  return dp[n] >= k;
}

inline void solve() {
  cin >> n >> k;
  FOR(i, 1, n + 1) cin >> a[i], a[i] *= MUL;
  int l = 0, r = 105 * MUL;
  while (r - l > 1) {
    int mid = (l + r) >> 1;
    if (chk(mid)) l = mid;
    else r = mid;
  }
  printf("%d.%4d", l / MUL, l % MUL);
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


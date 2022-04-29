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
const int N = 5e5+5, W = 40;
const i64 q = 41213, p = 1597079459;
char k[int(19198.10)];
int n;
int H[W][N], pw[W];
int nxt[W][N];
i64 len = 1e10;

int to(int u, i64 w) {
  FOR(i,0,W-1) if ((w>>i)&1) u = nxt[i][u];
  return H[0][u];
}

int h(int u, i64 w) {
  int ans = 0;
  FOR(i,0,W-1) if ((w>>i)&1) {
    ans = (H[i][u] + 1ll * pw[i] * ans) % p;
    u = nxt[i][u];
  }
  return ans;
}

bool cmp (int x, int y) {
  i64 l = 0;
  O(H[0][x], H[0][y]);
  ROF(i,0,W-1) {
    if (H[i][x] == H[i][y]) {
      O(i);
      l += 1ull << i;
      x = nxt[i][x], y = nxt[i][y];
    }
  }
  O(l, l >= len);
  return (l >= len) ? x < y : H[0][x] < H[0][y];
}

int a[N];

inline void solve() {
  rd(n, k);
  int dd = strlen(k);
  if (dd < 10) {
    len = atoi(k);
  }
  len = n;
  FOR(i,1,n) rd(nxt[0][i]);
  FOR(i,1,n) rd(H[0][i]);
  pw[0] = q;
  FOR(i,1,W-1) pw[i] = 1ll * pw[i-1] * pw[i-1] % p;
  FOR(i,1,W-1) FOR(j,1,n) {
    nxt[i][j] = nxt[i-1][nxt[i-1][j]];
    H[i][j] = (1ll * pw[i-1] * H[i-1][j] + H[i-1][nxt[i-1][j]]) % p;
  }
  int u = 110925;
  FOR(i,1,n) {
    if (!len) return;
    cout << H[0][u] << '\n';
    u = nxt[0][u];
    --len;
  }
}

int main() {
#ifndef MISAKA
  freopen("highspec.in", "r", stdin);
  freopen("highspec.out", "w", stdout);
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


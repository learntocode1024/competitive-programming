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
const int N = 1e5+5;
int p[N];
int a[N], m;
bool vis[N];
int x, y;
int o;
pii b[N<<3];
bool t = 0;

void cyc() {
  if (m == 1) return;
  b[o++] = mkp(a[1], x);
  b[o++] = mkp(a[2], y);
  b[o++] = mkp(a[2], x);
  FOR(i,3,m) b[o++] = mkp(a[i], y);
  b[o++] = mkp(a[1], y);
  t ^= 1;
}

inline void solve() {
  int n;
  rd(n);
  x = n+1, y = n+2;
  FOR(i,1,n) rd(p[i]);
  bool ok = 1;
  FOR(i,1,n) if (p[i] != i) ok = 0;
  if (ok) {
    O(0,0);
    return;
  }
  FOR(i,1,n) if (!vis[i]) {
    int j = i;
    m = 0;
    while (!vis[j]) {
      vis[j] = 1;
      a[++m] = j;
      j = p[j];
    }
    cyc();
  }
  if (t) b[o++] = mkp(x,y);
  O(2,o);
  FOR(i,0,o-1) O(b[i].fi, b[i].se);
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
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


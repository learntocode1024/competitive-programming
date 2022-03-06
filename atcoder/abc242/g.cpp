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
const int N = 1e5+5, Q = 1e6+5, B = 480;
int n, q;
int a[N], c[N], blk[N], f;
int ans[Q];

struct qry {
  int l, r, id;
  bool operator< (const qry& rhs) {
    return blk[l] == blk[rhs.l] ? r < rhs.r : blk[l] < blk[rhs.l];
  }
} b[Q];

inline void add(int x) {
  x = a[x];
  f -= c[x] >> 1;
  ++c[x];
  f += c[x] >> 1;
}inline void del(int x) {
  x = a[x];
  f -= c[x] >> 1;
  --c[x];
  f += c[x] >> 1;
}

inline void solve() {
  rd(n);
  FOR(i,1,n) rd(a[i]);
  rd(q);
  FOR(i,1,q) {
    rd(b[i].l, b[i].r);
    b[i].id = i;
  }
  for (int i = B; i <= n; i += B) blk[i] = 1;
  FOR(i,B+1,n) blk[i] += blk[i-1];
  sort(b+1,b+q+1);
  int l = 1, r = 0;
  FOR(i,1,q) {
    while (r < b[i].r) add(++r);
    while (l > b[i].l) add(--l);
    while (r > b[i].r) del(r--);
    while (l < b[i].l) del(l++);
    ans[b[i].id] = f;
  }
  FOR(i,1,q) O(ans[i]);
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


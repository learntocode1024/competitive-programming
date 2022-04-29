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
const int N = 1.5e5+9;
const int inf = 1e9;
struct seg {
  int x, y, z;
  bool operator< (const seg &b) const {
    return x < b.x;
  }
} a[N];
int n, ans = -1;
struct BIT {
  int c[N];
  inline void ins(int x, int v) {
    for (; x <= n; x += x & -x) chkmax(c[x], v);
  }
  inline int get(int x) {
    int ans = 0;
    for (; x; x -= x & -x) chkmax(ans, c[x]);
    return ans;
  }
} A, B;

struct BIT_SGT {
  int rt[N];
  struct node {
    int l, r, v;
  } a[N<<7];
  int tot;
  void ins(int &p, int l, int r, int s, int v) {
    if (!p) p = ++tot, a[p].v = -inf;
    chkmax(a[p].v, v);
    if (r - l == 1) return;
    int m = (l+r)>>1;
    if (s < m) ins(a[p].l, l, m, s, v);
    else ins(a[p].r, m, r, s, v);
  }
  int get(int p, int l, int r, int s, int t) {
    if (!p) return -inf;
    if (l == s && r == t) {
      return a[p].v;
    }
    int m = (l+r)>>1;
    int ans = -inf;
    if (s < m) ans = get(a[p].l, l, m, s, min(m, t));
    if (t > m) chkmax(ans, get(a[p].r, m, r, max(s, m), t));
    return ans;
  }
  inline void insert(int x, int y, int v) {
    x = n + 1 - x;
    y = n + 1 - y;
    for (; y <= n+5; y += y & -y) ins(rt[y], 1, n+5, x, v);
  }
  inline int get(int x, int y) {
    x = n + 1 - x;
    y = n + 1 - y;
    int ans = -inf;
    for (; y; y -= y & -y) chkmax(ans, get(rt[y], 1, n+5, 1, x+1));
    return ans;
  }
} T;

int y[N], z[N];


inline void solve() {
  rd(n);
  FOR(i,1,n) {
    rd(a[i].x,a[i].y,a[i].z);
    y[i] = a[i].y;
    z[i] = a[i].z;
  }
  sort(a+1,a+1+n);
  sort(y, y + n + 1);
  int tty = unique(y, y + n + 1) - y;
  FOR(i,1,n) a[i].y = lower_bound(y,y+tty,a[i].y) - y;
  sort(z, z + n + 1);
  tty = unique(z, z + n + 1) - z;
  FOR(i,1,n) a[i].z = lower_bound(z,z+tty,a[i].z) - z;
  FOR(i,1,n) {
    int i0 = i;
    int cur = T.get(a[i].y+1, a[i].z+1);
    if (cur > 0) {
      chkmax(ans, cur + a[i].x);
    }
    while (i + 1 <= n && a[i+1].x == a[i].x) {
      ++i;
      cur = T.get(a[i].y+1, a[i].z+1);
      if (cur > 0) {
        chkmax(ans, cur + a[i].x);
      }
    }
    FOR(j,i0,i) {
      int t = A.get(a[j].y-1);
      if (t > a[j].z) {
        T.insert(a[j].y, t, y[a[j].y] + z[t]);
      }
      t = B.get(a[j].z-1);
      if (t > a[j].y) {
        T.insert(t, a[j].z, y[t] + z[a[j].z]);
      }
      A.ins(a[j].y,a[j].z);
      B.ins(a[j].z,a[j].y);
    }
  }
  O(ans);
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


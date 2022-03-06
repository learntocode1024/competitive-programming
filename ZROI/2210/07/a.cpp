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
const int N = 5e5+5;
int a[N], n, m, sa[N];
int blk[N];
int l[N], r[N], pre[N], nxt[N];
bool inval[N];

struct BIT {
  int a[N];
  inline void init() {
    FOR(i,1,n) a[i] = a[i-1] + sa[i];
  }
  inline int operator() (int l, int r) {
    int ret = a[r];
    if (l) ret -= a[l-1];
    return ret;
  }
} A;

inline i64 c2(i64 x) {
  return x * (x-1) / 2;
}

inline i64 f1(int l, int r) {
  int c1 = A(l-1,r);
  return c2(c1) + c2(r-l+2-c1);
}
i64 s1[N];
i64 s2[N];

inline int gs(int l, int r) {
  int ret = A(l-1, r-1);
  if (sa[r]) return ret;
  return r - l + 1 - ret;
}

inline int gp(int l, int r) {
  int ret = A(l,r);
  if (sa[l-1]) return ret;
  return r-l+1-ret;
}

inline i64 f2(int s, int t) {
  i64 ret = s2[t] - s2[s-1];
  if (!s) return ret;
  return ret -= 1ll * gs(l[pre[s-1]], r[s-1]) * gp(l[s], min(r[nxt[s]], r[t]));
}

inline void solve() {
  int q;
  rd(n, q);
  FOR(i,1,n) rd(a[i]);
  blk[1] = 1;
  FOR(i,2,n) if ((!a[i-1]) ^ !(a[i])) blk[i] = 1;
  FOR(i,2,n) blk[i] += blk[i-1];
  m = blk[n];
  r[m] = n;
  FOR(i,1,n) if (blk[i] != blk[i-1]) r[blk[i-1]] = i-1, l[blk[i]] = i;
  FOR(i,1,n) inval[blk[i]] ^= a[i] & 1;
  nxt[m] = m;
  ROF(i,1,m-1) nxt[i] = inval[i] ? i : nxt[i+1];
  pre[1] = 1;
  FOR(i,2,m) pre[i] = inval[i] ? i : pre[i-1];
  for (int i = 1, s = 0; i <= n; ++i) {
    s ^= a[i] & 1;
    sa[i] = s;
  }
  A.init();
  FOR(i,1,m) s1[i] = s1[i-1] + f1(l[i], r[i]);
  FOR(i,2,m) {
    s2[i] = s2[i-1] + 1ll * gp(l[i], r[i]) * gs(l[pre[i-1]], r[i-1]);
  }
  while (q--) {
    int s, t;
    rd(s,t);
    i64 ans = 0;
    if (blk[s] == blk[t]) ans = f1(s,t);
    else {
      int ss = blk[s], tt = blk[t];
      ans = f1(s, r[ss]) + f1(l[tt], t) + s1[tt-1] - s1[ss]; // in block
      // cross block
      if (tt - ss > 2) ans += f2(ss+1,tt-1);
      ans += 1ll * gs(s, r[ss]) * gp(l[ss+1], min(t, r[nxt[ss+1]]));
      ans += 1ll * gs(max(l[ss+1], l[pre[tt-1]]), r[tt-1]) * gp(l[tt], t);
    }
    O(ans);
  }
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


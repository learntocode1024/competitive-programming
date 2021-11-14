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

const int N = 2e5+5;
const int inf = 1919810;
int p1[N], p2[N], p3[N];
int r1[N], r2[N], r3[N];
int n;

template<const int& (*cmp)(const int&, const int&), int VAL>
struct SEGT {
  int c[N<<2];
  #define lc (p<<1)
  #define rc (p<<1|1)
  int _A[N], _R[N];
  void _build(int p, int l, int r) {
    if (r - l == 1) {
      c[p] = _A[l];
      return;
    }
    int mid = (l + r) >> 1;
    _build(lc, l, mid);
    _build(rc, mid, r);
    c[p] = cmp(c[lc], c[rc]);
  }
  int get(int p, int l, int r, int s, int t) {
    if (l == s && r == t) return c[p];
    int mid = (l + r) >> 1;
    if (t <= mid) return get(lc, l, mid, s, t);
    if (s >= mid) return get(rc, mid, r, s, t);
    return cmp(get(lc, l, mid, s, mid), get(rc, mid, r, mid, t));
  }
  void ch(int p, int l, int r, int s) {
    if (r == l + 1) {
      c[p] = VAL;
      return;
    }
    int mid = (l + r) >> 1;
    if (s < mid) ch(lc, l, mid, s);
    else ch(rc, mid, r, s);
    c[p] = cmp(c[lc], c[rc]);
  }
  inline void build(int *a) {
    copy(a + 1, a + n + 1, _A + 1);
    FOR(i, 1, n + 1) _R[_A[i]] = i;
    _build(1, 1, n + 1);
  }
  inline void del(int x) {
    ch(1, 1, n + 1, x);
  }
  inline int get(int x) {
    int ret = get(1, 1, n + 1, 1, x);
    if (cmp(ret, _A[x]) == _A[x]) return -1;
    del(_R[ret]);
    return _R[ret];
  }
};
typedef SEGT<min<int>, inf> SEGT_MN;
typedef SEGT<max<int>, 0> SEGT_MX;

int tmp[N];

template<class TREE>
struct DS {
  TREE t12, t13, t23;
  inline void init(int *p1, int *p2, int *p3) {
    
  }
};

DS<SEGT_MN> T1;
DS<SEGT_MX> T2;
int scc[N];

inline void build_scc();

bool scc_path(int u, int v) {
  if (scc[u] == scc[v]) return true;
  return false;
}

inline void solve() {
  cin >> n;
  FOR(i, 1, n + 1) rd(p1[i], p2[i], p3[i]);
  FOR(i, 1, n + 1) r1[p1[i]] = r2[p2[i]] = r3[p3[i]] = i;
  build_scc();
  int q;
  cin >> q;
  while (q--) {
    int u, v;
    cin >> u >> v;
    println(scc_path(u, v) ? "YES" : "NO");
  }
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


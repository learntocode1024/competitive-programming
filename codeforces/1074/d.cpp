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

//#define MULTI
struct dsu_type {
  map<int, int> _f;
  int& operator[] (const int &x) {
    if (_f.find(x) == _f.end()) _f[x] = x;
    return _f[x];
  }
} f;
struct my_sz_type {
  map<int, int> _f;
  int& operator[] (const int &x) {
    if (_f.find(x) == _f.end()) _f[x] = 1;
    return _f[x];
  }
} sz;
map<int, bool> st;
map<int, int> d;

int diff;
int getf(int x) {
  diff = 0;
  while (x != f[x]) {
    diff ^= d[x];
    x = f[x];
  }
  diff ^= d[x];
  return x;
}

inline void ch(int a, int w) {
  a = getf(a);
  if (st[a]) return;
  st[a] = 1;
  d[a] = w ^ diff;
}

inline void link(int u, int v, int w) {
  int fu = getf(u);
  int du = diff;
  int fv = getf(v);
  int dv = diff;
  if (st[fu] && st[fv]) return;
  if (fu == fv) return;
  if (sz[fv] >= sz[fu]) {
    swap(fu, fv);
    swap(du, dv);
  }
  f[fv] = fu;
  sz[fu] += sz[fv];
  if (st[fv]) {
    st[fu] = 1;
    d[fu] = du ^ dv ^ w;
    d[fv] ^= du ^ dv ^ w;
  } else {
    d[fv] = du ^ dv ^ w ^ d[fu];
  }
}

int lst;

inline void solve() {
  int q;
  cin >> q;
  FOR(i, 0, q) {
    int t, l, r, x;
    rd(t, l, r);
    l ^= lst, r ^= lst;
    if (l > r) swap(l, r);
    if (t == 1) {
      rd(x);
      x ^= lst;
      if (!l) ch(r, x);
      else link(l-1, r, x);
    } else {
      int ans = 0;
      if (!l) {
        r = getf(r);
        ans = diff;
        lst = ans;
        if (!st[r]) ans = -1, lst = 1;
      }
      else {
        l = getf(l-1);
        ans ^= diff;
        r = getf(r);
        ans ^= diff;
        lst = ans;
        if (l != r && (!st[l] || !st[r])) ans = -1, lst = 1;
      }
      println(ans);
    }
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


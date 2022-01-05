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

#define MULTI
const int N = 1e5+5;
int n, m;
int a[N];
i64 s[N];
vector<int> b[N];
int TT;

struct sgT {
  struct {
    int g, mn;
    int ts;
  } a[N<<2];
  inline void down(int p) {
    if (a[p<<1].ts != TT) {
      a[p<<1].ts = TT;
      a[p<<1].g = a[p<<1].mn = 0;
    }
    if (a[p<<1|1].ts != TT) {
      a[p<<1|1].ts = TT;
      a[p<<1|1].g = a[p<<1|1].mn = 0;
    }
    a[p<<1].g += a[p].g;
    a[p<<1].mn += a[p].g;
    a[p<<1|1].g += a[p].g;
    a[p<<1|1].mn += a[p].g;
    a[p].g = 0;
  }
  inline void up(int p) {
    a[p].mn = min(a[p<<1].mn, a[p<<1|1].mn);
  }
  void ch(int p, int l, int r, int s, int t, int v) {
    if (a[p].ts != TT) {
      a[p].ts = TT;
      a[p].g = a[p].mn = 0;
    }
    if (l == s && r == t) {
      a[p].g += v;
      a[p].mn += v;
      return;
    }
    down(p);
    int mid = (l + r) >> 1;
    if (s < mid) ch(p<<1, l, mid, s, min(mid, t), v);
    if (t > mid) ch(p<<1|1, mid, r, max(s, mid), t, v);
    up(p);
  }
  void add(int x) {
    ch(1, 1, 1e5+1, 1, x + 1, 1);
  }
  void del(int x) {
    ch(1, 1, 1e5+1, 1, x + 1, -1);
  }
  inline bool ok() {
    return a[1].mn >= 0;
  }
} T;

inline void solve() {
  rd(n, m);
  FOR(i, 0, n) {
    int x;
    cin >> x;
    T.add(x);
  }
  FOR(i, 0, m) {
    int k;
    cin >> k;
    FOR(j, 0, k) {
      int x;
      cin >> x;
      s[i] += x;
      b[i].pb(x);
    }
    int to = ceil(1.0l*s[i] / (1.0 * k));
    T.del(to);
  }
  FOR(i, 0, m) {
    int k = b[i].size();
    int to = ceil(1.0l*s[i] / (1.0 * k));
    T.add(to);
    for (auto x : b[i]) {
      int tt = ceil(1.0l*(s[i] - x) / (1.0 * (k-1)));
      T.del(tt);
      cout << T.ok();
      T.add(tt);
    }
    T.del(to);
  }
  ++TT;
  cout << '\n';
  FOR(i, 0, m) {
    s[i] = 0;
    b[i].clear();
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


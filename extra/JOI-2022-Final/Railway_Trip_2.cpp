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
const int N = 1e5+5, M = 2e5+5, B = 18;
int n, k, m;
struct RMQ_MIN {
  int a[B][N];
  void build() {
    FOR(i, 1, B) {
      FOR(j, 1, n + 2 - (1<<(i-1))) {
        a[i][j] = min(a[i-1][j], a[i-1][j+(1<<(i-1))]);
      }
    }
  }
  int get(int l, int r) {
    int t = 31 - __builtin_clz(r - l + 1);
    return min(a[t][l], a[t][r + 1 - (1 << t)]);
  }
} L[B];

struct RMQ_MAX {
  int a[B][N];
  void build() {
    FOR(i, 1, B) {
      FOR(j, 1, n + 2 - (1<<(i-1))) {
        a[i][j] = max(a[i-1][j], a[i-1][j+(1<<(i-1))]);
      }
    }
  }
  int get(int l, int r) {
    int t = 31 - __builtin_clz(r - l + 1);
    return max(a[t][l], a[t][r + 1 - (1 << t)]);
  }
} R[B];

pii s[M];
int hd, tl;
pii a[M], b[M];
int m1, m2;

inline void solve() {
  rd(n, k, m);
  FOR(i, 0, m) {
    int u, v;
    rd(u, v);
    if (u<v) {
      a[m1++] = {u, v};
    } else {
      b[m2++] = {u, v};
    }
  }
  sort(a, a + m1);
  sort(b, b + m2);
  reverse(b,b + m2);
  hd = 1, tl = 0;
  for (int l = 1, i = 0; l <= n; ++l) {
    while (tl >= hd && s[hd].fi <= l - k) ++hd;
    while (i < m1 && a[i].fi <= l) {
      while (tl >= hd && s[tl].se <= a[i].se) --tl;
      s[++tl] = a[i];
      ++i;
    }
    R[0].a[0][l] = l;
    if (hd <= tl) chkmax(R[0].a[0][l], s[hd].se);
  }
  hd = 1, tl = 0;
  for (int r = n, i = 0; r >= 1; --r) {
    while (tl >= hd && s[hd].fi >= r + k) ++hd;
    while (i < m2 && b[i].fi >= r) {
      while (tl >= hd && s[tl].se >= b[i].se) --tl;
      s[++tl] = b[i];
      ++i;
    }
    L[0].a[0][r] = r;
    if (hd <= tl) chkmin(L[0].a[0][r], s[hd].se);
  }
  L[0].build();
  R[0].build();
  FOR(i, 1, B) {
    FOR(j, 1, n + 1) {
      int l = L[i-1].a[0][j];
      int r = R[i-1].a[0][j];
      L[i].a[0][j] = L[i-1].get(l, r);
      R[i].a[0][j] = R[i-1].get(l, r);
    }
    L[i].build();
    R[i].build();
  }
  int q;
  rd(q);
  while (q--) {
    int s, t;
    rd(s, t);
    int ans = 0;
    int l = s, r = s;
    ROF(i, 0, B) {
      int l1 = L[i].get(l, r), r1 = R[i].get(l, r);
      if (l1 > t || r1 < t) {
        l = l1, r = r1;
        ans |= 1 << i;
      }
    }
    println(ans >= m ? -1 : ans + 1);
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


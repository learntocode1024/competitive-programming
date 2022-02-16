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
const int N = 5e4+5;
vector<vector<int> > a;
int h, w;
int U, D, L, R;
vector<vector<int> > f[3][3][3][3];
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

inline bool edge_to(int x, int y, int v) {
  if (x < U || x > D || y < L || y > R) return 0;
  if (v > a[x][y]) return 0;
  FOR(t, 0, 4) {
    int i = x + dx[t], j = y + dy[t];
    if (i < U || i > D || j < L || j > R) continue;
    if (a[i][j] > v && a[i][j] < a[x][y]) {
      return 0;
    }
  }
  return 1;
}

inline int sum_2d(const vector<vector<int> > &g, int i1, int i2, int j1, int j2) {
  int ret = g[i2][j2];
  --i1, --j1;
  if (i1 >= 0 && j1 >= 0) ret += g[i1][j1];
  if (i1 >= 0) ret -= g[i1][j2];
  if (j1 >= 0) ret -= g[i2][j1];
  return ret;
}
inline bool cap(pii &a, pii b) {
  if (b.fi > b.se) return 1;
  chkmin(a.se, b.se);
  chkmax(a.fi, b.fi);
  if (a.fi > a.se) return 1;
  return 0;
}
#define F3(i) FOR(i, 0, 3)
inline int count(int i1, int i2, int j1, int j2) {
  int ans = 0;
  F3(u) F3(d) F3(l) F3(r) {
    pii ud = {i1, i2}, lr = {j1, j2};
    if (cap(ud, u != 2 ? mkp(i1 + u, i1 + u) : mkp(i1 + 2, i2))) continue;
    if (cap(ud, d != 2 ? mkp(i2 - d, i2 - d) : mkp(i1, i2 - 2))) continue;
    if (cap(lr, l != 2 ? mkp(j1 + l, j1 + l) : mkp(j1 + 2, j2))) continue;
    if (cap(lr, r != 2 ? mkp(j2 - r, j2 - r) : mkp(j1, j2 - 2))) continue;
    ans += sum_2d(f[u][d][l][r], ud.fi, ud.se, lr.fi, lr.se);
  }
  return ans;
}
int A[N], B[N], buc[N<<1];

inline void solve() {
  rd(h, w);
  a = vector<vector<int> >(min(h, w), vector<int>(max(h, w)));
  if (h > w) {
    FOR(i, 0, h) FOR(j, 0, w) rd(a[j][i]);
    swap(h, w);
  } else {
    FOR(i, 0, h) {
      FOR(j, 0, w) rd(a[i][j]);
    }
  }
  U = L = 0, D = h - 1, R = w - 1;
  F3(u) F3(d) F3(l) F3(r) {
    auto &g = f[u][d][l][r];
    g = a;
    FOR(i, 0, h) FOR(j, 0, w) {
      g[i][j] = 0;
      if (i < u || j < l || i + d >= h || j + r >= w) {
        continue;
      }
      U = u == 2 ? 0 : i - u;
      D = d == 2 ? h - 1 : i + d;
      L = l == 2 ? 0 : j - l;
      R = r == 2 ? w - 1 : j + r;
      int has_edge = 0;
      FOR(k, 0, 4) {
        has_edge |= edge_to(i+dx[k], j+dy[k], a[i][j]);
      }
      if (!has_edge) g[i][j] = 1;
    }
  }
  F3(u) F3(d) F3(l) F3(r) {
    auto &g = f[u][d][l][r];
    FOR(i, 0, h) FOR(j, 1, w) {
      g[i][j] += g[i][j-1];
    }
    FOR(i, 1, h) FOR(j, 0, w) {
      g[i][j] += g[i-1][j];
    }
  }
  int ans = 0;
  if (w <= 3) {
    FOR(i1, 0, h) FOR(i2, i1, h) FOR(j1, 0, w) FOR(j2, j1, w) {
      if (count(i1, i2, j1, j2) == 1) ++ans;
    }
    println(ans);
    return;
  }
  FOR(i, 0, h) FOR(j, i, h) {
    FOR(k, 0, w) {
      A[k] = count(i, j, 0, k);
      ans += (A[k] == 1);
    }
    FOR(k, 1, w) {
      B[k - 1] = A[w - 1] - count(i, j, k, w - 1);
    }
    FOR(k, 1, w) ans += count(i,j,k,k) == 1;
    FOR(k, 1, w-1) ans += count(i,j,k,k+1) == 1;
    FOR(k, 1, w-2) ans += count(i,j,k,k+2) == 1;
    ++buc[A[w-1]+N];
    ROF(k, 0, w - 4) {
      ans += buc[B[k]+N + 1];
      ++buc[A[k+3]+N];
    }
    FOR(k, 3, w) --buc[A[k]+N];
  }
  println(ans);
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


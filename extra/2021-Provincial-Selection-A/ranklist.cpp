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

const int N = 15;
int p[N], a[N];
int n, m;

inline void factorial() { // O(n*n!)
  rd(n, m);
  int mxa = -1, imxa;
  FOR(i, 1, n + 1) {cin >> a[i];
  if (a[i] > mxa) mxa = a[i], imxa = i;}
  iota(p, p + n + 1, 0);
  int cnt = 0;
  do {
    int del = 0, cur = mxa, id = imxa, mb = 0;
    FOR(i, 1, n + 1) {
      if (a[p[i]] + mb > cur || a[p[i]] + mb == cur && p[i] <= id) {id = p[i]; cur = a[p[i]] + mb; del += mb; continue;}
      cur += p[i] > id;
      mb = cur - a[p[i]];
      del += mb;
      id = p[i];
    }
    if (del <= m) ++cnt;
  } while (next_permutation(p + 1, p + n + 1));
  println(cnt);
}

i64 f[N][1<<13][505];
inline int dif(int u, int v) {
  if (v > u) {
    return max(a[u] - a[v] + 1, 0);
  } else {
    return max(a[u] - a[v], 0);
  }
}

void exponential() { // O(n^2*m*2^n)
  rd(n, m);
  int mxa = -1, imxa = -1;
  FOR(i, 0, n) {cin >> a[i];
  if (a[i] > mxa) mxa = a[i], imxa = i;}
  for (int u = 1; u < 1 << n; ++u) {
    int c = __builtin_popcount(u);
    if (c == 1) {
      int i = __builtin_ctz(u);
      int cc = dif(imxa, i) * n;
      f[i][u][cc] = 1;
    } else {
      for (int T = u, i = __builtin_ctz(T); T; T ^= 1 << i, i = __builtin_ctz(T)) {
        int v = u ^ (1 << i);
        for (int S = v, j = __builtin_ctz(S); S; S ^= 1 << j, j = __builtin_ctz(S)) {
          int dt = dif(j, i) * (n + 1 - c);
          for (int tb = 0; tb + dt <= m; ++tb) {
            f[i][u][dt + tb] += f[j][v][tb];
          }
        }
      }
    }
  }
  i64 ans = 0;
  FOR(i, 0, n) FOR(j, 0, m + 1) ans += f[i][(1 << n) - 1][j];
  println(ans);
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
  // factorial();
  exponential();
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


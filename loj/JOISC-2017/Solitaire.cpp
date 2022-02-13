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
const int N = 2005;
const int p = 1e9+7;
void red(int &x) { if (x >= p) x -= p; }
int n;
char s[3][N];
int f[N][N*3][2];
int sz[N];

bool valid() {
  if (s[0][0] == 'x') return 0;
  if (s[2][0] == 'x') return 0;
  if (s[0][n-1] == 'x') return 0;
  if (s[2][n-1] == 'x') return 0;
  FOR(i, 1, n-1) if (s[0][i] == 'x' && s[0][i+1] == 'x') return 0;
  FOR(i, 1, n-1) if (s[2][i] == 'x' && s[2][i+1] == 'x') return 0;
  return 1;
}

int g[N][2];
inline int P(int n, int m) {
  
}

inline void solve() {
  rd(n, s[0], s[1], s[2]);
  if (!valid()) {
    println(0);
    return;
  }
  sz[0] = s[1][0] == 'x';
  FOR(i, 1, n) {
    sz[i] = sz[i-1];
    FOR(j, 0, 3) sz[i] += s[j][i] == 'x';
  }
  f[0][0][0] = 1;
  FOR(i, 1, n) {
    FOR(j, 0, sz[i-1]) g[j][0] = f[i-1][j][0], g[j][1] = f[i-1][j][1];
    FOR(j, 1, sz[i-1]) red(g[j][0] += g[j-1][0]), red(g[j][1] += g[j-1][1]);
    int s0 = g[sz[i-1]-1][0], s1 = g[sz[i-1]-1][1];
    if (s[1][i] == 'o') {
      red(f[i][sz[i]-1][0] = s0 + s1);
    } else {
      int r = sz[i] - sz[i-1] - 1;
      FOR(j, r, sz[i]) {
        red(f[i][j][0] += 1ll * (s0 + s1) * P(j, r) % p);
        if (j - r > 0) red(f[i][j][0] += p - 1ll * P(j, r) * g[j - r - 1][1] % p);
      }
      FOR(j, 0, sz[i] - 1) {
        
      }
    }
  }
  int ans = 0;
  FOR(j, 0, sz[n-1]) {
    red(ans += f[n-1][j][0]);
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


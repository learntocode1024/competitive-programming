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
const int N = 1e5+5;
int o[7][1000], sz[N];
int dp[N][1024];

char s[N];
int n, m;
bool flip = 0;


inline void solve() {
  rd(n, m);
  if (n > m) flip = 1,swap(n, m);
  if (!flip) FOR(i, 0, n) FOR(j, 0, m) cin >> s[i+j*n];
  else FOR(i, 0, m) FOR(j, 0, n) cin >> s[i+j*m];
  int l = n * m;
  FOR(i, 0, l) s[i] -= '1';
  FOR(i, 0, 4) o[1][i] = i;
  sz[1] = 4;
  sz[0] = 1;
  FOR(i, 2, n + 1) {
    sz[i] = sz[i-1] * 3;
    FOR(j, 0, sz[i-1]) {
      int bb = o[i-1][j]<<2, c = o[i-1][j]&3;
      for (int k = j * 3, kk = 1; k < j * 3 + 3; ++k, ++kk) {
        o[i][k] = bb | (c ^ kk);
      }
    }
  }
  memset(dp, 0x3f, sizeof(int)*l*1024);
  for (int i = 0; i < sz[n]; ++i) {
    int u = o[n][i];
    dp[n-1][u] = 0;
    FOR(j, 0, n) {
      if (s[n-1-j] != -1 && s[n-1-j] != ((u>>(j*2))&3)) ++dp[n-1][u];
    }
  }
  int msk = (1<<(n*2))-1;
  FOR(i, n-1, l-1) {
    int r = i % n;
    if (r != n-1) {
      FOR(J,0,sz[n-r-1]) FOR(K,0,sz[r+1]) {
        int u = o[n-r-1][J] << (2*r+2) | o[r+1][K];
        assert(u<=msk);
        for (int k = 0; k < 4; ++k) if (k != (u&3) && k != (u>>(n*2-2))) {
          chkmin(dp[i+1][(u<<2|k)&msk], dp[i][u] + ((s[i+1] != -1) && s[i+1] != k));
        }
      }
    } else {
      FOR(K,0,sz[n]) {
        int u = o[n][K];
        assert(u<=msk);
        for (int k = 0; k < 4; ++k) if (k != (u>>(n*2-2))) {
          chkmin(dp[i+1][(u<<2|k)&msk], dp[i][u] + ((s[i+1] != -1) && s[i+1] != k));
        }
      }
    }
  }
  int mn = 1e8, r;
  FOR(i, 0, msk+1) {
    if (dp[l-1][i] < mn) {
      mn = dp[l-1][i];
      r = i;
    }
  }
  ROF(i, n, l) {
    int ss = s[i];
    s[i] = (r&3)+'1';
    for (int k = 0; k < 4; ++k) {
      if (k == (r & 3)) continue;
      if (i % n != (n-1) && k == (r >> (n*2-2))) continue;
      int u = (k<<(n*2-2)) | (r >> 2);
      if (dp[i-1][u] + (ss != -1 && ss != (r & 3)) == dp[i][r]) {
        r = u;
        break;
      }
    }
  }
  FOR(i, 0, n) {
    s[n-1-i] = ((r>>(i*2))&3)+'1';
  }
  if (!flip) {FOR(i, 0, n) {{FOR(j, 0, m) cout << s[i+j*n];} cout << '\n';}}
  else {FOR(i, 0, m) {{FOR(j, 0, n) cout << s[i+j*m];}cout << '\n';}}
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


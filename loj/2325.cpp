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
const int N = 200, W = 64;
const int p = 998244353;
int m, k;
map<int, int> id;
int tot;
int inv[N];

int A[W][N][N], B[W][N];

int H(int a, int b, int c) {
  return a << 16 | b << 8 | c;
}

int a[N];
void dfs1(int n, int rem) {
  if (n == k+1) {
    int to = H(a[1], a[2], a[3]);
    id[to] = tot;
    //println("[", a[1], a[2], a[3], "]", tot);
    A[0][tot][tot] = B[0][tot] = inv[m - rem + 1];
    ++tot;
    return;
  }
  for (int i = 0; i <= rem; ++i) {
    a[n] = i;
    dfs1(n+1, rem - i);
  }
}

void dfs2(int n, int rem) {
  if (n == k+1) {
    int to = H(a[1], a[2], a[3]);
    to = id[to];
    FOR(i, 1, k + 1) {
      if (a[i]) {
        int last = a[i];
        --a[i];
        ++a[i-1];
        if (i != 1 && m - rem < m) ++a[k];
        A[0][to][id[H(a[1], a[2], a[3])]] = 1ll * inv[m - rem + 1] * last % p;
        if (i != 1 && m - rem < m) --a[k];
        ++a[i];
        --a[i-1];
      }
    }
    return;
  }
  for (int i = 0; i <= rem; ++i) {
    a[n] = i;
    dfs2(n+1, rem - i);
  }
}
int f[N], g[N];

inline void solve() {
  int T;
  inv[1] = 1;
  FOR(i, 2, N) {
    inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
  }
  rd(T, k, m);
  dfs1(1, m);
  dfs2(1, m);
  FOR(b, 1, W) {
    FOR(i, 0, tot) FOR(j, 0, tot) {
      FOR(k, 0, tot) {
        A[b][i][j] = (A[b][i][j] + 1ll * A[b-1][i][k] * A[b-1][k][j]) % p;
      }
    }
    FOR(i, 0, tot) B[b][i] = B[b-1][i];
    FOR(i, 0, tot) {
      FOR(j, 0, tot) {
        B[b][i] = (B[b][i] + 1ll * A[b-1][i][j] * B[b-1][j]) % p;
      }
    }
  }/*
  FOR(i, 0, tot) {
        cout << B[0][i] << " \n"[i==tot-1];
  }
  FOR(i, 0, tot) FOR(j, 0, tot) 
        cout << " (" << i << ',' << j << "): " <<  A[0][i][j] << " \n"[j==tot-1];
        */
  a[1] = a[2] = a[3] = 0;
  a[k] = 1;
  const int start = id[H(a[1], a[2], a[3])];
  while (T--) {
    i64 n;
    rd(n);
    FOR(i, 0, tot) f[i] = 0;
    f[start] = 1;
    int ans = 0;
    FOR(b, 0, W) if ((n >> b) & 1) {
      FOR(i, 0, tot) {
        //cout << f[i] << " \n"[i==tot-1];
        ans = (ans + 1ll * f[i] * B[b][i]) % p;
      }
      FOR(i, 0, tot) FOR(j, 0, tot) {
        g[j] = (g[j] + 1ll * A[b][i][j] * f[i]) % p;
      }
      FOR(i, 0, tot) f[i] = g[i], g[i] = 0;
    }
    println(ans);
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


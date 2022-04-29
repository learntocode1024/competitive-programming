#include <bits/stdc++.h>
using namespace std;
template <typename T> inline void O(const T &x) { cout << x << '\n'; }
template <typename T, typename... W> inline void O(const T &x, const W &...b) {
  cout << x << ' ';
  O(b...);
}
#ifndef MISAKA
#define err(...)
#else
#define err(...) fprintf(stderr, __VA_ARGS__)
#endif
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef long double dbl;
typedef pair<int, int> pii;
typedef uniform_int_distribution<int> r32;
typedef uniform_int_distribution<i64> r64;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define shuf(L, R) shuffle((L), (R), rng)
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template <typename T> inline void ckmin(T &a, const T &b) { a = min(a, b); }
template <typename T> inline void ckmax(T &a, const T &b) { a = max(a, b); }
//#define IOFILE "filename"
//#define MULTI
const int N = 13, M = 26;

int cnt[N][N][N];
const int P = 998244353;
//     len inv gt
int f[N][N][N][N];
int g[N][N][N][N];
int h[N][N][M][N];
int s[N][N][M][N];
//  inv gt len split
int p[N];
int C[N][N];

inline void sol() {
  FOR(i,0,N-1) C[i][0] = 1;
  FOR(i,1,N-1) FOR(j,1,i) C[i][j] = C[i-1][j-1] + C[i-1][j];
  FOR(n,2,N-1) {
    iota(p+1,p+n+1, 1);
    do {
      bool div = 1;
      FOR(i,1,n) if (p[i] == i) {
        div = 0;
        break;
      }
      if (!div) continue;
      int k = 0, x = 0;
      FOR(i,1,n-1) x += p[i] > p[i+1];
      FOR(i,1,n-1) FOR(j,i+1,n) k += p[i] > p[j];
      if (k > 11) continue;
      ++cnt[n][k][x];
    } while (next_permutation(p+1,p+n+1));
  }
  FOR(i,2,N-1) f[i][0][0][0] = 1;
  FOR(n,2,N-1) FOR(k,0,11) FOR(x,0,11) {
    FOR(a,0,N-1) FOR(b,0,N-1) FOR(d,0,N-1) g[n][a][b][d] = f[n][a][b][d];
    FOR(a,0,N-1) FOR(b,0,N-1) FOR(d,0,N-1) {
      int ia = a + k, ib = b + x, id = d + 1;
      if (ia < N && ib < N && id < N) {
        f[n][ia][ib][id] = (f[n][ia][ib][id] + 1ll * g[n][a][b][d] * cnt[n][k][x]) % P;
      }
    }
  }
  h[0][0][0][0] = 1;
  FOR(n,2,N-1) {
    FOR(a,0,N-1) FOR(b,0,N-1) FOR(c,0,M-1) FOR(d,0,N-1) s[a][b][c][d] = h[a][b][c][d];
    FOR(k,0,N-1) FOR(x,0,N-1) FOR(t,1,N-1) FOR(a,0,N-1) FOR(b,0,N-1) FOR(c,0,M-1) FOR(d,0,N-1) {
      int ia = a + k, ib = b + x, ic = c + n * t, id = d + t;
      if (ia < N && ib < N && ic < M && id < N) {
        h[ia][ib][ic][id] = (h[ia][ib][ic][id] + 1ll * s[a][b][c][d] * f[n][k][x][t] % P * C[id][d] % P) % P;
      }
    }

  }
  printf("f[N][N][M][N]={");
  FOR(a,0,N-1) {
    printf("{");
    FOR(b,0,N-1) {
      printf("{");
      FOR(c,0,M-1) {
        printf("{");
        FOR(d,0,N-1) {
          if (d < N-1) printf("%d,", h[a][b][c][d]);
          else printf("%d", h[a][b][c][d]);
        }
        if (c < M-1) printf("},");
        else printf("}");
      }
      if (b < N-1) printf("},");
      else printf("}");
    }
    if (a < N-1) printf("},");
    else printf("}");
  }
  printf("};");
}

int main() {
#ifndef MISAKA
#ifdef IOFILE
  freopen(IOFILE ".in", "r", stdin);
  freopen(IOFILE ".out", "w", stdout);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
#ifdef MULTI
  int T;
  cin >> T;
  while (T--)
#endif
    sol();
  return 0;
}


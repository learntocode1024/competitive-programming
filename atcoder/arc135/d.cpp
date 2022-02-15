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
const int N = 505;
i64 a[N][N], x[N], y[N];
i64 b[N][N];
int n, m;

inline void solve() {
  rd(n, m);
  FOR(i, 1, n + 1) FOR(j, 1, m + 1) cin >> a[i][j];
  FOR(i, 1, n + 1) FOR(j, 1, m + 1) if ((i+j)&1) a[i][j] = -a[i][j];
  FOR(i, 1, n + 1) FOR(j, 1, m + 1) x[j] += a[i][j];
  FOR(i, 1, n + 1) FOR(j, 1, m + 1) y[i] += a[i][j];
  i64 cx = 0, cy = 0;
  FOR(i, 1, m + 1) cx += abs(x[i]);
  FOR(i, 1, n + 1) cy += abs(y[i]);
  println(max(cx, cy));
  FOR(i, 1, m + 1) {
    if (x[i] > 0) {
      FOR(j, 1, n + 1) if (y[j] > 0) {
        i64 d = min(x[i], y[j]);
        x[i] -= d;
        y[j] -= d;
        b[j][i] += d;
      }
    } else {
      FOR(j, 1, n + 1) if (y[j] < 0) {
        i64 d = max(x[i], y[j]);
        x[i] -= d;
        y[j] -= d;
        b[j][i] += d;
      }
    }
  }
  FOR(i, 1, m + 1) if (x[i] > 0) {
    FOR(j, 1, m + 1) if (x[j] < 0) {
      i64 d = min(abs(x[i]), abs(x[j]));
      x[i] -= d;
      x[j] += d;
      b[1][i] += d;
      b[1][j] -= d;
    }
  }
  FOR(i, 1, n + 1) if (y[i] > 0) {
    FOR(j, 1, n + 1) if (y[j] < 0) {
      i64 d = min(abs(y[i]), abs(y[j]));
      y[i] -= d;
      y[j] += d;
      b[i][1] += d;
      b[j][1] -= d;
    }
  }
  FOR(i, 1, n + 1) FOR(j, 1, m + 1) if ((i+j)&1) b[i][j] = -b[i][j];
  FOR(i, 1, n + 1) FOR(j, 1, m + 1) cout << b[i][j] << " \n"[j==m];
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


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
const int N = 1005;
int n, m;
typedef bitset<N> bs;
bs a[N];
struct base {
  bs a[N];
  int rk;
  void operator+= (bs x) {
    ROF(i, 0, m) {
      if (!x[i]) continue;
      if (a[i][i]) x ^= a[i];
      else {
        FOR(j, 0, i) if (a[j][j] && x[j]) x ^= a[j];
        FOR(j, i+1, m) if (a[j][i]) a[j] ^= x;
        a[i] = x;
        ++rk;
        return;
      }
    }
  }
} b[20], all;
int rk[N][N];
int L, R;

void cdq(int p, int l, int r) {
  b[p] = b[p-1];
  while (L < l) b[p] += a[L++];
  while (R > r) b[p] += a[R--];
  if (l == r) {
    bs x = a[l];
    ROF(i, 0, m) if (b[p].a[i][i] && x[i]) x ^= b[p].a[i];
    FOR(i, 0, m) {
      x.flip(i);
      rk[l][i] = b[p].rk;
      if (b[p].a[i][i] && x[i]) {
        rk[l][i] += (b[p].a[i] ^ x).count() != 0;
      } else rk[l][i] += x.count() != 0;
      x.flip(i);
    }
    return;
  }
  int mid = (l + r) >> 1;
  cdq(p+1, l, mid);
  L = l, R = r;
  cdq(p+1, mid+1, r);
}

inline void solve() {
  rd(n, m);
  FOR(i, 0, n) cin >> a[i], all += a[i];
  L = 0, R = n-1;
  cdq(1, 0, n-1);
  int RK = all.rk;
  FOR(i, 0, n) {
    ROF(j, 0, m) {
      if (rk[i][j] < RK) cout << '-';
      else if (rk[i][j] == RK) cout << '0';
      else cout << '+';
    }
    cout << '\n';
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


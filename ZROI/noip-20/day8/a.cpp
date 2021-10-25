#include <bits/stdc++.h>
using namespace std;
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

const int N = 105;

struct bint {
  int c, int a[N];
  bint() = default;
  bint(int x) {
    c = 0;
    while (x != 0) {
      a[c++] = x % 10;
      x /= 10;
    }
  }
  bint operator+ (const bint &b) const {
    bint ret = {};
    ret.c = max(c, b.c);
    int nxt = 0;
    for (int i = 0; i < max(c, b.c); ++i) {
      int cur = a[i] + b.a[i] + nxt;
      ret.a[i] = cur % 10;
      nxt = cur / 10;
    }
    if (nxt) {
      ret.a[ret.c++] = nxt;
    }
    return ret;
  }
  bint operator- (const bint &b) const {
    bint ret = {};
    ret.c = 0;
    int del = 0;
    for (int i = 0; i < c; ++i) {
      if (a[i] - del - b.a[i] < 0) {
        ret.a[i] = 10 + a[i] - del - b.a[i];
        del = 1;
      } else ret.a[i] = a[i] - del - b.a[i], del = 0;
    }
    for (int i = N - 1; i >= 0; --i) {
      if (ret.a[i] != 0) {
        ret.c = i + 1;
        break;
      }
    }
    return ret;
  }
  bint operator* (const bint &b) const {
    bint ret = {};
    for (int i = 0; i < c; ++i) {
      for (int j = 0; j < b.c; ++j) {
        ret.a[i + j] += a[i] * b.a[j];
      }
    }
    int nxt = 0;
    for (int i = 0; i < N - 1; ++i) {
      int cur = ret.a[i] + nxt;
      ret.a[i] = cur % 10;
      if (cur) {
        nxt = cur / 10;
      } else {
        ret.c = i;
        break;
      }
    }
    return ret;
  }
};

bint p2[350], p3[300];
char s[N];
bint out[1005], tot;

inline void solve() {
  p3[0] = p2[0] = bint(1);
  p2[1] = bint(2);
  p3[1] = bint(3);
  for (int i = 2; i < 340; ++i) {
    p2[i] = p2[i - 1] * p2[1];
  }
  for (int i = 2; i < 211; ++i) {
    p3[i] = p3[i - 1] * p3[1];
  }
  cin >> s;
  int n = strlen(s);
  bint a(0);
  for (int i = 0; i < n; ++i) {
    a.a[n - i - 1] = s[i] - '0';
  }
  a.c = n;
  int cnt = 0;
  bint
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
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


/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date:
 * Algorithm:
 * Difficulty:
 *
 *********************************************************************/

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

/********************************** buffer IO *********************************/
namespace IO {
char in[1 << 24]; // sizeof in varied in problem
char const *o;

void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0; // set 0 at the end of buffer.
}

int rd() {
  unsigned u = 0, s = 0;

  while (*o && *o <= 32)
    ++o; // skip whitespaces...

  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o; // skip sign

  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0'); // u * 10 = u * 8 + u * 2 :)

  return static_cast<int>((u ^ s) + !!s);
}

char *rdstr(char *s) {
  while (*o && *o <= 32)
    ++o;
  while (*o > 32)
    *s++ = *o++;
  return s;
}
} // namespace IO

/********************************* macros *************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
#define pb(x) push_back(x)
#define fi first
#define se second
#define REP(x, y, z) for (int x = y; x < z; ++x) // always [y, z)
#define PER(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T> void chkmax(T &a, const T &b) { a = max(a, b); }
template <typename T> void chkmin(T &a, const T &b) { a = min(a, b); }

/*********************************** solution *********************************/
using IO::rd;
#define MX 1005
bool s[MX][MX];
int h, w;
i64 ul[MX][MX], dr[MX][MX];
int p[MX][MX], q[MX][MX], pp[MX][MX], qq[MX][MX];
struct BIT {
struct data {
  i64 s, sx, sy, sxy;
  void operator+=(const data &t) {
    s += t.s, sx += t.sx, sy += t.sy, sxy += t.sxy;
  }
} s[MX][MX];

void inc(i64 x, i64 y, i64 c0) {
  data c;
  c.s = c0, c.sx = 1ll * x * c0, c.sy = 1ll * y * c0, c.sxy = 1ll * x * y * c0;
  for (i64 i = x; i <= h; i += i & -i)
    for (i64 j = y; j <= w; j += j & -j) s[i][j] += c;
}

i64 query(i64 x, i64 y) {
  data r;
  r.s = r.sx = r.sy = r.sxy = 0;
  for (i64 i = x; i > 0; i -= i & -i)
    for (i64 j = y; j > 0; j -= j & -j) r += s[i][j];
  return r.s * (x + 1) * (y + 1) - r.sx * (y + 1) - r.sy * (x + 1) + r.sxy;
}
void mod(int a, int b, int  c, int d, int x) {
  if (a > c || b > d) return;
  inc(a, b, x), inc(a, d + 1, -x), inc(c + 1, b, -x), inc(c + 1, d + 1, x);
}
i64 get(int a, int b, int c, int d) {
  if (a > c || b > d) return 0;
  return query(c, d) - query(c, b - 1) - query(a - 1, d) + query(a - 1, b - 1);
}
} x, y;
inline i64 div(int x) {
  return x * (x + 1) / 2;
}
void solve() {
  h = rd(), w = rd();
  int k = rd();
  for (int i = 0, a, b; i < k; ++i) {
    a = rd(), b = rd();
    s[a][b] = 1;
  }
  REP(i, 1, h + 1)
    REP(j, 1, w + 1)
      p[i][j] = (!s[i][j]) ? p[i][j - 1] : j, pp[i][j] = (!s[i][j]) ? pp[i - 1][j] : i;
  REP(i, 1, h + 1) q[i][w + 1] = w + 1;
  REP(i, 1, w + 1) qq[h + 1][i] = h + 1;
  PER(i, 1, h + 1) {
    PER(j, 1, w + 1)
      q[i][j] = (!s[i][j]) ? q[i][j + 1] : j, qq[i][j] = (!s[i][j]) ? qq[i + 1][j] : i;
  }
  for (int i = 1; i <= h; ++i) {
    for (int j = 1; j <= w; ++j) {
      if (s[i][j]) {
        for (int k = 1; k <= i; ++k) {  
          if (x.get(k, ))
        }
        continue;
      }
      ul[i][j] = (pp[i][j] + 1 - i) * (p[i][j] + 1 - j);
      ul[i][j] -= x.get(pp[i][j] + 1, p[i][j] + 1, i, j);
    }
  }
  for (int i = h; i; --i) {
    for (int j = w; j; --j) {
      if (s[i][j]) {
      y.mod(i, j, qq[i][j] - 1, q[i][j] - 1, 1);
      y.mod(i + 1, j + 1, qq[i][j] - 1, q[i][j] - 1, -1);
        continue;
      }
      dr[i][j] = (qq[i][j] - 1 - i) * (q[i][j] - 1 - j);
      dr[i][j] -= y.get(i, j, qq[i][j] - 1, q[i][j] - 1);
    }
  }
  i64 ans = 0;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (!s[i][j])
        ans += ul[i + 1][j + 1] * dr[i + 1][j + 1];
    }
  }
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
        cerr << ul[i + 1][j + 1] << ' ';
    }
    cerr << endl;
  }
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
        cerr << dr[i + 1][j + 1] << ' ';
    }
    cerr << endl;
  }
  cout << ans << '\n';
}

int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--)
    solve(), T && (clear(), 1);
#else
  solve();
#endif
  return 0;
}

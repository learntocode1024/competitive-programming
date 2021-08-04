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
#include <map>
#include <string>
#include <vector>
using namespace std;

/********************************** buffer IO *********************************/
namespace IO {
char in[1 << 23]; // sizeof in varied in problem
char const *o;

void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0; // set 0 at the end of buffer.
}

void readstr(char *s) {
  while (*o && *o <= 32)
    ++o;
  while (*o > 32)
    *s++ = *o++;
}

int read() {
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
template <typename T> void chkmin(T &a, const T &b) { b = min(a, b); }

/*********************************** solution *********************************/
using IO::read;
#define MX 100005
int n, q;
int a[MX];
char s[MX];

int low[MX];
vector<int> S[MX];
void init(char *s, int n) {
  int q = -1;
  low[0] = -1;
  for (int i = 1; i < n; ++i) {
    while (q > -1 && s[q + 1] != s[i]) q = low[q];
    if (s[q + 1] == s[i]) ++q;
    low[i] = q;
  }
}

namespace SUB1 {
void solve() {
  for (int i = 0; i < n; ++i) {
    char* t = s + i;
    init(t, a[i]);
    int q = -1;
    for (int j = 0; j < n; ++j) {
      while (q > -1 && t[q + 1] != s[j]) q = low[q];
      if (t[q + 1] == s[j]) ++q;
      if (q == a[i] - 1) {
        q = low[q];
        S[i].push_back(j - a[i] + 1);
      }
    }
  }
  while (q--) {
    int l = read(), r = read();
    --l;
    int ans = 0;
    for (int i = l; i < r; ++i) {
      ans += lower_bound(begin(S[i]), end(S[i]), r) - lower_bound(begin(S[i]), end(S[i]), l);
    }
    printf("%d\n", ans);
  }
}
}

namespace SUB3 {
int H[MX];
int P[MX];
long long ans[MX];
int sum[MX];
int l[MX], r[MX];
int A;
map<int, vector<int> > vt;
void solve() {
  srand(time(0));
  A = rand();
  P[0] = 0;
  for (int i = 1; i <= n; ++i) {
    P[i] = P[i - 1] * A;
  }
  H[0] = s[0];
  for (int i = 1; i < n; ++i) {
    H[i] = H[i - 1] * A + s[i];
  }
  for (int i = 0; i < n - a[0]; ++i) {
    int h = H[i + a[i] - 1];
    if (i) h -= H[i - 1] * P[a[i]];
    vt[h].push_back(i);
  }
  for (int i = 0; i < q; ++i) {
    l[i] = read();
    r[i] = read();
    --l[i];
    --r[i];
  }
  for (auto i : vt) {
    auto v = i.second;
    for (int i = 0; i < n; ++i) sum[i] = 0;
    for (auto p : v) sum[p] = 1;
    for (int i = 1; i < n; ++i) {
      sum[i] += sum[i - 1];
    }
    for (int i = 0; i < q; ++i) {
      long long t = sum[r[i]];
      if (l[i]) t -= sum[l[i] - 1];
      ans[i] += 1ll * t * t;
    }
  }
  for (int i = 0; i < q; ++i) {
    printf("%lld\n", ans[i]);
  }
}
}

void solve() {
  n = read();
  q = read();
  IO::readstr(s);
  bool prop1 = 1;
  for (int i = 0; i < n; ++i) {
    a[i] = read();
    if (i && a[i] != a[i - 1]) prop1 = 0;
  }
  if (n <= 3000) SUB1::solve();
  else if (prop1) SUB3::solve();
}

int main() {
  IO::init_in();
  solve();
  return 0;
}

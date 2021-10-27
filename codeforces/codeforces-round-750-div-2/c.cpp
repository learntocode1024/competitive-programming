#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/********************************** buffer IO *********************************/
namespace IO {
char in[1 << 24];  // sizeof in varied in problem
char const *o;
void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0;  // set 0 at the end of buffer.
}
int rd() {
  unsigned u = 0, s = 0;
  while (*o && *o <= 32) ++o;  // skip whitespaces...
  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o;  // skip sign
  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0');  // u * 10 = u * 8 + u * 2 :)
  return static_cast<int>((u ^ s) + !!s);
}
char *rdstr(char *s) {
  while (*o && *o <= 32) ++o;
  while (*o > 32) *s++ = *o++;
  *s = '\0';
  return s;
}
}  // namespace IO

/********************************* utility ************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef pair<int, int> pii;
#define pb(x) push_back(x)
#define mkp(x, y) make_pair(x, y)
#define fi first
#define se second
#define FOR(x, y, z) for (int x = y; x < z; ++x)  // always [y, z)
#define ROF(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  a = min(a, b);
}
pii operator+(const pii &a, const pii &b) {
  return mkp(a.fi + b.fi, a.se + b.se);
}

/*********************************** solution *********************************/
using IO::rd;
#define MULTI
const int N = 1e5+5;
char s[N], s1[N];

bool palin(char *s, int n) {
  FOR(i, 0, n) if (s[i] != s[n - i - 1]) return false;
  return true;
}

void solve() {
  int n = rd();
  IO::rdstr(s);
  int ans = n + 1;
  if (palin(s, n)) puts("0");
  else {
    for (char c = 'a'; c <= 'z'; ++c) {
      int tot = 0;
      FOR(i, 0, n) if (s[i] != c) s1[tot++] = s[i];
      if (!palin(s1, tot)) continue;
      int cur = n - tot;
      int l, r, t;
      for (l = -1, t = 0; t < tot / 2 + (tot & 1);) {
        ++l;
        if (s[l] != c) ++t;
      }
      for (r = n, t = 0; t < tot / 2 + (tot & 1);) {
        --r;
        if (s[r] != c) ++t;
      }
      if (l != r) cur -= r - l - 1;
      while (l >= 0 && r < n) {
        if (s[l] == c && s[r] == c) cur -= 2, --l, ++r;
        else if (s[l] == s[r]) --l, ++r;
        else if (s[l] == c) --l;
        else ++r;
      }
      chkmin(ans, cur);
    }
    cout << (ans == n + 1 ? -1 : ans) << '\n';
  }
}

int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
  solve();
#endif
  return 0;
}
/*
 * checklist:
 * - IO buffer size
 * - potential out-of-bound Errors
 * - inappropriate variable type
 * - potential Arithmetic Error
 * - potential Arithmetic Overflow
 * - typo / logical flaws
 * - clean-up on multiple test cases
 * - sufficient stress tests / random data tests
*/

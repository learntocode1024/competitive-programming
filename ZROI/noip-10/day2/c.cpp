/**********************************************************************
 * This file is the c++ solution to aa particular CP problem written by
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
void chkmax(T &aa, const T &bb) {
  aa = max(aa, bb);
}
template <typename T>
void chkmin(T &aa, const T &bb) {
  aa = min(aa, bb);
}
pii operator+(const pii &aa, const pii &bb) {
  return mkp(aa.fi + bb.fi, aa.se + bb.se);
}

/*********************************** solution *********************************/
using IO::rd;
#define MULTI
const int N = 60;
bool E[N][N];
bool vis[2][N];
int aa[N], bb[N], cnt;
int n;

void dfs(int u, int g) {
  vis[g][u] = 1;
  if (g == 0) {
    ++aa[cnt];
    for (int i = 0; i < n; ++i) {
      if (E[u][i] && !vis[1][i]) {
        dfs(i, 1);
      }
    }
  }
  if (g == 1) {
    ++bb[cnt];
    for (int i = 0; i < n; ++i) {
      if (E[i][u] && !vis[0][i]) {
        dfs(i, 0);
      }
    }
  }
}

int a[N], b[N], c[N];
int dp[10000000];
int cur[N], nxt[N];
int cat = 0;

inline int valid() {
  int ca = 0, cb = 0;
  for (int i = 0; i <= cat; ++i) {
    ca += nxt[i] * a[i];
    cb += nxt[i] * b[i];
  }
  if (ca != cb) return 0;
  return ca * ca;
}

inline int rem() {
  int ret = 0;
  for (int i = cat; i >= 0; --i) {
    ret *= c[i] + 1;
    ret += cur[i] - nxt[i];
  }
  return ret;
}

inline bool dp_next() {
  int i = 0;
  while (i <= cat && nxt[i] == 0) ++i;
  if (i == cat + 1) return 0;
  --nxt[i];
  for (int j = 0; j < i; ++j) {
    nxt[j] = cur[j];
  }
  return 1;
}

inline void get(int x) {
  for (int i = 0; i <= cat; ++i) {
    nxt[i] = cur[i] = x % (c[i] + 1);
    x /= c[i] + 1;
  }
}

void solve() {
  cin >> n;
  for (int i = 0; i < N; ++i) vis[0][i] = vis[1][i] = 0;
  for (int i = 0; i < N; ++i) a[i] = b[i] = c[i] = aa[i] = bb[i] = 0;
  cnt = 0;
  cat = 0;
  int exist = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      char ch;
      cin >> ch;
      E[i][j] = ch - '0';
      if (E[i][j]) ++ exist;
    }
  }
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (!vis[0][i]) {
      dfs(i, 0);
      if (aa[cnt] == bb[cnt]) {
        ans += aa[cnt] * aa[cnt];
        aa[cnt] = bb[cnt] = 0;
      } else {
        ++cnt;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    if (!vis[1][i]) {
      dfs(i, 1);
      if (aa[cnt] == bb[cnt]) {
        ans += aa[cnt] * aa[cnt];
        aa[cnt] = bb[cnt] = 0;
      } else {
        ++cnt;
      }
    }
  }
  pii tmp[N];
  for (int i = 0; i < cnt; ++i) {
    tmp[i].fi = aa[i], tmp[i].se = bb[i];
  }
  sort(tmp, tmp + cnt);
  a[0] = tmp[0].fi;
  b[0] = tmp[0].se;
  for (int i = 0; i < cnt; ++i) {
    if (i && tmp[i] != tmp[i - 1]) {
      ++cat;
      a[cat] = tmp[i].fi;
      b[cat] = tmp[i].se;
    }
    ++c[cat];
  }
  int prod = 1;
  for (int i = 0; i <= cat; ++i) prod *= c[i] + 1;
  for (int i = 1; i < prod; ++i) dp[i] = 1e7;
  for (int i = 1; i < prod; ++i) {
    get(i);
    do {
      int x = valid();
      if (x) {
        chkmin(dp[i], x + dp[rem()]);
      }
    } while (dp_next());
  }
  cout << ans - exist + dp[prod - 1] << '\n';
}

int main() {
#ifdef MULTI
  int T;
  cin >> T;
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

/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
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
  *s = '\0';
  return s;
}
}  // namespace IO

/********************************* utility ************************************/
typedef long long i64;
typedef __int128 i3;
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
std::ostream&
operator<<( std::ostream& dest, __int128_t value )
{
    std::ostream::sentry s( dest );
    if ( s ) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[ 128 ];
        char* d = std::end( buffer );
        do
        {
            -- d;
            *d = "0123456789"[ tmp % 10 ];
            tmp /= 10;
        } while ( tmp != 0 );
        if ( value < 0 ) {
            -- d;
            *d = '-';
        }
        int len = std::end( buffer ) - d;
        if ( dest.rdbuf()->sputn( d, len ) != len ) {
            dest.setstate( std::ios_base::badbit );
        }
    }
    return dest;
}
using IO::rd;
// #define MULTI
const i3 N = 1e5+5;
vector<i3> fc[N];
i3 a[N];
vector<i3> G[N];
i3 low[N], pri[N], phi[N], tot;

void solve() {
  i3 n = rd();
  for (i3 i = 1; i <= 100000; ++i) {
    for (i3 j = i; j <= 100000; j += i) {
      fc[j].pb(i);
    }
  }
  phi[1] = 1;
  for (i3 i = 2; i <= 100000; ++i) {
    if (!low[i]) {
      pri[tot++] = i;
      low[i] = i;
      phi[i] = i - 1;
    }
    for (i3 j = 0; j < tot && pri[j] * i <= 100000; ++j) {
      i3 to = pri[j] * i;
      low[to] = pri[j];
      if (pri[j] == low[i]) {
        phi[to] = phi[i] * pri[j];
        break;
      } else phi[to] = phi[i] * phi[pri[j]];
    }
  }
  for (i3 i = 1; i <= n; ++i) {
    i3 ai = rd();
    for (auto d : fc[ai]) {
      G[d].pb(i);
    }
  }
  i3 ans = 0;
  i3 cn = (n * n + n) / 2;
  for (i3 d = 1; d <= 100000; ++d) {
    if (G[d].size() < 2) continue;
    i3 cur = 0;
    i3 t = G[d].size();
    auto &g = G[d];
    for (i3 i = 0; i < t; ++i) {
      cur += 1ll * g[i] * g[i] * (t - 1);
      cur -= 1ll * g[i] * (n + 1) * i;
    }
    i3 suf = 0;
    for (i3 i = t - 1; i >= 0; --i) {
      cur -= suf * g[i];
      suf += g[i];
    }
    cur += cn * t * (t - 1) / 2;
    ans += cur * phi[d];
  }
  cout << ans << '\n';
}

int main() {
  IO::init_in();
#ifdef MULTI
  i3 T = IO::rd();
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

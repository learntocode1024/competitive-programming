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
#include <bitset>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;
typedef unsigned long long LL;
typedef unsigned long long ULL;

namespace IO {
template<unsigned T>
struct buffer {
  char in[T], out[T];
  char *o, *p, *o1, *p1;
  buffer() {
    o = o1 = in;
    p = out;
    p1 = out + T;
  }
  ~buffer() {
    fwrite(out, 1, p - out, stdout);
  }
  inline char get() {
    return (o == o1) && o1 = (o = in) + fread(in, 1, T, stdin), o == o1 ? EOF : *o++;
  }
  inline char put(char c) {
    if (p == p1) p1 = (p = out) + fwrite(out, 1, T, stdout);
    *p++ = c;
  }
};
buffer<1 << 20> io;

}

#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX 305


string s;
map<LL, bitset<MX>> mp;

int n;

LL hsh[MX];
LL powb[MX];
set<pair<LL, LL>> st;
void solve() {
  scanf("%d", &n);
  cin >> s;
  if (n > 300) return;
  LL b = rand(), c = rand();
  hsh[0] = s[0] * c;
  powb[0] = 1;
  for (int i = 1; i < n; ++i) {
    hsh[i] = hsh[i - 1] * b + s[i] * c;
    powb[i] = powb[i - 1] * b;
  }
  for (int l = 0; l < n; ++l) {
    for (int r = l; r < n; ++r) {
      LL t = hsh[r];
      if (l) t -= hsh[l - 1] * powb[r - l + 1];
      mp[t].set(l);
    }
  }
  LL ans = 0;
  for (int l = 0; l < n; ++l) {
    for (int r = l + 1; r < n; ++r) {
      for (int m = l; m < r; ++m) {
        LL t = hsh[r];
        if (l) t -= hsh[l - 1] * powb[r - l + 1];
        LL t0 = hsh[m];
        if (l) t0 -= hsh[l - 1] * powb[m - l + 1];
        if ((mp[t] ^ mp[t0])._Find_first() > n - r + l - 1) st.insert(make_pair(t, t0));
      }
    }
  }
  printf("%lld\n", st.size());
}

int main() {
  srand(0x292d84b2);
  int T = 1;
  while (T--)
    solve();
  return 0;
}


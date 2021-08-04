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
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long LL;
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
    return (o == o1) && (o1 = (o = in) + fread(in, 1, T, stdin)), o == o1 ? EOF : *o++;
  }
  inline char put(char c) {
    if (p == p1) p1 = (p = out) + fwrite(out, 1, T, stdout);
    *p++ = c;
  }
};
buffer<1 << 20> io;

int readInt() {
  unsigned u = 0, s = 0;
  char ch = io.get();
  do ch = io.get();
  while (ch && ch <= 32); // skip whitespaces...
  if (ch == '-')
    s = ~s, ch = io.get();
  else if (ch == '+')
    ch = io.get(); // skip sign

  
  do u = (u << 3) + (u << 1) + (ch - '0'), ch = io.get(); // u * 10 = u * 8 + u * 2 :)
  while (ch >= '0' && ch <= '9');
  return static_cast<int>((u ^ s) + !!s);
}
int readLL() {
  unsigned long long u = 0, s = 0;
  char ch = io.get();
  do ch = io.get();
  while (ch && ch <= 32); // skip whitespaces...
  if (ch == '-')
    s = ~s, ch = io.get();
  else if (ch == '+')
    ch = io.get(); // skip sign

  
  do u = (u << 3) + (u << 1) + (ch - '0'), ch = io.get(); // u * 10 = u * 8 + u * 2 :)
  while (ch >= '0' && ch <= '9');
  return static_cast<long long>((u ^ s) + !!s);
}
}

#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX

LL a, b;
int t[6], tt[6];
int T1[6] = {4, 0, 2, 3, 5, 1};
int T2[6] = {0, 3, 1, 4, 2, 5};

void t1() {
  for (int i = 0; i < 6; ++i) tt[i] = t[i];
  for (int i = 0; i < 6; ++i) t[i] = tt[T1[i]];
}

void t2() {
  for (int i = 0; i < 6; ++i) tt[i] = t[i];
  for (int i = 0; i < 6; ++i) t[i] = tt[T2[i]];
}

void solve() {
  cin >> a >> b;
  for (int i = 0; i < 6; ++i) {
    cin >> t[i];
  }
  if (a < b) swap(a, b);
  LL prev = 1;
  LL ans = t[4];
  for (int i = 1; i <= b; ++i, t1(), ans += t[4]) {
    LL curr = ceil(1.0 * i * a / b);
    for (int j = prev; j < curr; ++j) t2(), ans += t[4];
    prev = curr;
  }
  cout << ans - t[4] << endl;
}

int main() {
  int T = 1;
  while (T--)
    solve();
  return 0;
}


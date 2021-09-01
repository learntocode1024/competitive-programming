/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Aug  4, 2021
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
char in[1 << 23]; // sizeof in varied in problem
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
typedef long double f80;
#define pb(x) push_back(x)
#define fi first
#define se second
#define REP(x, y, z) for (int x = y; x < z; ++x) // always [y, z)
#define PER(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T> void chkmax(T &a, const T &b) { a = max(a, b); }
template <typename T> void chkmin(T &a, const T &b) { a = min(a, b); }

/*********************************** solution *********************************/
using IO::rd;
#define MX 100005
int q, n;

template<typename T, unsigned size>
struct BIT {
  T a[size];
  void ins(int pos, T val) {
    while (pos < size) {
      a[pos] += val;
      pos += pos & -pos;
    }
  }
  T get(int pos) const {
    T ret = 0;
    while (pos) {
      ret += a[pos];
      pos -= pos & -pos;
    }
    return pos;
  }
  const T &operator[](unsigned i) {
    return a[i];
  }
};

BIT<f80, MX << 1> x1, x0, y1, y2;

struct qry {
  int id, op;
  f80 a, b, c;
  inline void init(int i) {
    id = i;
    cin >> op;
    switch (op) {
      case 1:
        cin >> a >> b >> c;
      case 2:

      default:
    }
  }
  inline void run() {
    
  }
} Q[MX];

void work() {
  
}

void solve() {
  cin >> q;
  REP(i, 0, q)
    Q[i].init();
  work();
  REP(i, 0, q)
    Q[i].run();
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  // IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--)
    solve(), T && (clear(), 1);
#else
  solve();
#endif
  return 0;
}

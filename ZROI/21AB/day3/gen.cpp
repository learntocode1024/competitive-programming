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
#include <random>
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
#define pb(x) push_back(x)
#define fi first
#define se second
#define REP(x, y, z) for (int x = y; x < z; ++x) // always [y, z)
#define PER(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T> void chkmax(T &a, const T &b) { a = max(a, b); }
template <typename T> void chkmin(T &a, const T &b) { a = min(a, b); }

/*********************************** solution *********************************/
using IO::rd;
#define MX

const int N = 300, Q = 300;
typedef pair<int, int> pii;
pii a[N * N], b[N * N];
int main() {
  random_device rand_s;
  auto seed = rand_s();
  mt19937_64 rand(seed);
  uniform_int_distribution<int> p{1, N}, s{2000, N * N/ 9 - N};
  printf("%d %d\n", N, N);
  int k1 = s(rand),k2 = s(rand);
  for (int i = 0; i < N * N; ++i) {
    a[i] = make_pair(p(rand), p(rand));
    b[i] = make_pair(p(rand), p(rand));
  }
  sort(a, a + N * N);
  sort(b, b + N * N);
  unique(a, a + N * N);
  unique(b, b + N * N);
  printf("%d %d\n", k1, k2);
  for (int i = 0; i < k1; ++i)
    printf("%d %d ", a[i].fi, a[i].se);
  puts("");
  for (int i = 0; i < k2; ++i)
    printf("%d %d ", b[i].fi, b[i].se);
  puts("");
  printf("%d %d %d\n", p(rand), p(rand), Q);
  for (int i = 0; i < Q; ++i) {
    printf("%d %d\n", p(rand), p(rand));
  }
  cerr << N << ' ' << k1 << ' ' << k2 << ' ' << Q << endl;
  return 0;
}


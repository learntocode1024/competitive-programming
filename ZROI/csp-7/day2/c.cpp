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
#include <cstring>
#include <iostream>
#include <map>
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

/********************************* utility ************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef pair<int, int> pii;
#define pb(x) push_back(x)
#define mkp(x, y) make_pair(x, y)
#define fi first
#define se second
#define FOR(x, y, z) for (int x = y; x < z; ++x) // always [y, z)
#define ROF(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T> void chkmax(T &a, const T &b) { a = max(a, b); }
template <typename T> void chkmin(T &a, const T &b) { a = min(a, b); }
pii operator+(const pii &a, const pii &b) {
  return mkp(a.fi + b.fi, a.se + b.se);
}

/*********************************** solution *********************************/
using IO::rd;
const int N = 1005;
map<string, int> id;
int tot;
bitset<N> di[N];
string var[N];
int num[N];
char toss, curr;

void solve() {
  int n;
  cin >> n;
  while (n--) {
    string K;
    int cnt = 0;
    cin >> K >> toss >> var[0];
    while (var[cnt] != ";") {
      cin >> var[++cnt];
    }
    bool ans = 1;
    if (id.find(K) != id.end())
      ans = 0;
    for (int i = 0; ans && i < cnt; ++i) {
      if (id.find(var[i]) == id.end())
        ans = 0;
      else
        num[i] = id[var[i]];
    } // validity #2
    for (int i = 0; ans && i + 1 < cnt; ++i) {
      for (int j = i + 1; ans && j < cnt; ++j) {
        if ((di[num[i]] & di[num[j]]).any() && !di[num[i]][num[j]] && !di[num[j]][num[i]]) {
          ans = 0;
        }
      }
    } // validity #3
    if (ans) {
      id[K] = ++tot;
      for (int i = 0; i < cnt; ++i) {
        di[tot] |= di[num[i]];
      }
      di[tot].set(tot);
      cout << "ok\n";
    } else {
      cout << "greska\n";
    }
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
#ifdef MULTI
  int T = IO::rd();
  while (T--)
    solve();
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

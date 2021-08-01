#include <algorithm>
#include <bitset>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
#define FILEIO(X) freopen(x".in", "r", stdin); freopen(x".out", "w", stdout);
template<typename T>
void chkmax(T& a, const T& b) {
  a = max(a, b);
}
template<typename T>
void chkmin(T& a, const T& b) {
  a = min(a, b);
}
#define MX 400005
int jmp[128];
typedef unsigned long long ull;
const int N = 400000;
bool s[N+1][256];

ull myRand(ull &k1, ull &k2) {
    ull k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= (k3 << 23);
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}

void gen(int n, ull a1, ull a2) {
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 256; j++)
            s[i][j] = (myRand(a1, a2) & (1ull << 32)) ? 1 : 0;
}
int n, m;
bool last = 0;
ull a1, a2;
char str[100];
namespace pt20 {
bitset<256> d[MX];
void solve() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 256; ++j) {
      d[i][j] = s[i + 1][j];
    }
  }
  int k;
  bitset<256> Q;
  for (int i = 0; i < m; ++i) {
    cin >> str >> k;
    for (int k = 0; k < 64; ++k) {
      for (int j = 0; j < 4; ++j) {
        Q[(k << 2) + 3 - j] = last ^ ((jmp[str[k]] & (1 << j) ) > 0);
      }
    }
    int mn = 300;
    for (int j = 0; j < n; ++j) {
      int cur = (Q ^ d[j]).count();
      chkmin(mn, cur);
    }
  if (mn > k) {
    cout << "0\n", last = 0;
  } else cout << "1\n", last = 1;
  }
}
}


int main() {
  //freopen("qi.in", "r", stdin);
  //freopen("qi.out", "w", stdout);
  jmp['0'] = 0;
  jmp['1'] = 1;
  jmp['2'] = 2;
  jmp['3'] = 3;
  jmp['4'] = 4;
  jmp['5'] = 5;
  jmp['6'] = 6;
  jmp['7'] = 7;
  jmp['8'] = 8;
  jmp['9'] = 9;
  jmp['A'] = 10;
  jmp['B'] = 11;
  jmp['C'] = 12;
  jmp['D'] = 13;
  jmp['E'] = 14;
  jmp['F'] = 15;
  cin.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> a1 >> a2;
  gen(n, a1, a2);
  pt20::solve();
  return 0;
}

